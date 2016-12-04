#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "getSym.h"
#include "SymbolTable.h"
#include "error.h"


Table tbl[MAXTableNum];
//0:全局符号表 1~n:第n个函数符号表
int table_num;//统计表的数量
int addr = 0;
int tmp_num = 0;
int string_num = 0;
int label_num = 0;
char strings[MAXStringNum][MAXStringL];
FILE *output_symbol_table_pointer;

TableEle* enter_table(char name[], int kind, int type, int addr, int length, int table_num){
    if(tbl[table_num].table_ele_num >= MAXTableEleNum)
        error(35);
    if(check_same(name, table_num)>=0)
        error(36);//检查是否存在
    strcpy(tbl[table_num].table_ele[tbl[table_num].table_ele_num].name, name);
    tbl[table_num].table_ele[tbl[table_num].table_ele_num].kind = kind;
    tbl[table_num].table_ele[tbl[table_num].table_ele_num].type = type;
    tbl[table_num].table_ele[tbl[table_num].table_ele_num].addr = addr;
    tbl[table_num].table_ele[tbl[table_num].table_ele_num].length = length;
    fprintf(output_symbol_table_pointer,"Insert:%s %d %d %d %d in table %d\n", name, kind, type, addr, length, table_num);
    tbl[table_num].table_ele_num++;
    return &tbl[table_num].table_ele[tbl[table_num].table_ele_num-1];
}
int check_same(char name[], int table_num){
    int i;
    for(i = 0; i < tbl[table_num].table_ele_num; i++){
        if(!strcmp(name,tbl[table_num].table_ele[i].name))
            return i;
    }
    return -1;
}
TableEle* search_table(char name[], int table_num){
    int i;
    i = check_same(name, table_num);
    if(i >= 0){
        fprintf(output_symbol_table_pointer,"Found: %s %d %d %d %d in table %d", tbl[table_num].table_ele[i].name,tbl[table_num].table_ele[i].kind,tbl[table_num].table_ele[i].type,
               tbl[table_num].table_ele[i].addr,tbl[table_num].table_ele[i].length,table_num);
        return (&tbl[table_num].table_ele[i]);
    }
    else
        error(37);
    return &tbl[table_num].table_ele[i];
}
TableEle* search_all(char name[], int table_num){
    int i;
    i = check_same(name, table_num);
    if(i >= 0){
        fprintf(output_symbol_table_pointer,"Found: %s %d %d %d %d in table %d\n", tbl[table_num].table_ele[i].name,tbl[table_num].table_ele[i].kind,tbl[table_num].table_ele[i].type,
               tbl[table_num].table_ele[i].addr,tbl[table_num].table_ele[i].length,table_num);
        return &tbl[table_num].table_ele[i];
    }
    if(table_num == 0)
        error(37);
    i = check_same(name,0);
    if(i >= 0){
        fprintf(output_symbol_table_pointer,"Found: %s %d %d %d %d in table %d\n", tbl[0].table_ele[i].name,tbl[0].table_ele[i].kind,tbl[0].table_ele[i].type,
               tbl[0].table_ele[i].addr,tbl[0].table_ele[i].length,0);
    }
    else
        error(37);
    return &tbl[0].table_ele[i];
}
TableEle* create_new_tmp(int type, int value){
    char name[MAXTokenL]="\0";
    char tmpnum[25] = "\0";
    itoa(tmp_num,tmpnum,10);
    strcpy(name,".t");
    strcat(name,tmpnum);
    tmp_num++;
    if(type == 0){ //临时int常量
        enter_table(name,TMPCON,INT,value,0,table_num);
    }
    else if(type == 1){
        enter_table(name,TMPVAR,INT,value,0,table_num);
        addr+=4;
    }
    else if(type == 2){//临时char常量
        enter_table(name,TMPCON,CHAR,value,0,table_num);
    }
    else if(type == 3){//临时char常量
        enter_table(name,TMPVAR,CHAR,value,0,table_num);
        addr+=4;
    }
    return &tbl[table_num].table_ele[tbl[table_num].table_ele_num-1];
}
TableEle* create_new_string(char value[]){
    char name[MAXTokenL]="\0";
    char tmpnum[25] = "\0";
    TableEle* te;
    strcpy(name,".s");
    itoa(string_num, tmpnum, 10);
    strcat(name,tmpnum);
    //保存到.data
    fprintf(output_code_pointer,"\t%s:\t.asciiz\t\"%s\"\n",name,value);
    te = enter_table(name,STRING,VOID,0,0,table_num);
    string_num++;
    return te;
}
TableEle* create_new_label(){
    char name[MAXTokenL]="\0";
    char tmpnum[25] = "\0";
    TableEle* te;
    strcpy(name,".l");
    itoa(label_num, tmpnum, 10);
    strcat(name,tmpnum);
    te = enter_table(name,LABEL,VOID,0,0,table_num);
    label_num++;
    return te;
}
