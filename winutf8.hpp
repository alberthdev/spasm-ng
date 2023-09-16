#pragma once

#ifdef WIN32
#include <string>
#include <stringapiset.h>

static inline ::std::wstring widen(const char *s) {
	::std::wstring out;
	int wstr_length = MultiByteToWideChar(CP_UTF8, 0, s, -1, NULL, 0);

	out.resize(wstr_length);
	MultiByteToWideChar(CP_UTF8, 0, s, -1, &out[0], wstr_length);

    return out;
}
#endif