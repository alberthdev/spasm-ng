#ifndef __PASS_ONE_H
#define __PASS_ONE_H

typedef enum {
	SUFFIX_L = 1,
	SUFFIX_IL = 2
} suffix_type;

void run_first_pass (char *ptr);
char *run_first_pass_line (char *ptr);
int write_out (int);
char *handle_opcode_or_macro (char *ptr);
void do_listing_for_line (char *ptr);

extern bool adl_mode;

#endif
