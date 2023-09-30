#include <array>
#include <cassert>
#include <cstdarg>
#include <cstdio>
#include <cstdlib>

#define _ERRORS_CPP
#include "errors.h"

#include "spasm.h"
#include "console.h"
#include "list.h"

typedef struct tagERRORINSTANCE
{
	char *lpszFileName;
	int line_num;					//-1 for no line
	int32_t dwErrorCode;
	int nSession;
	bool fSuppressErrors;
	bool fIsWarning;
	int nPrintSession;
	char *lpszErrorText;
	char *lpszAnnotation;
} ERRORINSTANCE, *LPERRORINSTANCE;

typedef struct _errorlist {
	LPERRORINSTANCE data;
	struct _errorlist *next;
} errorlist_t;

errorlist_t *g_ErrorList;
int g_nErrorSession = 0;

static void PrintSPASMError(const LPERRORINSTANCE lpError)
{
	if (mode & MODE_CODE_COUNTER)
	{
		return;
	}

	assert(lpError != NULL);
	if ((lpError->dwErrorCode != SPASM_ERR_SUCCESS) || (lpError->lpszErrorText != NULL))
	{
		WORD orig_attributes = save_console_attributes();
		set_console_attributes(lpError->fIsWarning ? COLOR_YELLOW : COLOR_RED);
		if (lpError->lpszAnnotation != NULL)
		{
			printf("%s\n", lpError->lpszAnnotation);
		}

		printf("%s\n", lpError->lpszErrorText);
		restore_console_attributes(orig_attributes);
	}
}

static LPERRORINSTANCE AllocErrorInstance()
{
	LPERRORINSTANCE lpErr = (LPERRORINSTANCE) malloc(sizeof(ERRORINSTANCE));
	lpErr->dwErrorCode = SPASM_ERR_SUCCESS;
	lpErr->line_num = -1;
	lpErr->lpszFileName = NULL;
	//lpErr->fSuppressErrors = suppress_errors;
	lpErr->nSession = g_nErrorSession;
	lpErr->nPrintSession = -1;
	lpErr->lpszErrorText = NULL;
	lpErr->lpszAnnotation = NULL;
	return lpErr;
}

static void FreeErrorInstance(LPERRORINSTANCE lpErr)
{
	if (lpErr->lpszErrorText != NULL)
	{
		free(lpErr->lpszErrorText);
	}
	if (lpErr->lpszAnnotation != NULL)
	{
		free(lpErr->lpszAnnotation);
	}
	if (lpErr->lpszFileName != NULL)
	{
		free(lpErr->lpszFileName);
	}
	free(lpErr);
	lpErr = NULL;
}

int StartSPASMErrorSession(void)
{
	//suppress_errors = true;
	return ++g_nErrorSession;
}

int GetSPASMErrorSessionErrorCount(int nSession)
{
	int nCount = 0;
	list_t *pList = (list_t *) g_ErrorList;
	while ((pList != NULL) && ((LPERRORINSTANCE) pList->data)->nSession == nSession)
	{
		if (((LPERRORINSTANCE) pList->data)->dwErrorCode != SPASM_ERR_SUCCESS)
		{
			nCount++;
		}
		pList = pList->next;
	}
	return nCount;
}

bool IsSPASMErrorFatal(int32_t dwError)
{
	return !(dwError == SPASM_ERR_LOCAL_LABEL_FORWARD_REF ||
			  dwError == SPASM_ERR_LABEL_NOT_FOUND ||
			  dwError == SPASM_ERR_SUCCESS ||
			  dwError == SPASM_ERR_RECURSION_DEPTH);
}

bool IsSPASMErrorSessionFatal(int nSession)
{
	bool fIsFatal = false;
	list_t *pList = (list_t *) g_ErrorList;
	while ((pList != NULL) && ((LPERRORINSTANCE) pList->data)->nSession == nSession)
	{
		LPERRORINSTANCE lpError = (LPERRORINSTANCE) pList->data;
		int32_t dwError = lpError->dwErrorCode;
		if (IsSPASMErrorFatal(dwError))
		{
			fIsFatal = true;
			break;
		}
		pList = pList->next;
	}
	return fIsFatal;
}

static void ReplayErrorRecursive(const list_t *pList, bool fFatalOnly)
{
	if (pList == NULL)
		return;

	ReplayErrorRecursive(pList->next, fFatalOnly);
	if (((LPERRORINSTANCE) pList->data)->nSession == 1)
	{
		LPERRORINSTANCE lpError = (LPERRORINSTANCE) pList->data;
		if (fFatalOnly) 
		{
			if (!IsSPASMErrorFatal(lpError->dwErrorCode))
			{
				return;
			}
		}
		DPRINT("[ReplayErrorRecursive] printing error\n");
		PrintSPASMError(lpError);
	}
}

void ReplaySPASMErrorSession(int nSession, bool fFatalOnly)
{
	if (nSession == 1)
	{
		DPRINT("[ReplaySPASMErrorSession] calling ReplayErrorRecursive\n");
		ReplayErrorRecursive((list_t *) g_ErrorList, fFatalOnly);
	}
	else
	{
		list_t *pList = (list_t *) g_ErrorList;
		while ((pList != NULL) && ((LPERRORINSTANCE) pList->data)->nSession == nSession)
		{
			// Move it up to the next error level
			((LPERRORINSTANCE) pList->data)->nSession--;
			pList = pList->next;
		}
	}	
}

void ReplayFatalSPASMErrorSession(int nSession)
{
	ReplaySPASMErrorSession(nSession, true);
}

bool IsErrorInSPASMErrorSession(int nSession, int32_t dwErrorCode)
{
	list_t *pList = (list_t *) g_ErrorList;
	while ((pList != NULL) && ((LPERRORINSTANCE) pList->data)->nSession == nSession)
	{
		LPERRORINSTANCE lpError = (LPERRORINSTANCE) pList->data;
		if (lpError->dwErrorCode == dwErrorCode)
		{
			return true;
		}
		pList = pList->next;
	}
	return false;
}

void AddSPASMErrorSessionAnnotation(int nSession, const char *lpszFormat, ...)
{
	va_list valist;
	va_start(valist, lpszFormat);

	char szBuffer[256] = {};
	char szDescription[128] = "An error occurred";

	vsnprintf(szDescription, std::size(szDescription) - 1, lpszFormat, valist);
	snprintf(szBuffer, std::size(szBuffer) - 1, "%s:%d: %s",
		curr_input_file, line_num, szDescription);

	va_end(valist);

	list_t *pList = (list_t *) g_ErrorList;
	while (pList != NULL)
	{
		LPERRORINSTANCE lpErr = (LPERRORINSTANCE) pList->data;
		if (lpErr->nSession >= nSession)
		{
			if (lpErr->lpszAnnotation != NULL)
			{
				free(lpErr->lpszAnnotation);
			}
			lpErr->lpszAnnotation = strdup(szBuffer);
		}
		pList = pList->next;
	}
}
void EndSPASMErrorSession(int nSession) {
	DPRINT("[EndSPASMErrorSession] called with nSession = %d\n", nSession);
	int fatalErrors = CleanupSPASMErrorSession(nSession);
	DPRINT("[EndSPASMErrorSession] fatal errs = %d\n", fatalErrors);
	
	if (nSession == 1 && fatalErrors > 0)
		exit(EXIT_FATAL_ERROR);
}

//returns the number of fatal errors
int CleanupSPASMErrorSession(int nSession)
{
	int fatalErrorCount = 0;
	list_t *pList = (list_t *) g_ErrorList;
	
	list_t *pPrev = NULL, *old_list = NULL;
	while ((pList != NULL) && ((LPERRORINSTANCE) pList->data)->nSession == nSession)
	{
		LPERRORINSTANCE lpErr = (LPERRORINSTANCE) pList->data;

		if (pPrev == NULL)
		{
			g_ErrorList = (errorlist_t *) pList->next;
		}
		else
		{
			pPrev->next = pList->next;
		}
		if(IsSPASMErrorFatal(lpErr->dwErrorCode)) {
			fatalErrorCount++;
		}
		FreeErrorInstance(lpErr);
		list_t *pListOld = pList;
		pList = pList->next;
		list_free_node(pListOld);

		//assert(pList != NULL);
		if (pList == NULL)
			break;
	}

	g_nErrorSession--;
	return fatalErrorCount;
}


void ClearSPASMErrorSessions()
{
	if (g_ErrorList != NULL)
	{
		list_free((list_t *) g_ErrorList, true, (void (*)(void *)) FreeErrorInstance);
	}
	g_nErrorSession = 0;
	g_ErrorList = NULL;
}

void FreeSPASMErrorSessions(void)
{
	list_t *pList = (list_t *) g_ErrorList;
	
	list_t *pNext = NULL;
	while (pList)
	{
		LPERRORINSTANCE lpErr = (LPERRORINSTANCE) pList->data;
		
		pNext = pList->next;
		FreeErrorInstance(lpErr);
		list_free_node(pList);
		pList = pNext;
	}
}

#ifdef _TEST
int32_t GetLastSPASMError()
{
	list_t *pList = (list_t *) g_ErrorList;
	while (pList != NULL)
	{
		LPERRORINSTANCE lpError = (LPERRORINSTANCE) pList->data;
		if (lpError->dwErrorCode != SPASM_ERR_SUCCESS)
		{
			return lpError->dwErrorCode;
		}
		pList = pList->next;
	}
	return SPASM_ERR_SUCCESS;
}

int GetLastSPASMErrorLine()
{
	list_t *pList = (list_t *) g_ErrorList;
	while (pList != NULL)
	{
		LPERRORINSTANCE lpError = (LPERRORINSTANCE) pList->data;
		if (lpError->dwErrorCode != SPASM_ERR_SUCCESS)
		{
			return lpError->line_num;
		}
		pList = pList->next;
	}
	return SPASM_ERR_SUCCESS;
}
#endif


static void SetLastSPASMProblem(int32_t dwErrorCode, bool fIsWarning, va_list valist)
{
	if (dwErrorCode == SPASM_ERR_SUCCESS)
	{
		return;
	}

	LPERRORINSTANCE lpErr = AllocErrorInstance();
	lpErr->dwErrorCode = dwErrorCode;
	lpErr->line_num = line_num;
	lpErr->lpszFileName = strdup(curr_input_file);
	//lpErr->fSuppressErrors = suppress_errors;
	lpErr->fIsWarning = fIsWarning;
	
	char szBuffer[256];
	char szDescription[128] = "An error occurred";

	for (int i = 0; i < std::size(g_ErrorCodes); i++)
	{
		if (g_ErrorCodes[i].dwCode == lpErr->dwErrorCode)
		{
			vsnprintf(szDescription, std::size(szDescription) - 1,
				g_ErrorCodes[i].lpszDescription, valist);
			break;
		}
	}

	const char *lpszProblemType = (fIsWarning) ? "warning" : "error";
	const char *lpszProblemCode = (fIsWarning) ? "SW" : "SE";

	if (lpErr->line_num != -1)
	{
		snprintf(szBuffer, std::size(szBuffer) - 1, "%s:%d: %s %s%03X: %s",
			lpErr->lpszFileName, lpErr->line_num, lpszProblemType, lpszProblemCode, lpErr->dwErrorCode, szDescription);
	}
	else
	{
		snprintf(szBuffer, std::size(szBuffer) - 1, "%s: %s %s%03X: %s",
			lpErr->lpszFileName, lpszProblemType, lpszProblemCode, lpErr->dwErrorCode, szDescription);
	}

	lpErr->lpszErrorText = strdup(szBuffer);

	g_ErrorList = (errorlist_t *) list_prepend((list_t *) g_ErrorList, lpErr);
	//if (suppress_errors == false)
	//{
		//PrintSPASMError(lpErr);
	//}
}

void SetLastSPASMWarning(int32_t dwErrorCode, ...)
{
	va_list valist;
	va_start(valist, dwErrorCode);

	SetLastSPASMProblem(dwErrorCode, true, valist);

	va_end(valist);
}

void SetLastSPASMError(int32_t dwErrorCode, ...)
{
	va_list valist;
	va_start(valist, dwErrorCode);

	SetLastSPASMProblem(dwErrorCode, false, valist);

	va_end(valist);
}
