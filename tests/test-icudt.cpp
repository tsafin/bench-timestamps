#include "unicode/utypes.h"
#include "unicode/udat.h"

#include <chrono>
#include <iostream>
#include <string>

#include "gtest/gtest.h"

TEST(ICU, ParseTimeStamps)
{
	UErrorCode status = U_ZERO_ERROR;

	UDateFormat *fmt = udat_open(UDAT_DEFAULT, UDAT_DEFAULT, "en_US", NULL, 0,NULL, 0, &status);
	ASSERT_FALSE(U_FAILURE(status));
	int32_t pos = 0;

	const char16_t civil_string[] = u"2015-02-18T10:50:31.521345123+10:00";
	UDate d = udat_parse(fmt, civil_string, sizeof(civil_string) - 1, &pos, &status);
	ASSERT_FALSE(U_FAILURE(status));
}
