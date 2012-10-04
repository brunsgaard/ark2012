#ifndef MIPS_PARSER_H
#define MIPS_PARSER_H

void run_file (const char *filename);
void parse_file (const char *filename);
void parse_line (const char *line);
char *parse_labels (char *line);
void parse_instruction (char* line);

#endif
