#ifndef GETSYM_H_INCLUDED
#define GETSYM_H_INCLUDED
#define MAXTokenL 100
#define MAXStringL 100
#define MAXFileDirL 100
extern FILE *input_file_pointer;
extern FILE *output_words_pointer;
extern int words;
extern char token[MAXTokenL];
extern int num;
extern int ll;
extern int cc;
enum S{
    CONSTSY = 1, INTSY, CHARSY, VOIDSY, MAINSY, SCANFSY, PRINTFSY, IDSY,
    RETURNSY, IFSY, ELSESY, DOSY, WHILESY, FORSY,
    LBRACESY = 30, RBRACESY, LPARSY, RPARSY, LBRACKETSY, RBRACKETSY, SEMISY, COMMASY, PLUSSY, MINUSSY, STARSY, SLASHSY,
    ISSY, LSSY, NBGSY, BGSY, NLSSY, NEQSY, EQUSY,
    INTCON = 50, CHARCON, STRINGCON,
    ENDSY = 99
};
extern enum S symbol;
void clearToken();
void catToken(char c);
char getch();
void ungetch(char ch);
int searchReserver();
int transNum();
int isDigit(char c);
int isNewLine(char c);
int isSpace(char c);
int isTab(char c);
int isLetter(char c);
int isSQUO(char c);
int isDQUO(char c);
int isEQU(char c);
int isLS(char c);
int isBG(char c);
int isLBRACE(char c);
int isRBRACE(char c);
int isLBRACKET(char c);
int isRBRACKET(char c);
int isLPAR(char c);
int isRPAR(char c);
int isCOMMA(char c);
int isSEMI(char c);
int isPLUS(char c);
int isMINUS(char c);
int isSTAR(char c);
int isSLASH(char c);
int isEXC(char c);
int getsym();
#endif // GETSYM_H_INCLUDED
