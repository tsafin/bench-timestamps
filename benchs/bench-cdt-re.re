#include <stddef.h>
#include <string.h>
#include <assert.h>
#include "dt.h"

#include "benchmark/benchmark.h"

static size_t
count_digits(const char * p, size_t i, const size_t len) {
    const size_t n = i;

    for(; i < len; i++) {
        const unsigned char c = p[i] - '0';
        if (c > 9)
            break;
    }
    return i - n;
}

static int
parse_number(const char * p, size_t i, const size_t len) {
    int v = 0;

    switch (len) {
        case 9: v += (p[i++] - '0') * 100000000;
        case 8: v += (p[i++] - '0') * 10000000;
        case 7: v += (p[i++] - '0') * 1000000;
        case 6: v += (p[i++] - '0') * 100000;
        case 5: v += (p[i++] - '0') * 10000;
        case 4: v += (p[i++] - '0') * 1000;
        case 3: v += (p[i++] - '0') * 100;
        case 2: v += (p[i++] - '0') * 10;
        case 1: v += (p[i++] - '0');
    }
    return v;
}

static const int pow_10[10] = {
    1, 10, 100, 1000, 10000, 100000, 1000000, 10000000, 100000000, 1000000000,
};

/*
 *  fffffffff
 */

static size_t
parse_fraction_digits(const char *p, size_t i, size_t len, int *fp) {
    size_t n, ndigits;

    ndigits = n = count_digits(p, i, len);
    if (ndigits < 1)
        return 0;
    if (ndigits > 9)
        ndigits = 9;
    if (fp)
        *fp = parse_number(p, i, ndigits) * pow_10[9 - ndigits];
    return n;
}

size_t
re_parse_iso_date(const char *YYCURSOR, size_t len, dt_t *dtp)
{
    const char *YYLIMIT = YYCURSOR + len;
    const char *YYMARKER;
    const char *s1, *y1, *h1, *m1, *d1, *M1, *z1,
               *s2, *y2, *h2, *m2, *d2, *M2, *z2;
    const char *_yy1, *_yy2;

/*!re2c
    re2c:define:YYCTYPE = char;
    re2c:yyfill:enable = 0; 
    re2c:flags:tags = 1;
    re2c:tags:prefix = "_yy";

    year     = @y1 (([1-9][0-9]*)? [0-9]{4}) @y2;
    month    = @m1 ([1][0-2] | [0][1-9]) @m2;
    day      = @d1 ([3][0-1] | [0][1-9] | [1-2][0-9]) @d2;
    hours    = @h1 ([2][0-3] | [0-1][0-9]) @h2;
    minutes  = @M1 [0-5][0-9] @M2;
    seconds  = @s1 [0-5][0-9] @s2;
    timezone = @z1 ([Z] | [+-]([2][0-3] | [0-1][0-9])[:][0-5][0-9]) @z2;
    datetime = year [-] month [-] day [T] hours [:] minutes [:] seconds timezone [\n];

    *        { return 1; }
    datetime {
        int y, M, d;
        y = parse_number(y1, 0, y2 - y1);
        M = parse_number(m1, 0, m2 - m1);
        d = parse_number(d1, 0, d2 - d1);
        int h, m, s, f = 0;
        h = parse_number(h1, 0, h2 - h1);
        m = parse_number(m1, 0, m2 - m1);
        s = parse_number(s1, 0, s2 - s1);
        dt_parse_iso_zone_extended(z1, z2 - z1, NULL);
        printf(".");

        return 0;
    }
*/

}

static void Parse1()
{
	const char civil_string[] = "2015-02-18T10:50:31Z";
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
