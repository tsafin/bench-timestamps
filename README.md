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
19:04 $ taskset -c 0 ./bench --benchmark_repetitions=5
2021-05-08 19:04:59
Running ./bench
Run on (8 X 1992.01 MHz CPU s)
CPU Caches:
  L1 Data 32K (x4)
  L1 Instruction 32K (x4)
  L2 Unified 256K (x4)
  L3 Unified 8192K (x1)
***WARNING*** Library was built as DEBUG. Timings may be affected.
-------------------------------------------------------------
Benchmark                      Time           CPU Iterations
-------------------------------------------------------------
CDT_Parse                   4555 ns       4555 ns     111968
CDT_Parse                   4567 ns       4567 ns     111968
CDT_Parse                   4157 ns       4156 ns     111968
CDT_Parse                   3808 ns       3808 ns     111968
CDT_Parse                   4318 ns       4318 ns     111968
CDT_Parse_mean              4281 ns       4281 ns     111968
CDT_Parse_median            4318 ns       4318 ns     111968
CDT_Parse_stddev             315 ns        315 ns     111968
CDT_Parse1                    96 ns         96 ns    7083418
CDT_Parse1                    87 ns         86 ns    7083418
CDT_Parse1                    97 ns         97 ns    7083418
CDT_Parse1                    88 ns         88 ns    7083418
CDT_Parse1                   103 ns        103 ns    7083418
CDT_Parse1_mean               94 ns         94 ns    7083418
CDT_Parse1_median             96 ns         96 ns    7083418
CDT_Parse1_stddev              7 ns          7 ns    7083418
CCTZ_Parse1                  776 ns        776 ns     812659
CCTZ_Parse1                  737 ns        737 ns     812659
CCTZ_Parse1                  672 ns        672 ns     812659
CCTZ_Parse1                  671 ns        671 ns     812659
CCTZ_Parse1                  789 ns        789 ns     812659
CCTZ_Parse1_mean             729 ns        729 ns     812659
CCTZ_Parse1_median           737 ns        737 ns     812659
CCTZ_Parse1_stddev            56 ns         56 ns     812659
ICU_Parse1                 83369 ns      83363 ns       7199
ICU_Parse1                 93202 ns      93203 ns       7199
ICU_Parse1                 85615 ns      85611 ns       7199
ICU_Parse1                114555 ns     114530 ns       7199
ICU_Parse1                 98986 ns      98983 ns       7199
ICU_Parse1_mean            95145 ns      95138 ns       7199
ICU_Parse1_median          93202 ns      93203 ns       7199
ICU_Parse1_stddev          12498 ns      12490 ns       7199
ICU_Parse1_Inv               300 ns        300 ns    2333216
ICU_Parse1_Inv               258 ns        258 ns    2333216
ICU_Parse1_Inv               281 ns        281 ns    2333216
ICU_Parse1_Inv               275 ns        275 ns    2333216
ICU_Parse1_Inv               291 ns        291 ns    2333216
ICU_Parse1_Inv_mean          281 ns        281 ns    2333216
ICU_Parse1_Inv_median        281 ns        281 ns    2333216
ICU_Parse1_Inv_stddev         16 ns         16 ns    2333216
RE_Parse1                     11 ns         11 ns   71724166
RE_Parse1                     10 ns         10 ns   71724166
RE_Parse1                     12 ns         12 ns   71724166
RE_Parse1                     13 ns         13 ns   71724166
RE_Parse1                     12 ns         12 ns   71724166
RE_Parse1_mean                12 ns         12 ns   71724166
RE_Parse1_median              12 ns         12 ns   71724166
RE_Parse1_stddev               1 ns          1 ns   71724166
```

Pay attention to the timings of `*_Parse1` functions!

##  Speed comparison ratio

| Algo           | Median     |  x best   |
|----------------|------------|-----------|
| RE_Parse1      | 12 ns      |  1        |
| CDT_Parse1     | 96 ns      |  8x       |
| ICU_Parse1_Inv | 281 ns     |  23x      |
| CCTZ_Parse1    | 737 ns     |  61x      |





