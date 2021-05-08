#include <stddef.h>
#include <string.h>
#include <assert.h>

#include "dt.h"

#include "gtest/gtest.h"

size_t re_parse_iso_date(const char *, size_t len, dt_t *dtp);

TEST(RE2C, ParseTimeStamps)
{
	const char civil_string[] = "2015-02-18T10:50:31Z";
	dt_t dt_expected{};
	bool rc = re_parse_iso_date(civil_string,
				      sizeof(civil_string) - 1,
				      &dt_expected);
	ASSERT_TRUE(rc);
	const char string_short[] = "2015-02-18";
	rc = re_parse_iso_date(string_short, sizeof(string_short) - 1, &dt_expected);
	ASSERT_FALSE(rc);
}

