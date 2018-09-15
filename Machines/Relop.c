#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "machines.h"

struct machOut relop(int b, int end, char *buff, FILE *listFile) {
    int f = b;
    if(buff[f] == '<'){
        f++;
        if(buff[f] == '='){
            f++;
            char *lexeme = malloc((f-b+1)*sizeof(char));
            const char* from = buff;
            strncpy(lexeme, from+b, f-b);
            lexeme[f-b] = '\0';
            struct machOut out = {f, 0, lexeme, RELOP, LTEQ};
            return out;
        }
        else if(buff[f] == '>'){
            f++;
            char *lexeme = malloc((f-b+1)*sizeof(char));
            const char* from = buff;
            strncpy(lexeme, from+b, f-b);
            lexeme[f-b] = '\0';
            struct machOut out = {f, 0, lexeme, RELOP, NEQ};
            return out;
        }
        else{
            char *lexeme = malloc((f-b+1)*sizeof(char));
            const char* from = buff;
            strncpy(lexeme, from+b, f-b);
            lexeme[f-b] = '\0';
            struct machOut out = {f, 0, lexeme, RELOP, LT};
            return out;
        }
    }
    else if(buff[f] == '='){
        f++;
        char *lexeme = malloc((f-b+1)*sizeof(char));
        const char* from = buff;
        strncpy(lexeme, from+b, f-b);
        lexeme[f-b] = '\0';
        struct machOut out = {f, 0, lexeme, RELOP, EQ};
        return out;
    }
    else if(buff[f] == '>'){
        f++;
        if(buff[f] == '='){
            f++;
            char *lexeme = malloc((f-b+1)*sizeof(char));
            const char* from = buff;
            strncpy(lexeme, from+b, f-b);
            lexeme[f-b] = '\0';
            struct machOut out = {f, 0, lexeme, RELOP, GTEQ};
            return out;
        }
        else{
            char *lexeme = malloc((f-b+1)*sizeof(char));
            const char* from = buff;
            strncpy(lexeme, from+b, f-b);
            lexeme[f-b] = '\0';
            struct machOut out = {f, 0, lexeme, RELOP, GT};
            return out;
        }
    }
    else{
        struct machOut block = {BLOCK, -1, "\0", -1, -1};
        return block;
    }
}