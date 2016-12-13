#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "getSym.h"
#include "SymbolTable.h"
#include "error.h"
#include "grammar.h"
#include "Quadruple.h"
#include "GenerateCode.h"
int main(){
    char input_file_dir[MAXFileDirL],output_words_dir[MAXFileDirL], output_grammar_dir[MAXFileDirL],
    output_symbol_table_dir[MAXFileDirL],output_quadruple_dir[MAXFileDirL] ,output_code_dir[MAXFileDirL];

    printf("Input File Dir:\n");
    //scanf("%s",input_file_dir);
    strcpy(input_file_dir,"test.txt");
    printf("Output Words Dir:\n");
    //scanf("%s",output_words_dir);
    strcpy(output_words_dir,"out_words.txt");
    printf("Output Grammar Analysis Dir:\n");
    //scanf("%s",output_grammar_dir);
    strcpy(output_grammar_dir,"out_grammar.txt");
    printf("Output SymbolTable Dir:\n");
    strcpy(output_symbol_table_dir,"out_symbol_table.txt");
    printf("Output Quadruple Dir:\n");
    strcpy(output_quadruple_dir,"out_quadruple.txt");
    printf("Output Code Dir:\n");
    strcpy(output_code_dir,"out_code.txt");
    input_file_pointer = fopen(input_file_dir,"r");
    output_words_pointer = fopen(output_words_dir,"w");
    output_grammar_pointer = fopen(output_grammar_dir,"w");
    output_symbol_table_pointer = fopen(output_symbol_table_dir,"w");
    output_quadruple_pointer = fopen(output_quadruple_dir,"w");
    output_code_pointer = fopen(output_code_dir,"w");
    fprintf(output_code_pointer,".data:\n");
    getsym();
    program();
    if(error_num == 0)
        generate_code();
    fclose(input_file_pointer);
    fclose(output_words_pointer);
    fclose(output_quadruple_pointer);
    fclose(output_grammar_pointer);
    fclose(output_code_pointer);
    return 0;
}
