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
    if (rs == rt) pc = label.location;
}

void j_instr(Label label)
{
    pc = label.location;
}

void lw_instr (int toreg, int addr)
{
	writeReg(toreg, mem[addr]);
}

void sw_instr (int addr, int data)
{
	mem[addr] = data;
}

void syscall_instr()
{
	//TODO: not implemented
}