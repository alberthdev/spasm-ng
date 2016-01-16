#pragma once

#ifdef _WINDOWS
#ifndef _TEST
#include "SPASM_h.h"

#ifdef SPASM_NG_ENABLE_COM
class CSPASMModule : public ATL::CAtlExeModuleT<CSPASMModule>
{
public:
	DECLARE_LIBID(LIBID_SPASM)
};

extern CSPASMModule _AtlModule;
#endif

#endif
#endif
