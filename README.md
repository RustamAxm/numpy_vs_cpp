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
rustam@rustam-ZenBook:~/numpy_vs_cpp$ time python3 python_/decoder.py 
start find header 0xab
simple_decode runtime: 0.262674 s

real    0m3,192s
user    0m2,850s
sys     0m0,455s
rustam@rustam-ZenBook:~/numpy_vs_cpp$ cd cpp_/cmake-build-debug/
rustam@rustam-ZenBook:~/numpy_vs_cpp/cpp_/cmake-build-debug$ time ./numpy_vs_cpp 
Duration: 78 ms

real    0m2,053s
user    0m0,431s
sys     0m1,536s

```
Thread implements and async added, full cast more fast
```bash
rustam@rustam-ZenBook:~/numpy_vs_cpp/cpp_/cmake-build-debug$ time ./numpy_vs_cpp 
simple impl: 57 ms
simple full cast impl: 19 ms
thread impl: 66 ms
async impl: 63 ms

real    0m0,234s
user    0m0,223s
sys     0m0,070s


```



