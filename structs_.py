import numpy as np

packet_dtype_ = np.dtype([
    ('header', np.uint8),
    ('timestamp', np.uint64),
    ('payload', np.uint64),
    ('crc', np.uint32)
])