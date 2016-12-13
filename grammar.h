#ifndef GRAMMA_H_INCLUDED
#define GRAMMA_H_INCLUDED
#define MAXPredictNum 100

extern FILE * output_grammar_pointer;
extern char pre_token[MAXPredictNum];
extern int return_num;
void clearPreToken();
void program();
void con_dcl();
void con_def();
void var_dcl();
void var_def();
void r_func_dcl();
int dcl_head();
void para();
void para_table();
void comp_statement();
void statement_lists();
void statement();
void condition_statement();
TableEle* condition();
void loop_statement();
TableEle* step();
int function_call_statement();
void value_para_table();
void assign_statement();
void read_statement();
void write_statement();
void return_statement();
void v_func_dcl();
void func_main();
TableEle* expression();
TableEle* term();
TableEle* factor();
void integer();



#endif // GRAMMA_H_INCLUDED
