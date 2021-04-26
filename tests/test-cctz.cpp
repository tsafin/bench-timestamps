#include <chrono>
#include <iostream>
#include <string>

#include "cctz/time_zone.h"
#include "gtest/gtest.h"

TEST(CCTZ, ParseTimeStamps)
{
	const std::string civil_string = "2015-02-18T10:50:31.521345123+10:00";

	cctz::time_zone lax;
	// load_time_zone("America/Los_Angeles", &lax);
	std::chrono::system_clock::time_point tp;
	const bool ok = cctz::parse("%Y-%m-%dT%H:%M:%E9S%Ez", civil_string, lax, &tp);
	ASSERT_TRUE(ok);
}
