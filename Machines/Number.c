#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>
#include "machines.h"

int checkError(int state, int xx, int yy, int zz, char lead1, char trail2, char lead3){
  return 0;
}

struct machOut numbers(int b, int end, char *buff, FILE *listFile){
  int state = 0;//1 int, 2 sreal, 3 lreal
  int xx = 0;
  int yy = 0;
  int zz = 0;
  char lead1 = 'a';
  char lead2 = 'b';
  char lead3 = 'c';
  int f=b;

  if(isdigit(buff[f])!=0){
    f++;
    while(isdigit(buff[f])!=0){
      f++;
    }
    xx=f;
    // if(((f-b)>1) && buff[b]=='0'){//CHECK LEADING ZERO
    //   //LEADING ZERO
    //   char *lexeme = malloc((f-b+1)*sizeof(char));
    //   const char* from = buff;
    //   strncpy(lexeme, from+b,f-b);
    //   lexeme[f-b] = '\0';
    //   struct machOut err = {f, LEADZERO, lexeme};
    //   return err;
    // }
    if(buff[f] == '.'){
      f++;
      if(isdigit(buff[f])!=0){
        f++;
        while(isdigit(buff[f])!=0){
          f++;
        }
        yy = f-1;//minus 1 for period
        if(buff[f] == 'E'){//took out option for e because it isn't listed among pascals lexical conventions
          f++;
          if(isdigit(buff[f])!=0){
            f++;
            // if(buff[f-1] == '0'){
            //   //EXPLEADZERO
            //   //LEADING ZERO
            //   char *lexeme = malloc((f-b+1)*sizeof(char));
            //   const char* from = buff;
            //   strncpy(lexeme, from+b,f-b);
            //   lexeme[f-b] = '\0';
            //   struct machOut err = {f, EXPLEADZERO, lexeme};
            //   return err;
            // }
            state=3;//is definetly lreal
            while(isdigit(buff[f])!=0){
              f++;
            }
            zz = f - 2;//period, e
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
              // if(buff[f-1] == '0'){
              //   //EXPLEADZERO
              //   //LEADING ZERO
              //   char *lexeme = malloc((f-b+1)*sizeof(char));
              //   const char* from = buff;
              //   strncpy(lexeme, from+b,f-b);
              //   lexeme[f-b] = '\0';
              //   struct machOut err = {f, EXPLEADZERO, lexeme};
              //   return err;
              // }
              //d.dE+/-d
              while(isdigit(buff[f])!=0){
                f++;
              }
              zz = f - 3;//period, e, +/-
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
              // if(buff[f-1] == '0'){
              //   //DECTRAILZERO
              //   char *lexeme = malloc((f-b+1)*sizeof(char));
              //   const char* from = buff;
              //   strncpy(lexeme, from+b,f-b);
              //   lexeme[f-b] = '\0';
              //   struct machOut err = {f, DECTRAILZERO, lexeme};
              //   return err;
              // }
              state = 2;//return sreal
              char *lexeme = malloc((f-b+1)*sizeof(char));
              const char* from = buff;
              strncpy(lexeme, from+b, f-b);
              lexeme[f-b] = '\0';
              struct machOut out = {f, 0, lexeme, SREAL, 0};
              return out;
            }
          }
          else{
            // if(buff[f-1] == '0'){
            //   //DECTRAILZERO
            //   char *lexeme = malloc((f-b+1)*sizeof(char));
            //   const char* from = buff;
            //   strncpy(lexeme, from+b,f-b);
            //   lexeme[f-b] = '\0';
            //   struct machOut err = {f, DECTRAILZERO, lexeme};
            //   return err;
            // }
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
          // if(buff[f-1] == '0'){
          //   //DECTRAILZERO
          //   char *lexeme = malloc((f-b+1)*sizeof(char));
          //   const char* from = buff;
          //   strncpy(lexeme, from+b,f-b);
          //   lexeme[f-b] = '\0';
          //   struct machOut err = {f, DECTRAILZERO, lexeme};
          //   return err;
          // }
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

struct machOut number(int b, int end, char *buff, FILE *listFile){
  return numbers(b,end,buff,listFile);
}
