#include "mips_base.h"
#include "mips_instr.h"

void add_instr(int rd, int rs, int rt)
{
    writeReg(rd, rs + rt);
}

void sub_instr(int rd, int rs, int rt)
{
    writeReg(rd, rs - rt);
}

void and_instr(int rd, int rs, int rt)
{
    writeReg(rd, rs & rt);
}

void or_instr(int rd, int rs, int rt)
{
    writeReg(rd, rs | rt);
}

void slt_instr(int rd, int rs, int rt)
{
    writeReg(rd, rs < rt);
}

void beq_instr(int rs, int rt, Label label)
{
    if (rs == rt) nextInstr = label.location;
}

void j_instr(Label label)
{
    nextInstr = label.location;
}

int lw_instr (int addr)
{
	return mem[addr];
}

int sw_instr (int addr, int data)
{
	mem[addr] = data;
}