#include <fcntl.h>
#include <X11/Xlib.h>
#include "Scanner.h"
#include "errno.h"
#include "stdlib.h"
#include <ctype.h>





//wczytywanie pliku do pamieci, calego!

struct File init(char* path) {
    long fd;
    char *file;
    FILE *f;
    size_t nbytes;
    f = fopen(path, "rb");

    if (f == NULL) {
        perror("cannot open specific file");
        exit(EXIT_FAILURE);
    }

    fseek(f, 0, SEEK_END);
    fd = ftell(f);
    rewind(f);

    file = (char*) malloc(sizeof (char)*fd);

    if (file == NULL) {
        perror("Blod malloc");
        exit(EXIT_FAILURE);
    }

    if (f == NULL) {
        perror("cannot open specific file");
        exit(EXIT_FAILURE);
    }

    nbytes = fread(file, 1, fd, f);
    if (nbytes != fd) {
        perror("problem with read file");
        exit(EXIT_FAILURE);
    }
    fclose(f);
    struct File line = {0, 0, fd, 0, file};
    return line;
}

bool isDigit(char sign) {
    return sign >= '0' && sign <= '9';
}

bool isLetter(char sign) {
    return sign >= 'A' && sign <= 'Z' || sign >= 'a' && sign <= 'z';
}

bool isDigitOrLetter(char sign) {
    return isDigit(sign) || isLetter(sign);
}

void fillToken(struct Token *token, int line, int column, TokenType type) {
    token->line = line;
    token->column = column;
    token->type = type;
}

char getChar(struct File *line) {
    if (line->file != NULL) {
        char a = line->file[line->currentPosition];
        line->currentPosition++;
        line->column++;
        return a;

    }
    return 0;
}

char whatIsNextChar(struct File *file) {
    if (file->file != NULL) {
        return file->file[file->currentPosition];
    }
    return 0;
}

int typeOfIdent(char *ide) {
    int i = 0;
    char tmp[100] = "";
    while (ide[i] != '\0') {
        tmp[i] = (char) tolower((int) ide[i]);
        i++;
    }
    if (!strcmp(tmp, "var")) {
        return varsym;
    } else
        if (!strcmp(tmp, "while")) {
        return whilesym;
    } else
        if (!strcmp(tmp, "do")) {
        return dosym;
    } else
        if (!strcmp(tmp, "call")) {
        return callsym;
    } else
        if (!strcmp(tmp, "begin")) {
        return beginsym;
    } else
        if (!strcmp(tmp, "if")) {
        return ifsym;
    } else
        if (!strcmp(tmp, "then")) {
        return thensym;
    } else
        if (!strcmp(tmp, "const")) {
        return constsym;
    } else
        if (!strcmp(tmp, "procedure")) {
        return procsym;
    } else
        if (!strcmp(tmp, "odd")) {
        return oddsym;
    } else
        return ident;
}

struct Token scan(struct File *file) {
    char sign = getChar(file);
    struct Token __token;
    int line = file->line;
    int column = file->column;
    memset(&__token.buffer, 0, 1024);
    switch (sign) {
        case 0: fillToken(&__token, line, column, eof);
            return __token; // end of program! 
        case '\n':
            line++;
            column = 0;
            fillToken(&__token, line, column, whitespace);
            strcat(__token.buffer, "\n");
            return __token;
        case 9:
            fillToken(&__token, line, column, whitespace);
            strcat(__token.buffer, "       ");
            return __token;
        case 32:
            fillToken(&__token, line, column, whitespace);
            strcat(__token.buffer, " ");
            return __token;
        case 13:
            fillToken(&__token, line, column, whitespace);
            strcat(__token.buffer, (char) 13);
            return __token;
        case '=': fillToken(&__token, line, column, eql);
            strcat(__token.buffer, "=");
            return __token;
        case '+': fillToken(&__token, line, column, plus);
            strcat(__token.buffer, "+");
            return __token;
        case '-': fillToken(&__token, line, column, minus);
            strcat(__token.buffer, "-");
            return __token;
        case '>': if (whatIsNextChar(file) == '=') {
                sign = getChar(file);
                fillToken(&__token, line, column, geq);
                strcat(__token.buffer, ">=");
            } else
                fillToken(&__token, line, column, gtr);
            strcat(__token.buffer, ">");
            return __token;
        case '<':
            switch (whatIsNextChar(file)) {
                case '=':
                    sign = getChar(file);
                    fillToken(&__token, line, column, leq);
                    strcat(__token.buffer, "<=");
                    break;
                case '>':
                    sign = getChar(file);
                    fillToken(&__token, line, column, neq);
                    strcat(__token.buffer, "<>");
                    break;
                default:
                    fillToken(&__token, line, column, lss);
                    strcat(__token.buffer, "<");
            }
            return __token;
        case ':': switch (whatIsNextChar(file)) {
                case '=': fillToken(&__token, line, column, becomes);
                    strcat(__token.buffer, ":=");
                    getChar(file);
                    break;
                default: sign = getChar(file);
                    fillToken(&__token, line, column, error);
                    strcat(__token.buffer, ":");
            }
            return __token;

        case '.': fillToken(&__token, line, column, period);
            strcat(__token.buffer, ".");
            return __token;
        case '*': fillToken(&__token, line, column, times);
            strcat(__token.buffer, "*");
            return __token;
        case '/': fillToken(&__token, line, column, slash);
            strcat(__token.buffer, "/");
            return __token;
        case ';': fillToken(&__token, line, column, semicolon);
            strcat(__token.buffer, ";");
            return __token;
        case ',': fillToken(&__token, line, column, comma);
            strcat(__token.buffer, ",");
            return __token;
        default:
            if (isDigit(sign)) {
                fillToken(&__token, line, column, number);
                while (isDigit(sign)) {
                    __token.buffer[strlen(__token.buffer)] = sign;
                    __token.buffer[strlen(__token.buffer) + 1] = '\0';
                    sign = getChar(file);
                }
                file->currentPosition--;
            } else
                if (isLetter(sign)) {
                fillToken(&__token, line, column, ident);
                while (isDigitOrLetter(sign)) {
                    __token.buffer[strlen(__token.buffer)] = sign;
                    __token.buffer[strlen(__token.buffer) + 1] = '\0';
                    sign = getChar(file);
                }
                file->currentPosition--;
                __token.type = typeOfIdent(__token.buffer);
            }

            return __token;

    }

}
