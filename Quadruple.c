#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "getSym.h"
#include "SymbolTable.h"
#include "error.h"
#include "grammar.h"
#include "Quadruple.h"
FILE *output_quadruple_pointer;
int ins_num = 0;
void write_quadruple_t(int instr, TableEle* src1, TableEle* src2, TableEle* des){
    quad[ins_num].ins = instr;
    quad[ins_num].src1 = src1;
    quad[ins_num].src2 = src2;
    quad[ins_num].des = des;
    ins_num++;
    fprintf(output_quadruple_pointer,"%d:\t%d\t%s\t%s\t%s\n",ins_num,instr,src1->name,src2->name,des->name);
}
void write_quadruple_d(int instr, TableEle* src1, TableEle* des){
    quad[ins_num].ins = instr;
    quad[ins_num].src1 = src1;
    quad[ins_num].des = des;
    ins_num++;
    fprintf(output_quadruple_pointer,"%d:\t%d\t%s\t\t\t%s\n",ins_num,instr,src1->name,des->name);
}
void write_quadruple_s(int instr, TableEle* des){
    quad[ins_num].ins = instr;
    quad[ins_num].des = des;
    ins_num++;
    fprintf(output_quadruple_pointer,"%d:\t%d\t\t\t\t%s\n",ins_num,instr,des->name);
}
void write_quadruple(int instr){
    quad[ins_num].ins = instr;
    ins_num++;
    fprintf(output_quadruple_pointer,"%d:\t%d\t\t\t\t\t\t\n",ins_num,instr);
}
