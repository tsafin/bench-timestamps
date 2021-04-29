#define U_DISABLE_RENAMING 1
#include "unicode/utypes.h"
#include "unicode/udat.h"

#include <chrono>
#include <iostream>
#include <string>

#include "benchmark/benchmark.h"

const char16_t civil_string[] = u"2015-02-18T10:50:31.521345123+10:00";
const char16_t format[] = u"YYYY-MM-ddTHH:mm:ss.SX";

static void ParseTimeStamps()
{
	UErrorCode status = U_ZERO_ERROR;
	UDateFormat *fmt = udat_open(UDAT_PATTERN, UDAT_PATTERN, "en_US", NULL, 0, format, 0, &status);

	assert(!U_FAILURE(status));
	int32_t pos = 0;

	UDate d = udat_parse(fmt, civil_string, sizeof(civil_string) - 1, &pos, &status);
	assert(!U_FAILURE(status));
}

void ICU_Parse1(benchmark::State& state)
{
	for (auto _ : state)
		ParseTimeStamps();

}
BENCHMARK(ICU_Parse1);
