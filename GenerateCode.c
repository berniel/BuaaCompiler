#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "getSym.h"
#include "SymbolTable.h"
#include "Quadruple.h"
int start;
int page_size = 256;
FILE* output_code_pointer;

void generate_load_ele(TableEle *te, char rsl[], char t[]){
    char temp[MAXTokenL];
    if(te->kind == GLOVAR || te->kind == GLOCON){
        strcpy(rsl,"lw\t");
        strcat(rsl,t);
        strcat(rsl,"\t");
        strcat(rsl,te->name);
        strcat(rsl,"\n");
    }
    else if(te->kind == VAR || te->kind == PARA || te->kind == TMPVAR){
        strcpy(rsl,"lw\t");
        strcat(rsl,t);
        strcat(rsl,"\t");
        itoa(page_size-44-te->addr,temp,10);
        strcat(rsl,temp);
        strcat(rsl,"($sp)\n");
        //printf("%d\n", page_size-44-te->addr);
    }
    else if(te->kind == CONST || te->kind == TMPCON){
        strcpy(rsl,"li\t");
        strcat(rsl,t);
        strcat(rsl,"\t");
        itoa(te->addr,temp,10);
        //if(te->kind == TMPCON && te->type == CHAR)
            //printf("%d, %c\n", te->addr, te->addr);
        strcat(rsl,temp);
        strcat(rsl,"\n");
    }
    //else printf("load : %d\n", te->kind);
    fprintf(output_code_pointer,"#load\n");
}
void generate_save_ele(TableEle *te, char rsl[], char t[]){
    char temp[MAXTokenL];
    //printf("%s %d\n",te->name, te->kind);
    if(te->kind == GLOVAR){
        //printf("%s\n",te->name);
        strcpy(rsl,"sw\t");
        strcat(rsl,t);
        strcat(rsl,"\t");
        strcat(rsl,te->name);
        strcat(rsl,"\n");
    }
    else{
        strcpy(rsl,"sw\t");
        strcat(rsl,t);
        strcat(rsl,"\t");
        //printf("%d\n", te->addr);
        itoa(page_size-44-te->addr,temp,10);
        strcat(rsl,temp);
        strcat(rsl,"($sp)\n");
       // if(te->addr == 1){
      //      printf("%d\n",te->kind);
        //}
    }
    fprintf(output_code_pointer,"#save\n");
}
void generate_glc(int index){
    TableEle* te = quad[index].des;
    fprintf(output_code_pointer,"%s:\t.word\t%d\n",te->name,te->addr);
    fprintf(output_code_pointer,"#Global const declare\n");
}
void generate_glv(int index){
    TableEle* te = quad[index].des;
    if(te->kind != GLOARR)
        fprintf(output_code_pointer,"%s:\t.word\t0\n\t",te->name);
    else
        fprintf(output_code_pointer,"%s:\t.space\t%d\n",te->name,te->length*4);
    fprintf(output_code_pointer,"#Global var declare\n");
}
void generate_fdcl(int index){
    TableEle *te = quad[index].des;
    int addr = page_size-44;
    int i = 0, j = 0, para_num = 0;
    if(start == 0){
        start = 1;
        fprintf(output_code_pointer,".text:\n");
        fprintf(output_code_pointer,"j main\n");
    }
    fprintf(output_code_pointer,"%s:\n",te->name);
    fprintf(output_code_pointer,"addiu\t$sp\t$sp\t%d\n",-1*page_size);
    fprintf(output_code_pointer,"sw\t$ra\t%d($sp)\n",page_size-4);
    fprintf(output_code_pointer,"sw\t$fp\t%d($sp)\n",page_size-8);
    fprintf(output_code_pointer,"addiu\t$t0\t$sp\t-8\n");
    fprintf(output_code_pointer,"add\t$fp\t$t0\t$0\n");
    for(i = 3;i < 11; i++){
        fprintf(output_code_pointer,"sw\t$s%d\t%d($sp)\n",i-3,page_size-4*i);
    }
    fprintf(output_code_pointer,"#Function declare\n");
}
void generate_neg(int index){
    TableEle *te = quad[index].des;
    TableEle *te1 = quad[index].src1;
    char ins[MAXInstruL]="\0";
    generate_load_ele(te1,ins,"$t0");
    fprintf(output_code_pointer,ins);
    fprintf(output_code_pointer,"neg\t$t1\t$t0\n");
    generate_save_ele(te,ins,"$t1");
    fprintf(output_code_pointer,ins);
    fprintf(output_code_pointer,"#Neg\n");
}
void generate_add(int index){
    TableEle *te = quad[index].des;
    TableEle *te1 = quad[index].src1;
    TableEle *te2 = quad[index].src2;
    char ins[MAXInstruL]="\0";
    generate_load_ele(te1,ins,"$t0");
    fprintf(output_code_pointer,ins);
    generate_load_ele(te2,ins,"$t1");
    fprintf(output_code_pointer,ins);
    fprintf(output_code_pointer,"add\t$t2\t$t0\t$t1\n");
    generate_save_ele(te,ins,"$t2");
    fprintf(output_code_pointer,ins);
    fprintf(output_code_pointer,"#Add\n");
}
void generate_sub(int index){
    TableEle *te = quad[index].des;
    TableEle *te1 = quad[index].src1;
    TableEle *te2 = quad[index].src2;
    char ins[MAXInstruL]="\0";
    generate_load_ele(te1,ins,"$t0");
    fprintf(output_code_pointer,ins);
    generate_load_ele(te2,ins,"$t1");
    fprintf(output_code_pointer,ins);
    fprintf(output_code_pointer,"sub\t$t2\t$t0\t$t1\n");
    generate_save_ele(te,ins,"$t2");
    fprintf(output_code_pointer,ins);
    fprintf(output_code_pointer,"#Sub\n");
}
void generate_mul(int index){
    TableEle *te = quad[index].des;
    TableEle *te1 = quad[index].src1;
    TableEle *te2 = quad[index].src2;
    char ins[MAXInstruL]="\0";
    generate_load_ele(te1,ins,"$t0");
    fprintf(output_code_pointer,ins);
    generate_load_ele(te2,ins,"$t1");
    fprintf(output_code_pointer,ins);
    fprintf(output_code_pointer,"mul\t$t2\t$t0\t$t1\n");
    generate_save_ele(te,ins,"$t2");
    fprintf(output_code_pointer,ins);
    fprintf(output_code_pointer,"#Mul\n");
}
void generate_div(int index){
    TableEle *te = quad[index].des;
    TableEle *te1 = quad[index].src1;
    TableEle *te2 = quad[index].src2;
    char ins[MAXInstruL]="\0";
    generate_load_ele(te1,ins,"$t0");
    fprintf(output_code_pointer,ins);
    generate_load_ele(te2,ins,"$t1");
    fprintf(output_code_pointer,ins);
    fprintf(output_code_pointer,"div\t$t2\t$t0\t$t1\n");
    generate_save_ele(te,ins,"$t2");
    fprintf(output_code_pointer,ins);
    fprintf(output_code_pointer,"#Div\n");
}
void generate_bg(int index){
    TableEle *te = quad[index].des;
    TableEle *te1 = quad[index].src1;
    TableEle *te2 = quad[index].src2;
    char ins[MAXInstruL]="\0";
    generate_load_ele(te1,ins,"$t0");
    fprintf(output_code_pointer,ins);
    generate_load_ele(te2,ins,"$t1");
    fprintf(output_code_pointer,ins);
    fprintf(output_code_pointer,"slt\t$t2\t$t1\t$t0\n");
    generate_save_ele(te,ins,"$t2");
    fprintf(output_code_pointer,ins);
    fprintf(output_code_pointer,"#Bigger than\n");
}
void generate_ls(int index){
    TableEle *te = quad[index].des;
    TableEle *te1 = quad[index].src1;
    TableEle *te2 = quad[index].src2;
    char ins[MAXInstruL]="\0";
    generate_load_ele(te1,ins,"$t0");
    fprintf(output_code_pointer,ins);
    generate_load_ele(te2,ins,"$t1");
    fprintf(output_code_pointer,ins);
    fprintf(output_code_pointer,"slt\t$t2\t$t0\t$t1\n");
    generate_save_ele(te,ins,"$t2");
    fprintf(output_code_pointer,ins);
    fprintf(output_code_pointer,"#Less than\n");
}
void generate_nls(int index){
    TableEle *te = quad[index].des;
    TableEle *te1 = quad[index].src1;
    TableEle *te2 = quad[index].src2;
    char ins[MAXInstruL]="\0";
    generate_load_ele(te1,ins,"$t0");
    fprintf(output_code_pointer,ins);
    generate_load_ele(te2,ins,"$t1");
    fprintf(output_code_pointer,ins);
    fprintf(output_code_pointer,"sge\t$t2\t$t0\t$t1");
    generate_save_ele(te,ins,"$t2");
    fprintf(output_code_pointer,ins);
    fprintf(output_code_pointer,"#No less than\n");
}
void generate_nbg(int index){
    TableEle *te = quad[index].des;
    TableEle *te1 = quad[index].src1;
    TableEle *te2 = quad[index].src2;
    char ins[MAXInstruL]="\0";
    generate_load_ele(te1,ins,"$t0");
    fprintf(output_code_pointer,ins);
    generate_load_ele(te2,ins,"$t1");
    fprintf(output_code_pointer,ins);
    fprintf(output_code_pointer,"sle\t$t2\t$t0\t$t1");
    generate_save_ele(te,ins,"$t2");
    fprintf(output_code_pointer,ins);
    fprintf(output_code_pointer,"#No bigger than\n");
}
void generate_equ(int index){
    TableEle *te = quad[index].des;
    TableEle *te1 = quad[index].src1;
    TableEle *te2 = quad[index].src2;
    char ins[MAXInstruL]="\0";
    generate_load_ele(te1,ins,"$t0");
    fprintf(output_code_pointer,ins);
    generate_load_ele(te2,ins,"$t1");
    fprintf(output_code_pointer,ins);
    fprintf(output_code_pointer,"seq\t$t2\t$t0\t$t1\n");
    generate_save_ele(te,ins,"$t2");
    fprintf(output_code_pointer,ins);
    fprintf(output_code_pointer,"#Equ\n");
}
void generate_neq(int index){
    TableEle *te = quad[index].des;
    TableEle *te1 = quad[index].src1;
    TableEle *te2 = quad[index].src2;
    char ins[MAXInstruL]="\0";
    generate_load_ele(te1,ins,"$t0");
    fprintf(output_code_pointer,ins);
    generate_load_ele(te2,ins,"$t1");
    fprintf(output_code_pointer,ins);
    fprintf(output_code_pointer,"sne\t$t2\t$t0\t$t1\n");
    generate_save_ele(te,ins,"$t2");
    fprintf(output_code_pointer,ins);
    fprintf(output_code_pointer,"#Not Equ\n");
}
void generate_asn(int index){
    TableEle *te = quad[index].des;
    TableEle *te1 = quad[index].src1;
    char ins[MAXInstruL]="\0";
    generate_load_ele(te1,ins,"$t0");
    fprintf(output_code_pointer,ins);
    fprintf(output_code_pointer,"add\t$t1\t$0\t$t0\n");
    generate_save_ele(te,ins,"$t1");
    fprintf(output_code_pointer,ins);
    fprintf(output_code_pointer,"#Assign\n");
}
void generate_mdcl(int index){
    if(start == 0){
        start = 1;
        fprintf(output_code_pointer,".text:\n");
    }
    fprintf(output_code_pointer,"main:\n");
    fprintf(output_code_pointer,"la\t$ra\tm_end\n");
    fprintf(output_code_pointer,"sw\t$ra\t%d($sp)\n",page_size-4);
    fprintf(output_code_pointer,"sw\t$fp\t%d($sp)\n",page_size-8);
    fprintf(output_code_pointer,"addiu\t$t0\t$sp\t-8\n");
    fprintf(output_code_pointer,"add\t$fp\t$t0\t$0\n");
    fprintf(output_code_pointer,"#Main Declare\n");
}
void generate_end(int index){
    fprintf(output_code_pointer,"addi\t$v0\t$0\t0\n");
    fprintf(output_code_pointer,"lw\t$ra\t%d($sp)\n",page_size-4);
    fprintf(output_code_pointer,"lw\t$fp\t%d($sp)\n",page_size-8);
    fprintf(output_code_pointer,"addiu\t$sp\t$sp\t%d\n",page_size);
    fprintf(output_code_pointer,"jr\t$ra\n");
    fprintf(output_code_pointer,"#End\n");
}
void generate_rrt(int index){
    TableEle *te = quad[index].des;
    char ins[MAXInstruL]="\0";
    generate_load_ele(te,ins,"$t0");
    fprintf(output_code_pointer,ins);
    fprintf(output_code_pointer,"addi\t$v0\t$t0\t0\n");
    fprintf(output_code_pointer,"lw\t$ra\t%d($sp)\n",page_size-4);
    fprintf(output_code_pointer,"lw\t$fp\t%d($sp)\n",page_size-8);
    fprintf(output_code_pointer,"addiu\t$sp\t$sp\t%d\n",page_size);
    fprintf(output_code_pointer,"jr\t$ra\n");
    fprintf(output_code_pointer,"#Return with values\n");
}
void generate_vrt(int index){
    fprintf(output_code_pointer,"lw\t$ra\t%d($sp)\n",page_size-4);
    fprintf(output_code_pointer,"lw\t$fp\t%d($sp)\n",page_size-8);
    fprintf(output_code_pointer,"addiu\t$sp\t$sp\t%d\n",page_size);
    fprintf(output_code_pointer,"jr\t$ra\n");
    fprintf(output_code_pointer,"#Return without values\n");
}
void generate_lab(int index){
    TableEle *te = quad[index].des;
    fprintf(output_code_pointer,"%s:\n",te->name);
}
void generate_goto(int index){
    TableEle *te = quad[index].des;
    fprintf(output_code_pointer,"j\t%s\n",te->name);
    fprintf(output_code_pointer,"#Goto\n");
}
void generate_ngoto(int index){
    TableEle *te = quad[index].des;
    TableEle *te1 = quad[index].src1;
    char ins[MAXInstruL]="\0";
    generate_load_ele(te1,ins,"$t0");
    fprintf(output_code_pointer,ins);
    fprintf(output_code_pointer,"beqz\t$t0\t%s\n",te->name);
    fprintf(output_code_pointer,"#If not goto\n");
}
void generate_tgoto(int index){
    TableEle *te = quad[index].des;
    TableEle *te1 = quad[index].src1;
    char ins[MAXInstruL]="\0";
    generate_load_ele(te1,ins,"$t0");
    fprintf(output_code_pointer,ins);
    fprintf(output_code_pointer,"bnez\t$t0\t%s\n",te->name);
    fprintf(output_code_pointer,"#If true goto\n");
}
void generate_call(int index){
    TableEle *te = quad[index].des;
    int i = 3;
    char ins[MAXInstruL]="\0";
    fprintf(output_code_pointer,"jal\t%s\n", te->name);
    fprintf(output_code_pointer,"#Call\n");
}
void generate_push(int index){
    TableEle *te1 = quad[index].src1;
    TableEle *te = quad[index].des;
    char ins[MAXInstruL]="\0";
    generate_load_ele(te1,ins,"$t0");
 //   printf("%d\n",te->addr);
    fprintf(output_code_pointer,ins);
    fprintf(output_code_pointer,"sw\t$t0\t%d($sp)\n",-44-te->addr);
    fprintf(output_code_pointer,"#Push\n");
}
void generate_mff(int index){
    TableEle *te = quad[index].des;
    fprintf(output_code_pointer,"sw\t$v0\t%d($sp)\n",page_size-44-te->addr);
    fprintf(output_code_pointer,"#Move from function\n");
}
void generate_lfa(int index){
    TableEle *te = quad[index].des;
    TableEle *te1 = quad[index].src1;
    TableEle *te2 = quad[index].src2;
    char ins[MAXInstruL]="\0";
    if(te1->kind == ARRAY){
        fprintf(output_code_pointer,"la\t$t0\t%d($sp)\n",page_size-44-te1->addr);
    }
    else if(te1->kind == GLOARR)
        fprintf(output_code_pointer,"la\t$t0\t%s\n", te1->name);
    generate_load_ele(te2,ins,"$t1");
    fprintf(output_code_pointer,ins);
    fprintf(output_code_pointer,"li\t$t4\t4\n");
    fprintf(output_code_pointer,"mul\t$t1\t$t1\t$t4\n");
    if(te1->kind == ARRAY)
        fprintf(output_code_pointer,"sub\t$t3\t$t0\t$t1\n");
    else
        fprintf(output_code_pointer,"add\t$t3\t$t0\t$t1\n");
    fprintf(output_code_pointer,"lw\t$t2\t0($t3)\n");
    generate_save_ele(te,ins,"$t2");
    fprintf(output_code_pointer,ins);
    fprintf(output_code_pointer,"#Load from array\n");
}
void generate_sta(int index){
    TableEle *te = quad[index].des;
    TableEle *te1 = quad[index].src1;
    TableEle *te2 = quad[index].src2;
    char ins[MAXInstruL]="\0";
    if(te1->kind == ARRAY){
        fprintf(output_code_pointer,"la\t$t0\t%d($sp)\n",page_size-44-te1->addr);
    }
    else if(te1->kind == GLOARR)
        fprintf(output_code_pointer,"la\t$t0\t%s\n", te1->name);
    generate_load_ele(te2,ins,"$t1");
    fprintf(output_code_pointer,ins);
    generate_load_ele(te,ins,"$t2");
    fprintf(output_code_pointer,ins);
    fprintf(output_code_pointer,"li\t$t4\t4\n");
    fprintf(output_code_pointer,"mul\t$t1\t$t1\t$t4\n");
    if(te1->kind == ARRAY)
        fprintf(output_code_pointer,"sub\t$t3\t$t0\t$t1\n");
    else
        fprintf(output_code_pointer,"add\t$t3\t$t0\t$t1\n");
    fprintf(output_code_pointer,"sw\t$t2\t0($t3)\n");
    fprintf(output_code_pointer,"#Store to Array\n");
}
void generate_rd(int index){
    TableEle *te = quad[index].des;
    char ins[MAXInstruL]="\0";
    if(te->type == INT)
        fprintf(output_code_pointer,"li\t$v0\t5\n");
    else
        fprintf(output_code_pointer,"li\t$v0\t12\n");
    fprintf(output_code_pointer,"syscall\n");
    generate_save_ele(te,ins,"$v0");
    fprintf(output_code_pointer,ins);
    fprintf(output_code_pointer,"#Read\n");
}
void generate_wrs(int index){
    TableEle *te = quad[index].des;
    fprintf(output_code_pointer,"li\t$v0\t4\n");
    fprintf(output_code_pointer,"la\t$a0\t%s\n",te->name);
    fprintf(output_code_pointer,"syscall\n");
    fprintf(output_code_pointer,"#Write String\n");
}
void generate_wri(int index){
    TableEle *te = quad[index].des;
    char ins[MAXInstruL]="\0";
    generate_load_ele(te,ins,"$t0");
    fprintf(output_code_pointer,ins);
    fprintf(output_code_pointer,"li\t$v0\t1\n");
    fprintf(output_code_pointer,"add\t$a0\t$t0\t$0\n");
    fprintf(output_code_pointer,"syscall\n");
    fprintf(output_code_pointer,"#Write int\n");
}
void generate_wrc(int index){
    TableEle *te = quad[index].des;
    char ins[MAXInstruL]="\0";
    generate_load_ele(te,ins,"$t0");
    fprintf(output_code_pointer,ins);
    fprintf(output_code_pointer,"li\t$v0\t11\n");
    fprintf(output_code_pointer,"add\t$a0\t$t0\t$0\n");
    fprintf(output_code_pointer,"syscall\n");
    fprintf(output_code_pointer,"#Write Integer\n");
}
void generate_mend(int index){
    fprintf(output_code_pointer,"m_end:\n");
}

void generate_code(){
    int i;
    for(i = 0; i < ins_num; i++){
        if(quad[i].ins == GLC){
            generate_glc(i);
        }
        else if(quad[i].ins == GLV){
            generate_glv(i);
        }
        else if(quad[i].ins == FDCL){
            generate_fdcl(i);
        }
        else if(quad[i].ins == NEG){
            generate_neg(i);
        }
        else if(quad[i].ins == ADD){
            generate_add(i);
        }
        else if(quad[i].ins == SUB){
            generate_sub(i);
        }
        else if(quad[i].ins == MUL){
            generate_mul(i);
        }
        else if(quad[i].ins == DIV){
            generate_div(i);
        }
        else if(quad[i].ins == LS){
            generate_ls(i);
        }
        else if(quad[i].ins == BG){
            generate_bg(i);
        }
        else if(quad[i].ins == NLS){
            generate_nls(i);
        }
        else if(quad[i].ins == NBG){
            generate_nbg(i);
        }
        else if(quad[i].ins == EQU){
            generate_equ(i);
        }
        else if(quad[i].ins == NEQ){
            generate_neq(i);
        }
        else if(quad[i].ins == ASN){
            generate_asn(i);
        }
        else if(quad[i].ins == MDCL){
            generate_mdcl(i);
        }
        else if(quad[i].ins == END){
            generate_end(i);
        }
        else if(quad[i].ins == RRT){
            generate_rrt(i);
        }
        else if(quad[i].ins == VRT){
            generate_vrt(i);
        }
        else if(quad[i].ins == LAB){
            generate_lab(i);
        }
        else if(quad[i].ins == GOTO){
            generate_goto(i);
        }
        else if(quad[i].ins == TGOTO){
            generate_tgoto(i);
        }
        else if(quad[i].ins == NGOTO){
            generate_ngoto(i);
        }
        else if(quad[i].ins == CALL){
            generate_call(i);
        }
        else if(quad[i].ins == PUSH){
            generate_push(i);
        }
        else if(quad[i].ins == MFF){
            generate_mff(i);
        }
        else if(quad[i].ins == LFA){
            generate_lfa(i);
        }
        else if(quad[i].ins == STA){
            generate_sta(i);
        }
        else if(quad[i].ins == RD){
            generate_rd(i);
        }
        else if(quad[i].ins == WRS){
            generate_wrs(i);
        }
        else if(quad[i].ins == WRC){
            generate_wrc(i);
        }
        else if(quad[i].ins == WRI){
            generate_wri(i);
        }
        else if(quad[i].ins == MEND){
            generate_mend(i);
        }
    }
}
