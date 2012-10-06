#include <stdlib.h>
#include <stdio.h>

#include "config.h"
#include "mips_base.h"
#include "mips_instr.h"

void add_instr (int rd, int rs, int rt)
{
    writeReg(rd, rs + rt);
}

void sub_instr (int rd, int rs, int rt)
{
    writeReg(rd, rs - rt);
}

void and_instr (int rd, int rs, int rt)
{
    writeReg(rd, rs & rt);
}

void or_instr (int rd, int rs, int rt)
{
    writeReg(rd, rs | rt);
}

void slt_instr (int rd, int rs, int rt)
{
    writeReg(rd, rs < rt);
}

void beq_instr (int rs, int rt, int pos)
{
    if (rs == rt) pc = pos;
}

void j_instr (int pos)
{
    pc = pos;
}

void jal_instr (int pos)
{
    writeReg(REG_RA, pc);
    pc = pos;
}

void jr_instr (int pos)
{
    pc = pos;
}

void lw_instr (int toreg, int addr)
{
	writeReg(toreg, mem[addr]);
}

void la_instr (int rd, int addr)
{
    writeReg(rd, mem[addr]);
}

void sw_instr (int data, int addr)
{
	mem[addr] = data;
}

void syscall_instr ()
{
    int service = reg[REG_V0];

    switch (service)
    {
        // Print integer
        case 1:
	        printf("%d", reg[REG_A0]);
	        break;

        // Read integer
        case 5:
            scanf("%i", &reg[REG_V0]);
            break;

        // Exit
        case 10:
            exit(reg[REG_A0]);
            break;
    }
}
