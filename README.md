# Benchmark for C/C++ implementations of datetime parsers

This repository uses several C/C++ timestamp parser implementations
we have got our access to:

- Perl XS implementation [chansen/p5-time-moment](https://github.com/chansen/p5-time-moment.git)
  by  (Christian Hansen)[@hansen]. It's not compiled neither to test, nor 
  to bench. We use their test artifacts for basis of our own tests;

- Pure C implemenentation [chansen/c-dt](https://github.com/chansen/c-dt.git)
  which, AFAIK, is largely precursor for p5-time-moment. We had to patch
  it slightly to properly integrate into cmake build process;

- [Google Civil Time (cctz)](https://github.com/google/cctz.git) C++ 
  implmentation.

- and industry-standard [unicode-org/icu](https://github.com/unicode-org/icu.git) C++ implementation

## Googletest and Google benchmark

We use [Google Test](https://github.com/google/googletest.git) and 
[Google Benchmark](https://github.com/google/benchmark.git) frameworks
as a drivers for running unit-tests and benchmarks here.
We do not yet properly (seamlessly) integrated them to the
build process, and this repository is not yet self-contained, thus you should 
install `googletest` and `libbenchmark-dev` as prerequisites elsewhere.

## Building 

```shell
mkdir build
cd build
cmake .. -DCMAKE_BUILD_TYPE=Release -DCMAKE_EXPORT_COMPILE_COMMANDS=ON -DBUILD_TESTING=OFF
```

## Benchmark results

Be warned - your mileage may vary significantly...

### Release mode

```
✔ ~/bench-timestamp/build [master|✔] 
19:44 $ ./bench 
2021-04-29 19:44:48
Running ./bench
Run on (8 X 1992.01 MHz CPU s)
CPU Caches:
  L1 Data 32K (x4)
  L1 Instruction 32K (x4)
  L2 Unified 256K (x4)
  L3 Unified 8192K (x1)
***WARNING*** Library was built as DEBUG. Timings may be affected.
---------------------------------------------------
Benchmark            Time           CPU Iterations
---------------------------------------------------
CDT_Parse         2583 ns       2583 ns     301967
CDT_Parse1          25 ns         25 ns   25014165
CCTZ_Parse1        498 ns        498 ns    1151814
ICU_Parse1       66973 ns      66972 ns      12217
✔ ~/bench-timestamp/build [master|✔] 
```

Pay attention to the timings of `*_Parse1` functions!

### Debug mode 

```
✔ ~/bench-timestamp/build [master|✚ 3…1] 
19:14 $ ./bench
2021-04-29 19:14:21
Running ./bench
Run on (8 X 1992.01 MHz CPU s)
CPU Caches:
  L1 Data 32K (x4)
  L1 Instruction 32K (x4)
  L2 Unified 256K (x4)
  L3 Unified 8192K (x1)
***WARNING*** Library was built as DEBUG. Timings may be affected.
---------------------------------------------------
Benchmark            Time           CPU Iterations
---------------------------------------------------
CDT_Parse         7852 ns       7853 ns      89204
CDT_Parse1         106 ns        106 ns    5226233
CCTZ_Parse1       2463 ns       2463 ns     230875
ICU_Parse1       88205 ns      88203 ns       9390
✔ ~/bench-timestamp/build [master|✚ 3…1] 

```





