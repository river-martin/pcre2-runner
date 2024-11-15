#ifndef PCRE2_RUNNER_H
#define PCRE2_RUNNER_H

#define PCRE2_CODE_UNIT_WIDTH 8

#include <pcre2.h>

void match(const PCRE2_SPTR pattern, const PCRE2_SPTR subject);

#endif // PCRE2_RUNNER_H