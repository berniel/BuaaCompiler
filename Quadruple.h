#ifndef QUADRUPLE_H_INCLUDED
#define QUADRUPLE_H_INCLUDED
#define MAXInstruL 10000
extern TableEle* src1;
extern TableEle* src2;
extern TableEle* des;
extern FILE *output_quadruple_pointer;
extern int ins_num;
enum Instr{
    NEG = 1, ADD, SUB, MUL, DIV,
    LS, BG, NLS, NBG, EQU,
    NEQ, ASN, GLV, GLC, FDCL,
    MDCL, END, RRT, VRT, LAB,
    GOTO, TGOTO, NGOTO, CALL, PUSH,
    MFF, LFA, STA, RD, WRS,
    WRC, WRI, MEND
};
typedef struct Q{
    int ins;
    TableEle* src1;
    TableEle* src2;
    TableEle* des;
} Quadruple;

Quadruple quad[MAXInstruL];

void write_quadruple(int instr);
void write_quadruple_s(int instr, TableEle* des);
void write_quadruple_d(int instr, TableEle* src1, TableEle* des);
void write_quadruple_t(int instr, TableEle* src1, TableEle* src2, TableEle* des);
#endif // QUADRUPLE_H_INCLUDED
