#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "error.h"
#include "getSym.h"

FILE *input_file_pointer;
FILE *output_words_pointer;
/*
1:const 2.int 3.char 4.void 5.main 6.scanf 7.printf 8.标识符 9.return 10.if 11.else 12.do
13.while 14.for
30.{ 31.} 32.( 33.) 34.[ 35.] 36.; 37., 38.+ 39.- 40.* 41./ 42.= 43.< 44.<=
45.> 46.>= 47.!= 48.==
50.数字 51.字符 52.字符串
*/
int words = 0;
char token[MAXTokenL] = "\0";
int num;
int ll = 1;
int cc = 0;
enum S symbol = 0;
void clearToken(){
    token[0] = '\0';
}
void catToken(char c){
    char c_t[2] = {c,'\0'};
    strcat(token,c_t);
}
char getch(){
    cc++;
    return fgetc(input_file_pointer);
}
void ungetch(char ch){
    cc--;
    ungetc(ch, input_file_pointer);
}
int searchReserver(){
    if(strcmp(token,"const") == 0)
        return CONSTSY;
    else if(strcmp(token,"int") == 0)
        return INTSY;
    else if(strcmp(token,"char") == 0)
        return CHARSY;
    else if(strcmp(token,"void") == 0)
        return VOIDSY;
    else if(strcmp(token,"main") == 0)
        return MAINSY;
    else if(strcmp(token,"scanf") == 0)
        return SCANFSY;
    else if(strcmp(token,"printf") == 0)
        return PRINTFSY;
    else if(strcmp(token,"return") == 0)
        return RETURNSY;
    else if(strcmp(token,"if") == 0)
        return IFSY;
    else if(strcmp(token,"else") == 0)
        return ELSESY;
    else if(strcmp(token,"do") == 0)
        return DOSY;
    else if(strcmp(token,"while") == 0)
        return WHILESY;
    else if(strcmp(token,"for") == 0)
        return FORSY;
    else
        return IDSY;
}
int transNum(){
    return atoi(token);
}
int isSpace(char c){
    if(c == ' ')
        return 1;
    return 0;
}
int isNewLine(char c){
    if(c == '\n'){
        ll++;
        cc = 0;
        return 1;
    }
    return 0;
}
int isTab(char c){
    if(c == '\t')
        return 1;
    return 0;
}
int isLetter(char c){
    if((c >= 'a' && c <='z') || (c >='A' && c <='Z') || c == '_')
        return 1;
    return 0;
}
int isDigit(char c){
    if(c >= '0' && c <= '9')
        return 1;
    return 0;
}
int isSQUO(char c){
    if(c == '\'')
        return 1;
    return 0;
}
int isDQUO(char c){
    if(c == '\"')
        return 1;
    return 0;
}
int isEQU(char c){
    if(c == '=')
        return 1;
    return 0;
}
int isLS(char c){
    if(c == '<')
        return 1;
    return 0;
}
int isBG(char c){
    if(c == '>')
        return 1;
    return 0;
}
int isLBRACE(char c){
    if(c == '{')
        return 1;
    return 0;
}
int isRBRACE(char c){
    if(c == '}')
        return 1;
    return 0;
}
int isLBRACKET(char c){
    if(c == '[')
        return 1;
    return 0;
}
int isRBRACKET(char c){
    if(c == ']')
        return 1;
    return 0;
}
int isLPAR(char c){
    if(c == '(')
        return 1;
    return 0;
}
int isRPAR(char c){
    if(c == ')')
        return 1;
    return 0;
}
int isCOMMA(char c){
    if(c == ',')
        return 1;
    return 0;
}
int isSEMI(char c){
    if(c == ';')
        return 1;
    return 0;
}
int isPLUS(char c){
    if(c == '+')
        return 1;
    return 0;
}
int isMINUS(char c){
    if(c == '-')
        return 1;
    return 0;
}
int isSTAR(char c){
    if(c == '*'){
        return 1;
    }
    return 0;
}
int isSLASH(char c){
    if(c == '/')
        return 1;
    return 0;
}
int isEXC(char c){
    if(c == '!')
        return 1;
    return 0;
}
int getsym(){
    char ch;
    int i = 0;
    words++;
    clearToken();
    ch = getch();
    while(isSpace(ch) || isNewLine(ch) || isTab(ch)){
        ch = getch();
    }
    if(isLetter(ch)){
        while(isLetter(ch) || isDigit(ch)){
            catToken(ch);
            ch = getch();
        }
        ungetch(ch);
        symbol = searchReserver();
    }
    else if(isDigit(ch)){
        while(isDigit(ch)){
            if(token[0] == '0')
                error(6);//错误6：前导0
            catToken(ch);
            ch = getch();
        }
        ungetch(ch);
        num = transNum();
        symbol = INTCON;
    }
    else if(isSQUO(ch)){
        ch = getch();
        if(!isDigit(ch) && !isLetter(ch) && !isSTAR(ch) && !isSLASH(ch) && !isPLUS(ch) && !isMINUS(ch))
            error(7);//错误7：不可识别字符
        catToken(ch);
        num = (int)ch;
        ch = getch();
        if(!isSQUO(ch)){
            error(1);//错误1：字符缺少单引号
            //ungetch(ch);
        }
        symbol = CHARCON;
    }
    else if(isDQUO(ch)){
        ch = getch();
        while(!isDQUO(ch)){
            i++;
            if(i == MAXStringL){
                error(2);//错误2：字符串长度超出范围或缺少双引号
                break;
            }
            if((int)ch != 32 && (int)ch != 33 && ((int)ch < 35 || (int)ch > 126)){
                error(3);//错误3：字符串中出现不可辨识字符或读到文件尾
                break;
            }
            catToken(ch);
            ch = getch();
        }
        symbol = STRINGCON;
    }
    else if(isEQU(ch)){
        catToken(ch);
        ch = getch();
        if(isEQU(ch)){
            symbol = EQUSY;
            catToken(ch);
        }
        else{
            ungetch(ch);
            symbol = ISSY;
        }
    }
    else if(isLS(ch)){
        catToken(ch);
        ch = getch();
        if(isEQU(ch)){
            symbol = NBGSY;
            catToken(ch);
        }
        else{
            ungetch(ch);
            symbol = LSSY;
        }
    }
    else if(isBG(ch)){
        catToken(ch);
        ch = getch();
        if(isEQU(ch)){
            symbol = NLSSY;
            catToken(ch);
        }
        else{
            ungetch(ch);
            symbol = BGSY;
        }
    }
    else if(isLBRACE(ch)) {symbol = LBRACESY;catToken(ch);}
    else if(isRBRACE(ch)) {symbol = RBRACESY;catToken(ch);}
    else if(isLBRACKET(ch)) {symbol = LBRACKETSY;catToken(ch);}
    else if(isRBRACKET(ch)) {symbol = RBRACKETSY;catToken(ch);}
    else if(isLPAR(ch)) {symbol = LPARSY;catToken(ch);}
    else if(isRPAR(ch)) {symbol = RPARSY;catToken(ch);}
    else if(isCOMMA(ch)) {symbol = COMMASY;catToken(ch);}
    else if(isSEMI(ch)) {symbol = SEMISY;catToken(ch);}
    else if(isPLUS(ch)) {symbol = PLUSSY;catToken(ch);}
    else if(isMINUS(ch)) {symbol = MINUSSY;catToken(ch);}
    else if(isSTAR(ch)) {symbol = STARSY;catToken(ch);}
    else if(isSLASH(ch)) {symbol = SLASHSY;catToken(ch);}
    else if(isEXC(ch)) {
        catToken(ch);
        ch = getch();
        if(!isEQU(ch)){
            ungetch(ch);
            error(5);//!后不是=
        }
        catToken(ch);
        symbol = NEQSY;
    }
    else if(feof(input_file_pointer)) symbol = ENDSY;
    else
        error(4);//错误4：编译过程中出现不可识别字符
    fprintf(output_words_pointer, "%d ", words);
    switch(symbol){
            case 1: fprintf(output_words_pointer,"CONSTSY "); break;
            case 2: fprintf(output_words_pointer,"INTSY "); break;
            case 3: fprintf(output_words_pointer,"CHARSY "); break;
            case 4: fprintf(output_words_pointer,"VOIDSY "); break;
            case 5: fprintf(output_words_pointer,"MAINSY "); break;
            case 6: fprintf(output_words_pointer,"SCANFSY "); break;
            case 7: fprintf(output_words_pointer,"PRINTFSY "); break;
            case 8: fprintf(output_words_pointer,"IDSY "); break;
            case 9: fprintf(output_words_pointer,"RETURNSY "); break;
            case 10: fprintf(output_words_pointer,"IFSY "); break;
            case 11: fprintf(output_words_pointer,"ELSESY "); break;
            case 12: fprintf(output_words_pointer,"DOSY "); break;
            case 13: fprintf(output_words_pointer,"WHILESY ");break;
            case 14: fprintf(output_words_pointer,"FORSY "); break;
            case 30: fprintf(output_words_pointer,"LBRACESY "); break;
            case 31: fprintf(output_words_pointer,"RBRACESY "); break;
            case 32: fprintf(output_words_pointer,"LPARSY "); break;
            case 33: fprintf(output_words_pointer,"RPARSY "); break;
            case 34: fprintf(output_words_pointer,"LBRACKETSY "); break;
            case 35: fprintf(output_words_pointer,"RBRACKETSY "); break;
            case 36: fprintf(output_words_pointer,"SEMISY "); break;
            case 37: fprintf(output_words_pointer,"COMMASY "); break;
            case 38: fprintf(output_words_pointer,"PLUSSY "); break;
            case 39: fprintf(output_words_pointer,"MINUSSY "); break;
            case 40: fprintf(output_words_pointer,"STARSY "); break;
            case 41: fprintf(output_words_pointer,"SLASHSY "); break;
            case 42: fprintf(output_words_pointer,"ISSY "); break;
            case 43: fprintf(output_words_pointer,"LSSY "); break;
            case 44: fprintf(output_words_pointer,"NBGSY "); break;
            case 45: fprintf(output_words_pointer,"BGSY "); break;
            case 46: fprintf(output_words_pointer,"NLSSY "); break;
            case 47: fprintf(output_words_pointer,"NEQSY "); break;
            case 48: fprintf(output_words_pointer,"EQUSY "); break;
            case 50: fprintf(output_words_pointer,"INTCON "); break;
            case 51: fprintf(output_words_pointer,"CHARCON "); break;
            case 52: fprintf(output_words_pointer,"STRINGCON "); break;
            //case 99: fprintf("ENDSY "); break;
            default: ;
        }
    fprintf(output_words_pointer,"%s\n",token);
    return strlen(token);
}

