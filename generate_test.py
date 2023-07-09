import time
import numpy as np
from zlib import crc32
from structs_ import packet_dtype_


def generate_bin():
    size_ = 10000
    tmp = np.zeros(1, dtype=packet_dtype_)
    tmp['header'] = 0xab

    for i in range(size_):
        tmp['timestamp'] = np.uint64(time.time_ns())
        tmp['payload'] = np.uint64(i)
        tmp['crc'] = crc32(tmp.tobytes()[:-4])
        if i == 0:
            out = tmp
        else:
            out = np.row_stack((out, tmp))
    out_bin_ = out.tobytes()

    with open('out.bin', 'wb') as file:
        file.write(out_bin_ * 100)


if __name__ == '__main__':
    generate_bin()
