#include "mips_base.h"

#ifndef MIPS_PARSER_H
#define MIPS_PARSER_H

int label_address(const char *name);
void run_file (const char *filename);
void parse_file (const char *filename);
void parse_line (const char *line);
void parse_labels (const char *line);
void parse_instruction (char* line);

extern Label labels[LABEL_SIZE];

#endif
