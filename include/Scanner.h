#ifndef SCANNER
#define SCANNER
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <stdbool.h>
typedef enum {
  ident,number,lparen,rparne,times,slash,plus,minus,eql,neq,lss,leq,
  geq,gtr,callsym,beginsym,semicolon,ednsym,ifsym,whilesym,becomes,thensym,
  dosym,constsym,comma,varsym,procsym,period,oddsym,eof,error,whitespace
} TokenType;

 struct Token {
  TokenType type;
  char buffer[1024];
  int line;
  int column;
};
struct File {
    int line;
    int column;
    int maxlenght;
    int currentPosition;
    char *file;
};

bool isDigit(char sign);
bool isLetter(char sign);
bool isDigitOrLetter(char sign);
void fillToken(struct Token *token,int line,int column,TokenType type);
void setBuffer(struct Token *token,int size);
char getChar(struct File *file);
char whatIsNextChar(struct File* file);
struct File init(char* path);
struct Token scan(struct File *file);


#endif
