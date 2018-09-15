#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>
#include "machines.h"

struct machOut number(int b, int end, char *buff, FILE *listFile){
  int state = 0;//1 int, 2 sreal, 3 lreal
  int f=b;
  if(isdigit(buff[f])!=0){
    f++;
    while(isdigit(buff[f])!=0){
      f++;
    }
    if(((f-b)>1) && buff[b]=='0'){//CHECK LEADING ZERO
      //LEADING ZERO
      struct machOut err = {f,};
    }
    if(buff[f] == '.'){
      f++;
      if(isdigit(buff[f])!=0){
        f++;
        while(isdigit(buff[f])!=0){
          f++;
        }
        if(buff[f] == 'E'){//took out option for e because it isn't listed among pascals lexical conventions
          f++;
          if(isdigit(buff[f])!=0){
            f++;
            state=3;//is definetly lreal
            while(isdigit(buff[f])!=0){
              f++;
            }
            //return lreal d.dEd
            state = 2;//sreal
            char *lexeme = malloc((f-b+1)*sizeof(char));
            const char* from = buff;
            strncpy(lexeme, from+b, f-b);
            lexeme[f-b] = '\0';
            struct machOut out = {f, 0, lexeme, LREAL, 0};
            return out;
          }
          else if(buff[f] == '+' || buff[f] == '-'){
            f++;
            if(isdigit(buff[f])!=0){
              f++;
              //d.dE+/-d
              while(isdigit(buff[f])!=0){
                f++;
              }
              //return lreal
              char *lexeme = malloc((f-b+1)*sizeof(char));
              const char* from = buff;
              strncpy(lexeme, from+b, f-b);
              lexeme[f-b] = '\0';
              struct machOut out = {f, 0, lexeme, LREAL, 0};
              return out;
            }
            else{
              f--;
              //d.dE+O
              //return sreal
              state = 2;
              char *lexeme = malloc((f-b+1)*sizeof(char));
              const char* from = buff;
              strncpy(lexeme, from+b, f-b);
              lexeme[f-b] = '\0';
              struct machOut out = {f, 0, lexeme, SREAL, 0};
              return out;
            }
          }
          else{
            state = 2;//sreal
            char *lexeme = malloc((f-b+1)*sizeof(char));
            const char* from = buff;
            strncpy(lexeme, from+b, f-b);
            lexeme[f-b] = '\0';
            struct machOut out = {f, 0, lexeme, SREAL, 0};
            return out;
          }
        }
        else{
          state = 2;//sreal
          char *lexeme = malloc((f-b+1)*sizeof(char));
          const char* from = buff;
          strncpy(lexeme, from+b, f-b);
          lexeme[f-b] = '\0';
          struct machOut out = {f, 0, lexeme, SREAL, 0};
          return out;
        }
      }
      else{ //d.O
        f--;
        state = 1;//not a real...return just the int
        char *lexeme = malloc((f-b+1)*sizeof(char));
        const char* from = buff;
        strncpy(lexeme, from+b, f-b);
        lexeme[f-b] = '\0';
        struct machOut out = {f, 0, lexeme, INT, 0};
        return out;
      }
    }
    else{
      state = 1;//int
      char *lexeme = malloc((f-b+1)*sizeof(char));
      const char* from = buff;
      strncpy(lexeme, from+b, f-b);
      lexeme[f-b] = '\0';
      struct machOut out = {f, 0, lexeme, INT, 0};
      return out;
    }
  }
  else{
    struct machOut block = {BLOCK, -1, "\0", -1, -1};
    return block;
  }
}
