#include "stdafx.h"

#define __PARSER_C

//max depth of #defines
#define RECURSION_LIMIT 20

#include "spasm.h"
#include "parser.h"
#include "storage.h"
#include "utils.h"
#include "preop.h"
#include "errors.h"

			//case '+': total += last_num; break;
			//case '-': total -= last_num; break;
			//case '*': total *= last_num; break;
			//case '/': total /= last_num; break;
			//case '%': total %= last_num; break;
			//case '^': total ^= last_num; break;
			//case '&': total &= last_num; break;
			//case '|': total |= last_num; break;
			//case '<': total <<= last_num; break;
			//case '>': total >>= last_num; break;

typedef enum tagMATHOP
{
	// Math
	M_ADD,
	M_SUB,
	M_MUL,
	M_DIV,
	M_MOD,
	M_XOR,
	M_LAND,
	M_LOR,
	M_LSHIFT,
	M_RSHIFT,

	// Conditions
	M_AND,
	M_OR,
	M_LTE,
	M_GTE,
	M_LT,
	M_GT,
	M_EQUALS,
	M_NOTEQUALS,

	// 
	M_NONE,
}
MATHOP;

static const struct tagMATHOPDEF
{
	MATHOP Op;
	const char *szDef;
}
MathDefs[] =
{
	{M_LSHIFT, "<<"},
	{M_RSHIFT, ">>"},

	// Conditions
	{M_AND, "&&"},
	{M_OR, "||"},
	{M_LTE, "<="},
	{M_GTE, ">="},
	{M_LT, "<"},
	{M_GT, ">"},
	{M_EQUALS, "=="},
	{M_EQUALS, "="},
	{M_NOTEQUALS, "!="},

	// Math
	{M_ADD, "+"},
	{M_SUB, "-"},
	{M_MUL, "*"},
	{M_DIV, "/"},
	{M_MOD, "%"},
	{M_XOR, "^"},
	{M_LAND, "&"},
	{M_LOR, "|"},
};


extern char *curr_input_file;
extern int line_num;
extern bool error_occurred;
extern bool pass_one;
extern unsigned int program_counter;

static const char *parse_single_num (const char *expr, int *value);
static const char *parse_num_full (const char *expr, int *value, int depth);
static bool conv_dec (const char* str, const char *end, int *output);
static bool conv_bin (const char* str, const char *end, int *output);

//set when the parser hits an undefined #define or label
bool parser_forward_ref_err;
//current recursive depth in expression
int parse_depth;

/*
 * Parses an expression, sets
 * the result in value and
 * returns TRUE if successful,
 * otherwise sets value to 0
 * and returns FALSE
 */

bool parse_num (const char *expr, int *value) {
	int fake_value;
	const char *result;

	if (value == NULL)
		value = &fake_value;

	parse_depth = 0;
	result = parse_num_full (expr, value, 0);

	if (!result)
		*value = 0;

	return (result != NULL);
}

/*
 * Parses expression,
 * ignoring errors
 */

int parse_f (const char *expr) {
	int result;
	int session = StartSPASMErrorSession();
	if (!(parse_num (expr, &result)))
		result = -1;

	if (IsSPASMErrorSessionFatal(session) == true)
	{
		result = -1;
	}

	EndSPASMErrorSession(session);
	return result;
}


/*
 * Parses the contents of a define,
 * handling preops, and returns
 * the first line with a value,
 * allocated
 */

char *parse_define (define_t *define)
{
	char *curr_line = define->contents;
	char *lpszResult = NULL;

	while (curr_line != NULL && *curr_line && !error_occurred) {
		char *next_line = curr_line;
		curr_line = skip_whitespace(curr_line);
		if (*curr_line == '#')
		{
			next_line = handle_preop(curr_line + 1);
		}
		else if (is_end_of_code_line(curr_line) == false)
		{
			//otherwise, it must be a value, so return that
			lpszResult = strndup(curr_line, skip_to_code_line_end(curr_line) - curr_line);
			break;
		}

		curr_line = next_code_line(next_line);
		line_num++;
	}

	return lpszResult;
}


/*
 * Parses a single number, sets
 * the value, and returns the
 * end of the number
 */

static const char *parse_single_num (const char *expr, int *value) {

	switch (*expr) {
#ifdef USE_REUSABLES
		case '+':
		//case '_':
		{
			//Local label!
			int this_reusable = get_curr_reusable();
			while (*expr == '+')
			{
				expr++;
				this_reusable++;
			}

			if (*(expr++) != '_')
			{
				SetLastSPASMError(SPASM_ERR_LOCAL_LABEL_SYNTAX);
				return NULL;
			}
			else if (this_reusable >= get_num_reusables())
			{
				SetLastSPASMError(SPASM_ERR_LOCAL_LABEL_FORWARD_REF);
				return NULL;
			}
			else
			{
				*value = search_reusables(this_reusable);
			}
			break;

		}
		case '-':
		{
			//Again, a local label!
			int this_reusable = get_curr_reusable();
			if (*expr == '-') expr++;
			
			while (*expr == '-' && this_reusable > 0) {
				expr++;
				this_reusable--;
			}
	
			if (*(expr++) != '_' || this_reusable < 0)
			{
				SetLastSPASMError(SPASM_ERR_LOCAL_LABEL_SYNTAX);
				return NULL;
			}
	
			*value = search_reusables(this_reusable);
			break;

		}
#endif
		//If the number has a prefix it's easy to tell what the type is!
		case '$':
		{
			const char *num_start = ++expr;
			//Could be a hex number (ld hl,$1A2F) or the current address (ld hl,$)
			if (isxdigit ((unsigned char) *expr)) {
				while (isalnum(*expr))
					expr++;
				bool success = conv_hex (num_start, expr, value);
				if (!success)
				{
					return NULL;
				}
			} else
				//TODO: This is questionable behavior.  It should probably check specifically for $
				*value = program_counter;
			break;
	
		}
		case '%':
		{
			const char *num_start = ++expr;
			while (isalnum(*expr))
				expr++;
			bool succeeded = conv_bin (num_start, expr, value);
			if (!succeeded)
			{
				return NULL;
			}
			break;

		}
		//Handle literal chars in single quotes
		case '\'':
		{
			*value = *(++expr);
			if (*value == '\\') {
				switch (toupper (*(++expr))) {
					case 'N': 	*value = '\n'; break;
					case '\\': 	*value = '\\'; break;
					case '0': 	*value = '\0'; break;
					case 'R': 	*value = '\r'; break;
					case 'T': 	*value = '\t'; break;
					case '\'': 	*value = '\''; break;
					case '#': 	*value = rand () & 0xFF; break;
					default: 	*value = *expr;
				}
			}

			if (*(++expr) != '\'') {
				show_warning ("Literal char is missing single quote at end");
			} else {
				expr++;
			}

			break;

		}
		//By now, it's either a label, number, or macro
		default:
			if (isalpha ((unsigned char) *expr) || *expr == '_') {
				//If it starts with a letter or underscore, it's a label or a macro that returns a value
				label_t *label = NULL;
				define_t *define = NULL;
				char *name;

				const char *expr_start = expr;
				//Find the end of the name, then try it as a label first
				expr = skip_to_name_end (expr_start);
				name = strndup (expr_start, expr - expr_start);
				
				define = search_local_defines(name);
				if (define == NULL) {
					label = search_labels(name);
					if (label == NULL) {
						define = search_defines(name);
					}
				}
				
				//see if it's a local label
				if (!strcmp (name, "_")) {
					free (name);
					if (get_curr_reusable() + 1 < get_num_reusables())
					{
						*value = search_reusables(get_curr_reusable() + 1);
					}
					else
					{
						SetLastSPASMError(SPASM_ERR_LOCAL_LABEL_FORWARD_REF);
						return NULL;
					}
				}
				else if (label != NULL) {
						*value = label->value;
						free (name);
						//or the "eval" macro
					} else if (!strcasecmp (name, "eval") && *expr == '(') {
						free(name);
						//show_warning ("eval() has no effect except in #define");
						expr = parse_num_full (expr, value, 0);
						//then a normal label
					}
					else if (!strcasecmp (name, "getc") && *expr == '(')
					{
						char filename[256];
						FILE *temp_file;
						define_t *define;
						int char_index;
						char parse_buf[256];
						char *rfn;

						free(name);

						expr++;
						read_expr(&expr, filename, ",");

						// Is the filename given a macro?
						if ((define = search_defines (filename)))
						{
							strncpy (filename, define->contents, sizeof (filename));
						}

						read_expr (&expr, parse_buf, ",");
						char_index = parse_f (parse_buf);

						rfn = fix_filename (reduce_string (filename));
						if ((temp_file = fopen (rfn, "r"))) {
							fseek (temp_file, char_index, SEEK_SET);
							*value = fgetc (temp_file);
							fclose (temp_file);
						} else {
							SetLastSPASMError(SPASM_ERR_FILE_NOT_FOUND, filename);
						}

						if (*expr == ')') expr++;
						//If that didn't work, see if it's a macro
					}
					else if (define)
					{
						list_t *args = NULL;
						char *contents;

						free (name);

						expr = parse_args (expr, define, &args);
						if (!expr)
							return NULL;

						bool fHasError = false;
						int old_line_num = line_num;
						line_num = define->line_num;

						int session = StartSPASMErrorSession();
						contents = parse_define (define);
						if (contents == NULL)
						{
							SetLastSPASMError(SPASM_ERR_ARG_USED_WITHOUT_VALUE, define->name);
						}
						else
						{
							parse_num_full(contents, value, 0);
							free(contents);
						}

						line_num = old_line_num;

						if (GetSPASMErrorSessionErrorCount(session) > 0)
						{
							AddSPASMErrorSessionAnnotation(session, _T("Error during evaluation of macro '%s'"), define->name);
							ReplaySPASMErrorSession(session);
							fHasError = true;
						}
						EndSPASMErrorSession(session);

						remove_arg_set (args);
						if (fHasError == true)
						{
							return NULL;
						}
					}
					else
					{
						SetLastSPASMError(SPASM_ERR_LABEL_NOT_FOUND, name);
						parser_forward_ref_err = true;
						free (name);
						return NULL;
					}

			} else if (isdigit ((unsigned char) *expr)) {
				const char *expr_start = expr;
				//Find the end of the number
				while (isalnum ((unsigned char) expr[1])) expr++;

				bool success;
				switch (toupper (expr[0])) {
		case 'H':	success = conv_hex (expr_start, expr++, value);	break;
		case 'B':	success = conv_bin (expr_start, expr++, value); break;
		case 'D':	success = conv_dec (expr_start, expr++, value); break;
		default:	success = conv_dec (expr_start, ++expr, value); break;
				}

				if (!success)
				{
					return NULL;
				}

			} else {
				SetLastSPASMError(SPASM_ERR_BAD_VALUE_PREFIX, *expr);
				return NULL;
			}
			break;
	}

	return expr;
}


/*
 * Skips until the next &&, ||,
 * <, >, ==, !=, <=, or >=, and
 * returns a pointer to it
 */

const char *find_next_condition (const char *ptr) {
	int depth = 0;
	while (!is_end_of_code_line (ptr)) {
		if (depth == 0 &&
			(((*ptr == '&' || *ptr == '|') && *(ptr + 1) == *ptr)
			|| *ptr == '=' || *ptr == '!' ||
			((*ptr == '<' || *ptr == '>') && *(ptr + 1) != *ptr)))
			break;
		switch (*ptr) {
			case '(': depth++; break;
			case ')':
				depth--;
				if (depth < 0) return ptr;
				break;
			case '\'':
				ptr++;
				if (*ptr == '\\') ptr++;
				if (*ptr) ptr++;
				break;
		}
		ptr++;
	}
	return ptr;
}


/*
 * Evaluates the expression in expr, sets value to result, returns
 * pointer to end of expression (if depth > 0) or NULL on error.
 */

static const char *parse_num_full (const char *expr, int *value, int depth) {
	int total = 0, last_num;
	MATHOP last_op = M_NONE;
	bool invert_lastnum, neg_lastnum;
	const char *const expr_start = expr;

	parser_forward_ref_err = false;
	if (++parse_depth > RECURSION_LIMIT)
	{
		SetLastSPASMError(SPASM_ERR_EXCEEDED_RECURSION_LIMIT);
		return NULL;
	}

	expr = skip_whitespace (expr);
	if (!(*expr))
	{
		SetLastSPASMError(SPASM_ERR_VALUE_EXPECTED);
		return NULL;
	}

	//Now loop through the whole expression
	for (;;)
	{

		//First look for numbers
		invert_lastnum = neg_lastnum = false;

		//Catch any invert symbols before the number
		if (*expr == '~') {
			invert_lastnum = true;
			expr = skip_whitespace (expr + 1);
		//Same with +/- signs, unless it's a local label
		} else if ((*expr == '-' || *expr == '+') && expr[1] != *expr &&
			   (expr[1] != '_' || skip_to_name_end (expr + 1) != expr + 2)) {
			neg_lastnum = expr[0] == '-';
			expr = skip_whitespace (expr + 1);
		}

		//If it's a parenthesis, evaluate the stuff inside there
		if (*expr == '(') {
			expr = parse_num_full (++expr, &last_num, depth + 1);
			//If there was an error in that expression, then abort
			if (!expr)
				return NULL;
		//Otherwise it's just a normal value
		} else {
			expr = parse_single_num (expr, &last_num);
			if (!expr)
				return NULL;
		}

		if (invert_lastnum)
			last_num = ~last_num;
		if (neg_lastnum)
			last_num = -last_num;

		// Guard against divide by zero
		if ((last_op == M_DIV || last_op == M_MOD) && last_num == 0) {
			SetLastSPASMError(SPASM_ERR_DIVIDE_BY_ZERO, expr_start);
			return NULL;
		}
		// Also INT_MIN / -1 and friends
		if ((last_op == M_DIV || last_op == M_MOD) && total == INT_MIN && last_num == -1) {
			SetLastSPASMError(SPASM_ERR_DIVIDE_IMIN1, expr_start);
			return NULL;
		}

		//Now check on the last operator to see what to do with this number
		switch (last_op) {
			case M_NONE:
				//Special case for the first number in the expression
				total = last_num; break;

			// Math
			case M_ADD: total += last_num; break;
			case M_SUB: total -= last_num; break;
			case M_MUL: total *= last_num; break;
			case M_DIV: total /= last_num; break;
			case M_MOD: total %= last_num; break;
			case M_XOR: total ^= last_num; break;
			case M_LAND: total &= last_num; break;
			case M_LOR: total |= last_num; break;
			case M_LSHIFT: total <<= last_num; break;
			case M_RSHIFT: total >>= last_num; break;

			// Condition
			case M_AND: total = total && last_num; break;
			case M_OR: total = total || last_num; break;
			case M_LT: total = total < last_num; break;
			case M_GT: total = total > last_num; break;
			case M_LTE: total = total <= last_num; break;
			case M_GTE: total = total >= last_num; break;
			case M_EQUALS: total = total == last_num; break;
			case M_NOTEQUALS: total = total != last_num; break;
		}

		//Get the next operator
	get_op:
		expr = skip_whitespace (expr);
		//If it's the end of the expression, return the total so far
		if (is_end_of_code_line (expr)) {
			if (depth > 0)
				show_warning ("Missing %d parentheses at end of expression", depth);
			*value = total;
			parse_depth--;
			return expr;
		}

		last_op = M_NONE;
		for (int i = 0; i < ARRAYSIZE(MathDefs); i++)
		{
			if (strncmp(expr, MathDefs[i].szDef, strlen(MathDefs[i].szDef)) == 0)
			{
				last_op = MathDefs[i].Op;
				expr += strlen(MathDefs[i].szDef);
				break;
			}
		}

		if (last_op != M_NONE)
		{
		}
		else if (*expr == ')') {
			if (depth > 0) {
				// We've been parsing an expression in parentheses and reached the end,
				// so return the result and go up a level again
				*value = total;
				expr = skip_whitespace (expr + 1);
				parse_depth--;
				return expr;
			} else {
				//Otherwise it's just an extra parenthesis
				show_warning ("Extra parenthesis found, ignoring it");
				expr++;
				goto get_op;
			}

		} else {
			SetLastSPASMError(SPASM_ERR_OPERATOR_EXPECTED, *expr);
			return NULL;
		}

		//Skip any whitespace after the operator
		expr = skip_whitespace (expr);
		if (*expr == '\0') {
			SetLastSPASMError(SPASM_ERR_VALUE_EXPECTED);
			return NULL;
		}
	}
}

/*
 * General form of numeric literal conversion.
 * 
 * Writes the integer form of the value between `str` and `end` to `output_num`,
 * parsed in base `base` and yielding SPASM error `error_code` in case of invalid
 * characters.
 *
 * Returns true if successful, false otherwise.
 */
static bool conv_generic(const char *str, const char *end, int *output_num,
                  int base, int error_code) {
	char *ep;
	long value = strtol(str, &ep, base);

	if (ep < end) {
		char *number = strndup(str, end - str);
		SetLastSPASMError(error_code, *ep, number);
		free(number);
		return false;
	}

	if (value < INT_MIN || value > INT_MAX) {
		char *number = strndup(str, end - str);
		SetLastSPASMError(SPASM_ERR_INTEGER_OVERFLOW, number);
		free(number);
		return false;
	}
		
	*output_num = (int)value;
	return true;
}

bool conv_hex (const char* str, const char *end, int *output_num) {
	return conv_generic(str, end, output_num, 16, SPASM_ERR_INVALID_HEX_DIGIT);
}

static bool conv_dec (const char* str, const char *end, int *output_num) {
	return conv_generic(str, end, output_num, 10, SPASM_ERR_INVALID_DECIMAL_DIGIT);
}

static bool conv_bin (const char* str, const char *end, int *output_num) {
	return conv_generic(str, end, output_num, 2, SPASM_ERR_INVALID_BINARY_DIGIT);
}

