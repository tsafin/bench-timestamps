#include <stddef.h>
#include <string.h>
#include <assert.h>

#include "dt.h"

#include "benchmark/benchmark.h"


bool re_parse_iso_date(const char *YYCURSOR, size_t len, dt_t *dtp);

static void Parse1()
{
	// const char civil_string[] = "2015-02-18T10:50:31Z";
	const char civil_string[] = "2015-02-18";
	dt_t dt_expected{};
	bool rc = re_parse_iso_date(civil_string, sizeof(civil_string) - 1,
				                &dt_expected);
	assert(rc);
}

void RE_Parse1(benchmark::State& state) {
	for (auto _ : state)
		Parse1();
}
BENCHMARK(RE_Parse1);
