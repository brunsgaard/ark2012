#include "mips_base.h"

#ifndef MIPS_INSTR_H
#define MIPS_INSTR_H

void add_instr (int rd, int rs, int rt);
void sub_instr (int rd, int rs, int rt);
void and_instr (int rd, int rs, int rt);
void or_instr (int rd, int rs, int rt);
void slt_instr (int rd, int rs, int rt);
void lw_instr (int rd, int addr);
void la_instr (int rd, int addr);
void sw_instr (int addr, int data);
void beq_instr (int rs, int rt, int pos);
void j_instr (int pos);
void jr_instr (int pos);
void jal_instr(int pos);
void syscall_instr ();

#endif
