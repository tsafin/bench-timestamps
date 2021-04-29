# Benchmark for C/C++ implementations of datetime parsers

This repository uses several C/C++ timestamp parser implementations
we have got our access to:

- Perl XS implementation [chansen/p5-time-moment](https://github.com/chansen/p5-time-moment.git)
  by  [Christian Hansen](https://github.com/chansen). It's not compiled neither to test, nor 
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

gcc 8.3, with release mode gives the following numbers for me.
_Be warned - your mileage may vary significantly_...

```
✔ ~/bench-timestamp/build [master|✚ 1] 
02:12 $ ./bench 
2021-04-30 02:13:00
Running ./bench
Run on (8 X 1992.01 MHz CPU s)
CPU Caches:
  L1 Data 32K (x4)
  L1 Instruction 32K (x4)
  L2 Unified 256K (x4)
  L3 Unified 8192K (x1)
***WARNING*** Library was built as DEBUG. Timings may be affected.
------------------------------------------------------
Benchmark               Time           CPU Iterations
------------------------------------------------------
CDT_Parse            2025 ns       1958 ns     469491
CDT_Parse1             23 ns         23 ns   30816175
CCTZ_Parse1           475 ns        475 ns    1319145
ICU_Parse1         595501 ns     594711 ns      13085
ICU_Parse1_Inv        238 ns        238 ns    2871033
✔ ~/bench-timestamp/build [master|✚ 1]
```

Pay attention to the timings of `*_Parse1` functions!





