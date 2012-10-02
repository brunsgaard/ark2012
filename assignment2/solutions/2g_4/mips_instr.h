#include "mips_base.h"

#ifndef MIPS_INSTR_H
#define MIPS_INSTR_H

void add_instr (int rd, int rs, int rt);
void sub_instr (int rd, int rs, int rt);
void and_instr (int rd, int rs, int rt);
void or_instr (int rd, int rs, int rt);
void slt_instr (int rd, int rs, int rt);
void beq_instr (int rs, int rt, Label label);
void j_instr (Label label);
int lw_instr (int addr);
void sw_instr (int addr, int data);
void syscall_instr ();

#else
#endif
