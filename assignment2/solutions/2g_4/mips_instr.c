//#include "mips_base.h"
#include "mips_instr.h"

void add_instr(int rd, int rs, int rt)
{
    reg[rd] = rs + rt;
}

void sub_instr(int rd, int rs, int rt)
{
    reg[rd] = rs - rt;
}

void and_instr(int rd, int rs, int rt)
{
    reg[rd] = rs & rt;
}

void or_instr(int rd, int rs, int rt)
{
    reg[rd] = rs | rt;
}

void slt_instr(int rd, int rs, int rt)
{
    reg[rd] = rs < rt;
}

//void beq_instr(int rs, int rt, Label label)
//{
//    if (reg[rs] == reg[rt]) reg[31] = 1;
//}
//
//void j_instr(Label label)
//{
//    reg[31] = 1;
//}

