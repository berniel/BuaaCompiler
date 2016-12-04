#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "getSym.h"
#include "error.h"

int error_num = 0;
void error(int n){
    printf("error:%d\n",n);
    printf("\t");
    switch(n){
        case 1: printf("\' \' \' expected.");break;
        case 2: printf("\' \" \' expected or string is too long."); break;
        case 3: printf("Non-identifiable character in string.");break;
        case 4: printf("Non-identifiable character."); break;
        case 5: printf("\' ! \' expected.");break;
        case 6: printf("Invalid 0"); break;
        case 7: printf("Non-identifiable character in character."); break;
        case 8: printf("Identifier expected."); break;
        case 9: printf("Type expected."); break;
        case 10: printf("Variable declaration or function declaration expected here."); break;
        case 11: printf("Main or identifier expected."); break;
        case 12: printf("Const expected."); break;
        case 13: printf("\' ; \' expected."); break;
        case 14: printf("\' = \' expected."); break;
        case 15: printf("Integer expected."); break;
        case 16: printf("Character expected."); break;
        case 17: printf("Char/Int expected."); break;
        case 18: printf("\' ] \' expected."); break;
        case 19: printf("\' ( \' expected."); break;
        case 20: printf("\' ) \' expected."); break;
        case 21: printf("\' { \' expected."); break;
        case 22: printf("\' } \' expected."); break;
        case 24: printf("If expected."); break;
        case 25: printf("While expected."); break;
        case 26: printf("\' +/- \' expected."); break;
        case 27: printf("do/for expected."); break;
        case 28: printf("Scanf expected."); break;
        case 29: printf("Printf expected."); break;
        case 30: printf("Cannot be 0."); break;
        case 31: printf("\'+/-\' or a number expected."); break;
        case 32: printf("Return expected."); break;
        case 33: printf("Void expected."); break;
        case 34: printf("Main expected."); break;
        case 35: printf("Symbol Table is full."); break;
        case 36: printf("Redefinition."); break;
        case 37: printf("Undefined variable."); break;
        case 38: printf("Invalid assignment."); break;
        case 39: printf("A call for function with no return."); break;
        case 40: printf("Unmatched parameter number."); break;
        case 41: printf("Unmatched parameter type."); break;
        case 42: printf("Lack of return."); break;
        case 43: printf("Unmatched return type."); break;
    }
    printf("\n");
    printf("line:%d col:%d\n",ll, cc);
    printf("near %s\n",token);
    //exit(0);
    error_num++;
}
