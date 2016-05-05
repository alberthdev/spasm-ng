#pragma once

#ifndef _STDAFX_H
#define _STDAFX_H

#if defined(_WINDOWS)
#ifndef STRICT
#define STRICT
#endif

#include "targetver.h"

/* Workaround for error in Visual Studio 2015 (and newer):
 * error LNK2019: unresolved external symbol ___iob_func referenced in function ___gmp_default_allocate
 */
#if _MSC_VER >= 1900
#include <stdio.h>
extern "C" { FILE __iob_func[3] = { *stdin,*stdout,*stderr }; }
#endif

#ifdef SPASM_NG_ENABLE_COM
//#define _ATL_APARTMENT_THREADED
#define _ATL_FREE_THREADED

#define _ATL_NO_AUTOMATIC_NAMESPACE

#define _ATL_CSTRING_EXPLICIT_CONSTRUCTORS	// some CString constructors will be explicit

#define _ATL_STATIC_REGISTRY
#define ATL_NO_ASSERT_ON_DESTROY_NONEXISTENT_WINDOW
#endif

#include "resource.h"

#ifdef SPASM_NG_ENABLE_COM
#include <atlbase.h>
#include <atlcom.h>
#include <atlctl.h>
#include <atlconv.h>
#include <atlsafe.h>

using namespace ATL;

// We don't have to really worry about this (non-ATL), but
// we'll include it in this #ifdef anyways.
#include <comutil.h>
#endif

#include <windows.h>
#include <windowsx.h>
#include <WinCrypt.h>
#include <wincon.h>
#include <fcntl.h>
#include <sys/timeb.h>
#include <direct.h>
#include <sys/types.h>
#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <ctype.h>
#include <math.h>
#include <time.h>

#include <tchar.h>
#include <strsafe.h>
#include <assert.h>

#include <comutil.h>
#include <comdef.h>
#include <io.h>

#include <string>
#include <unordered_map>
#include <vector>
#include <map>

//#include <vld.h>

#import <scrrun.dll> rename("FreeSpace", "FreeSpace2") no_namespace, raw_interfaces_only

#include "SPASM_h.h"

#include "gmp.h"

// Silly workarounds for WinSDK conflicts with VS2010 Express
// (a seriously buggy release of VS...)
#ifdef SPASM_NG_ENABLE_COM
// Are we using VS2010?
#if (_MSC_VER == 1600)

// The Chromium devs did it best, so I'll let them take over here...

/* Copyright 2013 The Chromium Authors. All rights reserved.
 * Use of this source code is governed by a BSD-style license.
 * Workaround for:
 * http://connect.microsoft.com/VisualStudio/feedback/details/621653/
 * http://crbug.com/225822
 * Note that we can't actually include <stdint.h> here because there's other
 * code in third_party that has partial versions of stdint types that conflict.
 */
#include <intsafe.h>
#undef INT8_MIN
#undef INT16_MIN
#undef INT32_MIN
#undef INT64_MIN
#undef INT8_MAX
#undef UINT8_MAX
#undef INT16_MAX
#undef UINT16_MAX
#undef INT32_MAX
#undef UINT32_MAX
#undef INT64_MAX
#undef UINT64_MAX

#endif // VS2010 check
#endif // SPASM_NG_ENABLE_COM

#else
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <assert.h>
#include <unistd.h>
#include <ctype.h>
#include <stdarg.h>
#ifndef NO_APPSIGN
#include <gmp.h>
#include <openssl/md5.h>
#endif /* NO_APPSIGN */
#include <math.h>
#include <errno.h>
#include <stdbool.h>
#include <sys/timeb.h>

#define __inout

#ifdef UNIXVER
typedef unsigned int DWORD;
#else
#include <windows.h>
#endif
typedef const char *LPCTSTR;
typedef char *LPSTR, *LPTSTR;
typedef char TCHAR;
typedef void *LPVOID;

#define _T(z) z

#define _stricmp strcasecmp
#define _tcsdup strdup
#define _strdup strdup
#define sprintf_s sprintf
#define _strtoi64 strtoll

#define StringCchPrintf(dest, size, fmt, ...) snprintf(dest, size, fmt, __VA_ARGS__)
#define StringCchVPrintf(dest, size, fmt, args) vsnprintf(dest, size, fmt, args)

#ifdef UNIXVER
#define ARRAYSIZE(z) (sizeof(z)/sizeof((z)[0]))
#endif

#endif
#endif
