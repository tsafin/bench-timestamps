#include "dt.h"
#include <string.h>
#include <assert.h>

#include "benchmark/benchmark.h"
// 180_from_string.t

const char sample[] = "2012-12-24T15:30Z";

const char * tests[] = {
	"2012-12-24 15:30Z",
	"2012-12-24 15:30z",
	"2012-12-24 16:30+01:00",
	"2012-12-24 16:30+0100",
	"2012-12-24 16:30+01",
	"2012-12-24 14:30-01:00",
	"2012-12-24 14:30-0100",
	"2012-12-24 14:30-01",
	"2012-12-24 15:30:00Z",
	"2012-12-24 15:30:00z",
	"2012-12-24 16:30:00+01:00",
	"2012-12-24 16:30:00+0100",
	"2012-12-24 14:30:00-01:00",
	"2012-12-24 14:30:00-0100",
	"2012-12-24 15:30:00.123456Z",
	"2012-12-24 15:30:00.123456z",
	"2012-12-24 16:30:00.123456+01:00",
	"2012-12-24 16:30:00.123456+01",
	"2012-12-24 14:30:00.123456-01:00",
	"2012-12-24 14:30:00.123456-01",
	"2012-12-24t15:30Z",
	"2012-12-24t15:30z",
	"2012-12-24t16:30+01:00",
	"2012-12-24t16:30+0100",
	"2012-12-24t14:30-01:00",
	"2012-12-24t14:30-0100",
	"2012-12-24t15:30:00Z",
	"2012-12-24t15:30:00z",
	"2012-12-24t16:30:00+01:00",
	"2012-12-24t16:30:00+0100",
	"2012-12-24t14:30:00-01:00",
	"2012-12-24t14:30:00-0100",
	"2012-12-24t15:30:00.123456Z",
	"2012-12-24t15:30:00.123456z",
	"2012-12-24t16:30:00.123456+01:00",
	"2012-12-24t14:30:00.123456-01:00",
	"2012-12-24 16:30 +01:00",
	"2012-12-24 14:30 -01:00",
	"2012-12-24 15:30 UTC",
	"2012-12-24 16:30 UTC+1",
	"2012-12-24 16:30 UTC+01",
	"2012-12-24 16:30 UTC+0100",
	"2012-12-24 16:30 UTC+01:00",
	"2012-12-24 14:30 UTC-1",
	"2012-12-24 14:30 UTC-01",
	"2012-12-24 14:30 UTC-01:00",
	"2012-12-24 14:30 UTC-0100",
	"2012-12-24 15:30 GMT",
	"2012-12-24 16:30 GMT+1",
	"2012-12-24 16:30 GMT+01",
	"2012-12-24 16:30 GMT+0100",
	"2012-12-24 16:30 GMT+01:00",
	"2012-12-24 14:30 GMT-1",
	"2012-12-24 14:30 GMT-01",
	"2012-12-24 14:30 GMT-01:00",
	"2012-12-24 14:30 GMT-0100",
	"2012-12-24 14:30 -01:00",
	"2012-12-24 16:30:00 +01:00",
	"2012-12-24 14:30:00 -01:00",
	"2012-12-24 16:30:00.123456 +01:00",
	"2012-12-24 14:30:00.123456 -01:00",
	"2012-12-24 15:30:00.123456 -00:00",
	"20121224T1630+01:00",
	"2012-12-24T1630+01:00",
	"20121224T16:30+01",
	"20121224T16:30 +01",
};

#define DIM(a) (sizeof(a) / sizeof(a[0]))

// p5-time/moment/src/moment_pare.c: parse_string_strict()
static int
parse_datetime_extended(const char *str, size_t len,
			int64_t *sp, int64_t *np, int64_t *op)
{
	size_t n;
	dt_t dt;
	int sod, nanosecond, offset;
	bool extended;

	n = dt_parse_iso_date(str, len, &dt);
	if (!n || n == len)
		return 1;

	/*
	* 0123456789
	* 2012-12-14
	*/
	extended = str[4] == '-';
	if (str[n++] != 'T')
		return 1;

	str += n;
	len -= n;

	if (extended)
		n = dt_parse_iso_time_extended(str, len, &sod, &nanosecond);
	else
		n = dt_parse_iso_time_basic(str, len, &sod, &nanosecond);

	if (!n || n == len)
		return 1;

	str += n;
	len -= n;

	if (extended)
		n = dt_parse_iso_zone_extended(str, len, &offset);
	else
		n = dt_parse_iso_zone_basic(str, len, &offset);

	if (!n || n != len)
		return 1;

	*sp = ((int64_t)dt_rdn(dt) - 719163) * 86400 + sod - offset * 60;
	*np = nanosecond;
	*op = offset;
	return 0;
}

static void ParseTimeStamps()
{
	size_t index;
	int64_t secs_expected;
	int64_t nanosecs;
	int64_t ofs;
	int rc = parse_datetime_extended(sample, sizeof(sample) - 1,
					 &secs_expected, &nanosecs, &ofs);
	assert(rc == 0);
	assert(nanosecs == 0);

	for (index = 0; index < DIM(tests); index++) {
		int64_t secs;
		int rc = parse_datetime_extended(sample, sizeof(sample) - 1,
						&secs, &nanosecs, &ofs);
		assert(rc == 0);
		assert(secs == secs_expected);
	}
}

void CDT_Parse(benchmark::State& state) {
	for (auto _ : state)
		ParseTimeStamps();
}
BENCHMARK(CDT_Parse);

static void Parse1()
{
	const char civil_string[] = "2015-02-18T10:50:31.521345123+10:00";
	int64_t secs;
	int64_t nanosecs;
	int64_t ofs;
	int rc = parse_datetime_extended(civil_string, sizeof(civil_string) - 1,
					 &secs, &nanosecs, &ofs);
	assert(rc == 0);
	assert(nanosecs == 521345123);
}

void CDT_Parse1(benchmark::State& state) {
	for (auto _ : state)
		Parse1();
}
BENCHMARK(CDT_Parse1);


BENCHMARK_MAIN();
