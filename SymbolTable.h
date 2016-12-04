#ifndef SYMBOLTABLE_H_INCLUDED
#define SYMBOLTABLE_H_INCLUDED
#define MAXTableEleNum 1000
#define MAXTableNum 100
#define MAXStringNum 1000
extern FILE *output_symbol_table_pointer;
extern FILE* output_code_pointer;

extern int page_size;
enum KIND{
    CONST = 1, VAR, PARA, FUNC, ARRAY, STRING, TMPVAR, TMPCON, LABEL, GLOVAR, GLOCON, GLOARR
};
enum TYPE{
    VOID = 1, INT, CHAR
};
typedef struct{
    char name[MAXTokenL];//标识符名称
    int kind;//标识符种类
    int type;//标识符类型
    int addr;//数组、变量、函数：地址，符号表编号 常量：值
    int length;//数组长度
}TableEle;//符号表项
typedef struct{
    TableEle table_ele[MAXTableEleNum];
    int table_ele_num;
}Table;//

extern Table tbl[MAXTableNum];
//0:全局符号表 1~n:第n个函数符号表
extern int table_num;//统计表的数量
extern int addr;
//登记符号表
extern int tmp_num;
extern int string_num;
extern char strings[MAXStringNum][MAXStringL];

TableEle* enter_table(char name[], int kind, int type, int addr, int length, int table_num);
int check_same(char name[], int table_num);
TableEle* search_table(char name[], int table_num);
TableEle* search_all(char name[], int table_num);
TableEle* create_new_tmp(int type, int value);
TableEle* create_new_label();
TableEle* create_new_string(char value[]);
#endif // SYMBOLTABLE_H_INCLUDED
