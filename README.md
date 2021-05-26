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
15:08 $ taskset -c 0 ./bench --benchmark_repetitions=5
2021-05-26 15:08:47
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
CDT_Parse                   3247 ns       3247 ns     189428
CDT_Parse                   2997 ns       2997 ns     189428
CDT_Parse                   2515 ns       2515 ns     189428
CDT_Parse                   2673 ns       2673 ns     189428
CDT_Parse                   3227 ns       3227 ns     189428
CDT_Parse_mean              2932 ns       2932 ns     189428
CDT_Parse_median            2997 ns       2997 ns     189428
CDT_Parse_stddev             328 ns        328 ns     189428
CDT_Parse1                   131 ns        131 ns    5508517
CDT_Parse1                    99 ns         99 ns    5508517
CDT_Parse1                    82 ns         82 ns    5508517
CDT_Parse1                    78 ns         78 ns    5508517
CDT_Parse1                    90 ns         90 ns    5508517
CDT_Parse1_mean               96 ns         96 ns    5508517
CDT_Parse1_median             90 ns         90 ns    5508517
CDT_Parse1_stddev             21 ns         21 ns    5508517
CCTZ_Parse1                 1084 ns       1084 ns     854417
CCTZ_Parse1                  852 ns        852 ns     854417
CCTZ_Parse1                  873 ns        873 ns     854417
CCTZ_Parse1                  918 ns        918 ns     854417
CCTZ_Parse1                  939 ns        939 ns     854417
CCTZ_Parse1_mean             933 ns        933 ns     854417
CCTZ_Parse1_median           918 ns        918 ns     854417
CCTZ_Parse1_stddev            91 ns         91 ns     854417
ICU_Parse1                251897 ns     251893 ns       2564
ICU_Parse1                251807 ns     251801 ns       2564
ICU_Parse1                125341 ns     125341 ns       2564
ICU_Parse1                 91493 ns      91495 ns       2564
ICU_Parse1                 79715 ns      79717 ns       2564
ICU_Parse1_mean           160050 ns     160049 ns       2564
ICU_Parse1_median         125341 ns     125341 ns       2564
ICU_Parse1_stddev          85460 ns      85457 ns       2564
ICU_Parse1_Inv               195 ns        195 ns    3640290
ICU_Parse1_Inv               176 ns        176 ns    3640290
ICU_Parse1_Inv               177 ns        177 ns    3640290
ICU_Parse1_Inv               171 ns        171 ns    3640290
ICU_Parse1_Inv               165 ns        165 ns    3640290
ICU_Parse1_Inv_mean          177 ns        177 ns    3640290
ICU_Parse1_Inv_median        176 ns        176 ns    3640290
ICU_Parse1_Inv_stddev         11 ns         11 ns    3640290
RE_Parse1                      7 ns          7 ns   98633539
RE_Parse1                      8 ns          8 ns   98633539
RE_Parse1                      7 ns          7 ns   98633539
RE_Parse1                      7 ns          7 ns   98633539
RE_Parse1                      7 ns          7 ns   98633539
RE_Parse1_mean                 7 ns          7 ns   98633539
RE_Parse1_median               7 ns          7 ns   98633539
RE_Parse1_stddev               0 ns          0 ns   98633539
RE_Parse                     403 ns        403 ns    1630402
RE_Parse                     400 ns        400 ns    1630402
RE_Parse                     433 ns        433 ns    1630402
RE_Parse                     417 ns        417 ns    1630402
RE_Parse                     418 ns        418 ns    1630402
RE_Parse_mean                414 ns        414 ns    1630402
RE_Parse_median              417 ns        417 ns    1630402
RE_Parse_stddev               13 ns         13 ns    1630402
```

Pay attention to the timings of `*_Parse1` functions!

##  Speed comparison ratio

For the single literal parse loop:

| Algo           | Median     |  x best   |
|----------------|------------|-----------|
| RE_Parse1      | 7 ns       |  1        |
| CDT_Parse1     | 90 ns      |  13x      |
| ICU_Parse1_Inv | 176 ns     |  25x      |
| CCTZ_Parse1    | 918 ns     |  131x     |





