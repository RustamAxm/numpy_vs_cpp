import sys
import logging
import time

import numpy as np
from multiprocessing import Pool, cpu_count
from structs_ import packet_dtype_

logger = logging.getLogger('__decoder__')
logger.setLevel(logging.DEBUG)
sh = logging.StreamHandler()
logger.addHandler(sh)

header = 0xab


def benchmark(func):
    def wrapper(*args, **kwargs):
        start = time.time()
        to_ret = func(*args)
        logger.info(f'{func.__name__} runtime: {time.time() - start:f} s')
        return to_ret
    return wrapper


def simple_decode(buffer):
    ch = [0]
    offset = 0
    logger.info(f'start find header {hex(header)}')
    try:
        while ch[0] != header:
            ch = np.frombuffer(buffer, dtype=np.uint8, count=1, offset=offset)
            offset += 1
    except ValueError as ex:
        logger.error(f'header {hex(header)} not in buffer {ex.args}')

    offset -= 1
    count = len(buffer) // packet_dtype_.itemsize - 5
    try:
        to_return = np.frombuffer(buffer, dtype=packet_dtype_, count=count, offset=offset).tolist()
    except ValueError as ex:
        logger.error(f'buffer size is small {ex.args}')

    return to_return


def multiproc_decode(buffer):
    cpu_count_ = cpu_count()
    list_bin = []
    step = len(buffer) // cpu_count_
    logger.info(f'step = {step}')
    for i in range(cpu_count_ - 1):
        start = i * step
        stop = start + step
        list_bin.append(buffer[start:stop])
    list_bin.append(buffer[stop::])

    logger.info(f'{[len(x) for x in list_bin]}')

    with Pool(cpu_count_) as p:
        tmp = p.map(simple_decode, list_bin)

    res = np.row_stack(tmp)
    return res


def save_np(name, out):
    try:
        header = " ".join(packet_dtype_.names)
        np.savetxt(name, out, comments='', header=header, fmt='%12d')
    except Exception as ex:
        logger.error(f'cant save to txt {ex.args}')


if __name__ == '__main__':
    try:
        file_bin = sys.argv[1]
    except IndexError:
        file_bin = 'out.bin'

    with open(file_bin, 'rb') as file:
        bin_in = file.read()

    out = benchmark(simple_decode)(bin_in)

    # out_2 = benchmark(multiproc_decode)(bin_in)

    save_np(f'out.txt', out)
    # save_np(f'out2.txt', out_2)
