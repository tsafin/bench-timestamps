#include <stddef.h>
#include <string.h>
#include <assert.h>
#include "dt.h"

#include "benchmark/benchmark.h"

size_t re_parse_iso_date(const char *, size_t len, dt_t *dtp);

static void Parse1()
{
	// const char civil_string[] = "2015-02-18T10:50:31Z";
	const char civil_string[] = "2015-02-18";
	dt_t dt_expected{};
	size_t rc = re_parse_iso_date(civil_string,
				      sizeof(civil_string) - 1,
				      &dt_expected);
	assert(rc > 1);
}

void RE_Parse1(benchmark::State& state) {
	for (auto _ : state)
		Parse1();
}
BENCHMARK(RE_Parse1);
