#pragma once

#include <stdint.h>

typedef struct tagSPASMERROR
{
	uint32_t dwCode;
	const char *lpszDescription;
}
SPASMERROR, *LPSPASMERROR;

#define SPASM_ERR_SUCCESS					0x000
#define SPASM_ERR_FILE_NOT_FOUND			0x001
#define SPASM_ERR_NO_ACCESS					0x002

#define SPASM_ERR_LOCAL_LABEL_FORWARD_REF	0x100
#define SPASM_ERR_LOCAL_LABEL_SYNTAX		0x101
#define SPASM_ERR_ARG_USED_WITHOUT_VALUE	0x102
#define SPASM_ERR_OPERATOR_EXPECTED			0x103
#define SPASM_ERR_VALUE_EXPECTED			0x104
#define SPASM_ERR_BAD_VALUE_PREFIX			0x105
#define SPASM_ERR_LABEL_NOT_FOUND			0x106
#define SPASM_ERR_INVALID_ADDRESS			0x107
#define SPASM_ERR_SIZE_MUST_BE_POSITIVE		0x108
#define SPASM_ERR_FILENAME_EXPECTED			0x109
#define SPASM_ERR_INVALID_OPERANDS			0x110
#define SPASM_ERR_UNKNOWN_PREOP				0x111
#define SPASM_ERR_UNKNOWN_DIRECTIVE			0x112
#define SPASM_ERR_UNKNOWN_OPCODE			0x113
#define SPASM_ERR_EQUATE_MISSING_LABEL		0x114
#define SPASM_ERR_EXCEEDED_RECURSION_LIMIT	0x115
#define SPASM_ERR_UNMATCHED_IF				0x116
#define SPASM_ERR_STRAY_PREOP				0x117
#define SPASM_ERR_EXPRESSION_EXPECTED		0x118
#define SPASM_ERR_SYNTAX					0x119
#define SPASM_ERR_JUMP_EXCEEDED				0x120
#define SPASM_ERR_INDEX_OFFSET_EXCEEDED		0x121
#define SPASM_ERR_NAME_EXPECTED				0x122
#define SPASM_ERR_NO_PREVIOUS_DEFINE		0x123
#define SPASM_ERR_ELIF_WITHOUT_IF			0x124
#define SPASM_ERR_INVALID_OPTION			0x125
#define SPASM_ERR_INVALID_ADDINSTR			0x126
#define SPASM_ERR_INVALID_RST_OPERANDS		0x127
#define SPASM_ERR_DEFINE_HAS_NO_VALUE		0x128
#define SPASM_ERR_RECURSION_DEPTH			0x129
#define SPASM_ERR_LABEL_CONFLICT			0x130
#define SPASM_ERR_INVALID_INDEX_OFFSET		0x131

#define SPASM_ERR_INVALID_DECIMAL_DIGIT		0x200
#define SPASM_ERR_INVALID_HEX_DIGIT			0x201
#define SPASM_ERR_INVALID_BINARY_DIGIT		0x202
#define SPASM_ERR_DIVIDE_BY_ZERO			0x203
#define SPASM_ERR_INTEGER_OVERFLOW			0x204
#define SPASM_ERR_DIVIDE_IMIN1				0x205

#define SPASM_ERR_FCREATE_NOFILE			0x301

#define SPASM_ERR_SIGNER_MISSING_LENGTH		0x501
#define SPASM_ERR_SIGNER_PRGM_TYPE			0x502
#define SPASM_ERR_SIGNER_MISSING_PAGES		0x503
#define SPASM_ERR_SIGNER_MISSING_NAME		0x504
#define SPASM_ERR_SIGNER_ROOM_FOR_SIG		0x505


#define SPASM_ERR_CUSTOM					0x600

#define SPASM_WARN_TRUNCATING_8				0x800
#define SPASM_WARN_TRUNCATING_16			0x801
#define SPASM_WARN_SMALL_LAST_PAGE			0x802
#define SPASM_WARN_UNKNOWN_EXTENSION		0x803
#define SPASM_WARN_MACRO_TOO_MANY_ARGS		0x804
#define SPASM_WARN_LABEL_OVER_DEFINE		0x805


#define SPASM_WARN_SIGNER_FILE_SIZE_64KB	0x550
#define SPASM_WARN_SIGNER_FILE_SIZE_24KB	0x551

#ifndef _ERRORS_CPP
extern
#endif
SPASMERROR g_ErrorCodes[]
#ifdef _ERRORS_CPP
=
{
	{SPASM_ERR_FILE_NOT_FOUND,			"Could not find the file '%s'"},
	{SPASM_ERR_NO_ACCESS,				"Could not access the file '%s'"},

	{SPASM_ERR_LOCAL_LABEL_SYNTAX,		"Error in local label's syntax (had leading +/- but no _)"},
	{SPASM_ERR_LOCAL_LABEL_FORWARD_REF,	"Reference to local label which doesn't exist"},
	{SPASM_ERR_ARG_USED_WITHOUT_VALUE,	"Argument '%s' used without value"},
	{SPASM_ERR_OPERATOR_EXPECTED,		"Expecting an operator, found '%c' instead"},
	{SPASM_ERR_VALUE_EXPECTED,			"Expecting a value, expression ended early"},
	{SPASM_ERR_LABEL_NOT_FOUND,			"Could not find label or macro '%s'"},
	{SPASM_ERR_BAD_VALUE_PREFIX,		"Unrecognized value prefix '%c'"},
	{SPASM_ERR_INVALID_ADDRESS,			"The value '%s' is not a valid Z80 address"},
	{SPASM_ERR_SIZE_MUST_BE_POSITIVE,	"The value '%s' is a size and must be positive"},
	{SPASM_ERR_FILENAME_EXPECTED,		"Expecting a filename, none was provided"},
	{SPASM_ERR_INVALID_OPERANDS,		"The opcode %s was given invalid operands"},
	{SPASM_ERR_INVALID_RST_OPERANDS,	"The opcode rst was given invalid operands"},
	{SPASM_ERR_UNKNOWN_PREOP,			"Unknown preprocessor command '#%s'"},
	{SPASM_ERR_UNKNOWN_DIRECTIVE,		"Unknown assembler directive '.%s'"},
	{SPASM_ERR_UNKNOWN_OPCODE,			"Unknown opcode '%s'"},
	{SPASM_ERR_EQUATE_MISSING_LABEL,	"Equate is missing corresponding label"},
	{SPASM_ERR_EXCEEDED_RECURSION_LIMIT,"Recursion depth limit exceeded"},
	{SPASM_ERR_EXPRESSION_EXPECTED,		"Expecting an expression, statement ended early"},
	{SPASM_ERR_SYNTAX,					"Unknown syntax"},
	{SPASM_ERR_JUMP_EXCEEDED,			"Relative jump distance exceeded (distance %d)"},
	{SPASM_ERR_INDEX_OFFSET_EXCEEDED,	"Index register offset exceeded (offset %d)"},
	{SPASM_ERR_NAME_EXPECTED,			"Expecting a name, expression ended early"},
	{SPASM_ERR_NO_PREVIOUS_DEFINE,		"No previous define to continue"},
	{SPASM_ERR_ELIF_WITHOUT_IF,			"Use of #ELIF outside of an #IF expression"},
	{SPASM_ERR_INVALID_OPTION,			"The option %s does not exist"},
	{SPASM_ERR_INVALID_ADDINSTR,		"Required information for .ADDINSTR is missing or invalid"},
	{SPASM_ERR_INVALID_RST_OPERANDS,	"Invalid operands for the RST command"},
	{SPASM_ERR_DEFINE_HAS_NO_VALUE,		"The define '%s' has been used, but doesn't have a value"},
	{SPASM_ERR_RECURSION_DEPTH,			"Expression is too deep (only %d levels allowed)"},
	{SPASM_ERR_LABEL_CONFLICT,			"Conflicting definition of '%s' at %s:%d"},
	{SPASM_ERR_INVALID_INDEX_OFFSET,	"Index offset is expected to begin with '+' or '-' or be missing"},

	{SPASM_ERR_INVALID_DECIMAL_DIGIT,	"Invalid digit '%c' in the decimal number '%s'"},
	{SPASM_ERR_INVALID_HEX_DIGIT,		"Invalid digit '%c' in the hexadecimal number '%s'"},
	{SPASM_ERR_INVALID_BINARY_DIGIT,	"Invalid digit '%c' in the binary number '%s'"},
	{SPASM_ERR_DIVIDE_BY_ZERO,			"Division by zero in evaluation of expression '%s'"},
	{SPASM_ERR_INTEGER_OVERFLOW,		"Magnitude of literal value '%s' is too large"},
	{SPASM_ERR_DIVIDE_IMIN1,			"Division of INT_MIN by -1 in expression '%s' is unrepresentable"},

	{SPASM_ERR_FCREATE_NOFILE,			"No buffer was selected for the fcreate call"},
	{SPASM_ERR_UNMATCHED_IF,			"Unbalanced #IF/#ENDIF"},
	{SPASM_ERR_STRAY_PREOP,				"Stray #%s"},

	{SPASM_ERR_SIGNER_MISSING_LENGTH,	"Length field missing"},
	{SPASM_ERR_SIGNER_PRGM_TYPE,		"Program type field missing or incorrect"},
	{SPASM_ERR_SIGNER_MISSING_PAGES,	"Page count field missing"},
	{SPASM_ERR_SIGNER_MISSING_NAME,		"Name field missing"},
	{SPASM_ERR_SIGNER_ROOM_FOR_SIG,		"Not enough room for signature on last page"},

	{SPASM_ERR_CUSTOM,					"%s"},

	{SPASM_WARN_TRUNCATING_8,			"Value too large for 8-bits, truncation required"},
	{SPASM_WARN_TRUNCATING_16,			"Value too large for 16-bits, truncation required"},
	{SPASM_WARN_SMALL_LAST_PAGE,		"Only %d bytes are used on the last APP page"},
	{SPASM_WARN_UNKNOWN_EXTENSION,		"Unrecognized file extension, assuming binary"},
	{SPASM_WARN_MACRO_TOO_MANY_ARGS,	"Macro '%s' was given too many arguments, ignoring extras"},
	{SPASM_WARN_LABEL_OVER_DEFINE,		"Label %s was used instead define %s"},

	{SPASM_WARN_SIGNER_FILE_SIZE_24KB,	"The output file is larger than 24KB"},
	{SPASM_WARN_SIGNER_FILE_SIZE_64KB,	"The output file is larger than 64KB"},
}
#endif
;

void SetLastSPASMError(int32_t dwErrorCode, ...);
void SetLastSPASMWarning(int32_t dwErrorCode, ...);
//int32_t GetLastSPASMError();
int StartSPASMErrorSession(void);
int GetSPASMErrorSessionErrorCount(int nSession);
bool IsSPASMErrorSessionFatal(int nSession);
void ReplaySPASMErrorSession(int nSession, bool fFatalOnly = false);
void ReplayFatalSPASMErrorSession(int nSession);
void EndSPASMErrorSession(int errors);
void ClearSPASMErrorSessions();
int CleanupSPASMErrorSession(int nSession);
void AddSPASMErrorSessionAnnotation(int nSession, const char *lpszFormat, ...);
bool IsErrorInSPASMErrorSession(int nSession, uint32_t dwErrorCode);
void FreeSPASMErrorSessions(void);
#ifdef _TEST
uint32_t GetLastSPASMError();
int GetLastSPASMErrorLine();
#endif
