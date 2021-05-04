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
  implmentation;

- and industry-standard [unicode-org/icu](https://github.com/unicode-org/icu.git) C++ implementation;

- also there is simple `re2c`-based reimplementation of `c-dt` 
  datetime parser, which supposed to show the beauty of deterministic
  finite automatas :)

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
✔ ~/bench-timestamp/build [master|●2✚ 2…2]
01:09 $ ./bench
2021-05-05 01:09:27
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
CDT_Parse            1526 ns       1526 ns     446671
CDT_Parse1             17 ns         17 ns   42355736
CCTZ_Parse1           583 ns        583 ns    1856389
ICU_Parse1          74802 ns      74801 ns      11760
ICU_Parse1_Inv        160 ns        160 ns    3999884
RE_Parse1               7 ns          7 ns   92551055
```

Pay attention to the timings of `*_Parse1` functions!





