# np decode tests
## simple numpy vs multiproc python + numpy
logs
```bash
start find header 0xab
simple_decode runtime: 0.404432 s
step = 2625000
[2625000, 2625000, 2625000, 2625000, 2625000, 2625000, 2625000, 2625000]
start find header 0xab
start find header 0xab
start find header 0xab
start find header 0xab
start find header 0xab
start find header 0xab
start find header 0xab
start find header 0xab
multiproc_decode runtime: 1.838379 s
```

## simple cpp vs simple numpy python
logs
```bash
rustam@rustam-ZenBook:~/np_decoder$ time python3 python_/decoder.py 
start find header 0xab
simple_decode runtime: 0.262674 s

real    0m3,192s
user    0m2,850s
sys     0m0,455s
rustam@rustam-ZenBook:~/np_decoder$ cd cpp_/cmake-build-debug/
rustam@rustam-ZenBook:~/np_decoder/cpp_/cmake-build-debug$ time ./np_decoder 
Duration: 78 ms

real    0m2,053s
user    0m0,431s
sys     0m1,536s

```
Thread implements added 
```bash
rustam@rustam-ZenBook:~/np_decoder/cpp_/cmake-build-debug$ time ./np_decoder 
thread impl: 78 ms
simple impl: 139 ms

real    0m0,167s
user    0m0,141s
sys     0m0,065s

```



