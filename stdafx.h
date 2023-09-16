#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <ctype.h>
#include <stdarg.h>
#include <math.h>
#include <errno.h>
#include <stdbool.h>
#include <sys/timeb.h>

#ifndef NO_APPSIGN
#include <gmp.h>
#include <openssl/md5.h>
#endif /* NO_APPSIGN */

#define ARRAYSIZE(z) (sizeof(z)/sizeof((z)[0]))