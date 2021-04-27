#include <chrono>
#include <iostream>
#include <string>
#include <assert.h>

#include "cctz/time_zone.h"
#include "benchmark/benchmark.h"

const std::string civil_string = "2015-02-18T10:50:31.521345123+10:00";
cctz::time_zone lax;
std::chrono::system_clock::time_point tp;

static void ParseTimeStamps()
{
	// load_time_zone("America/Los_Angeles", &lax);
	const bool ok = cctz::parse("%Y-%m-%dT%H:%M:%E9S%Ez", civil_string, lax, &tp);
	assert(ok);
}

void CCTZ_Parse1(benchmark::State& state)
{
	for (auto _ : state)
		ParseTimeStamps();

}
BENCHMARK(CCTZ_Parse1);
