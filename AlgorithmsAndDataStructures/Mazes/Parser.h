#include<stdio.h>
#include<stdlib.h>

//Enumerazione dei simboli
typedef enum {LPAR, RPAR, ARROW, COMMA, SEMICOLON, DOT, WALL, CORRIDOR, FINISH} symbols;

void avoidSpace (FILE* fd);
int match (FILE *fd, symbols sym);
void syntaxErr (symbols sym, int pos);
int ParseInt(FILE *fd, int *num);
int ParseFloat(FILE *fd, float *num);
