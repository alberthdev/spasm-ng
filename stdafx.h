#pragma once

#ifndef _STDAFX_H
#define _STDAFX_H

#if defined(_WINDOWS)
#ifndef STRICT
#define STRICT
#endif

#include "targetver.h"

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

typedef unsigned int DWORD;
typedef const char *LPCTSTR;
typedef char *LPSTR, *LPTSTR;
typedef char TCHAR;
typedef void *LPVOID;

#define _T(z) z

#define _stricmp strcasecmp
#define _tcsdup strdup
#define _strdup strdup
#define sprintf_s sprintf


#define StringCchPrintf(dest, size, fmt, ...) sprintf(dest, fmt, __VA_ARGS__)
#define StringCchVPrintf(dest, size, fmt, args) vsprintf(dest, fmt, args)

#define ARRAYSIZE(z) (sizeof(z)/sizeof((z)[0]))

#endif
#endif
