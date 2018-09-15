#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "machines.h"
#include "../tokens.h"

/*
 * This file finds all types of characters including:
 * ':=', '..', ':', ',', ';', '.', '(', ')', '[', ']'
 */

struct machOut catchall(int b, int end, char *buff, FILE *listFile){
    int f =b;
    if(strncmp(&buff[f], ":=", 2)==0) {
        f = f+2;
        char *lexeme = malloc((f-b+1)*sizeof(char));
        const char* from = buff;
        strncpy(lexeme, from+b, f-b);
        lexeme[f-b] = '\0';
        struct machOut out = {f, 0, lexeme, ASSIGNOP, 0};
        return out;
    }
    else if(strncmp(&buff[f], "..", 2)==0){
        f = f+2;
        char *lexeme = malloc((f-b+1)*sizeof(char));
        const char* from = buff;
        strncpy(lexeme, from+b, f-b);
        lexeme[f-b] = '\0';
        struct machOut out = {f, 0, lexeme, ARRAY, 0};
        return out;
    }
    else if(buff[f] == ':'){
        f++;
        char *lexeme = malloc((f-b+1)*sizeof(char));
        const char* from = buff;
        strncpy(lexeme, from+b, f-b);
        lexeme[f-b] = '\0';
        struct machOut out = {f, 0, lexeme, TYPE, 0};
        return out;
    }
    else if(buff[f] == ','){
        f++;
        char *lexeme = malloc((f-b+1)*sizeof(char));
        const char* from = buff;
        strncpy(lexeme, from+b, f-b);
        lexeme[f-b] = '\0';
        struct machOut out = {f, 0, lexeme, PUNCTUATION, COMMA};
        return out;
    }
    else if(buff[f] == ';'){
        f++;
        char *lexeme = malloc((f-b+1)*sizeof(char));
        const char* from = buff;
        strncpy(lexeme, from+b, f-b);
        lexeme[f-b] = '\0';
        struct machOut out = {f, 0, lexeme, PUNCTUATION, SEMICOLON};
        return out;
    }
    else if(buff[f] == '.'){
        f++;
        char *lexeme = malloc((f-b+1)*sizeof(char));
        const char* from = buff;
        strncpy(lexeme, from+b, f-b);
        lexeme[f-b] = '\0';
        struct machOut out = {f, 0, lexeme, PUNCTUATION, PERIOD};
        return out;
    }
    else if(buff[f] == '('){
        f++;
        char *lexeme = malloc((f-b+1)*sizeof(char));
        const char* from = buff;
        strncpy(lexeme, from+b, f-b);
        lexeme[f-b] = '\0';
        struct machOut out = {f, 0, lexeme, GROUPING, LPAR};
        return out;
    }
    else if(buff[f] == ')'){
        f++;
        char *lexeme = malloc((f-b+1)*sizeof(char));
        const char* from = buff;
        strncpy(lexeme, from+b, f-b);
        lexeme[f-b] = '\0';
        struct machOut out = {f, 0, lexeme, GROUPING, RPAR};
        return out;
    }
    else if(buff[f] == '['){
        f++;
        char *lexeme = malloc((f-b+1)*sizeof(char));
        const char* from = buff;
        strncpy(lexeme, from+b, f-b);
        lexeme[f-b] = '\0';
        struct machOut out = {f, 0, lexeme, GROUPING, LBRACK};
        return out;
    }
    else if(buff[f] == ']'){
        f++;
        char *lexeme = malloc((f-b+1)*sizeof(char));
        const char* from = buff;
        strncpy(lexeme, from+b, f-b);
        lexeme[f-b] = '\0';
        struct machOut out = {f, 0, lexeme, GROUPING, RBRACK};
        return out;
    }
    else{
        struct machOut block = {BLOCK, -1, "\0", -1, -1};
        return block;
    }
}
