#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>
#include "machines.h"

struct numsOut
{
  struct machOut out;
  int xx;
  int yy;
  int zz;
  char lead1;
  char trail2;
  char lead3;
  int state;
};

// int checkError(int state, int xx, int yy, int zz, char lead1, char trail2, char lead3){
//   return 0;
// }

struct numsOut numbers(int b, int end, char *buff, FILE *listFile){
  int state = 0;//1 int, 2 sreal, 3 lreal
  int xx = 0;
  int yy = 0;
  int zz = 0;
  char lead1 = 'a';
  char trail2 = 'a';
  char lead3 = 'a';
  int f=b;

  if(isdigit(buff[f])!=0){
    f++;
    while(isdigit(buff[f])!=0){
      f++;
    }
    xx=f-b;
    lead1 = buff[b];
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
        yy = f-b-xx-1;//minus 1 for period
        trail2 = buff[f-1];
        if(buff[f] == 'E'){//took out option for e because it isn't listed among pascals lexical conventions
          f++;
          if(isdigit(buff[f])!=0){
            lead3=buff[f];
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
            zz = f-b-yy-xx-1-1;//period, e,xx,yy
            //return lreal d.dEd
            state = 3;//lreal
            char *lexeme = malloc((f-b+1)*sizeof(char));
            const char* from = buff;
            strncpy(lexeme, from+b, f-b);
            lexeme[f-b] = '\0';
            struct machOut out = {f, 0, lexeme, LREAL, 0};
            struct numsOut numOut = {out, xx, yy, zz,lead1, trail2, lead3, state};
            return numOut;
          }
          else if(buff[f] == '+' || buff[f] == '-'){
            f++;
            if(isdigit(buff[f])!=0){
              lead3=buff[f];
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
              zz = f-b-yy-xx-1-2;//period, e, +/-, xx, yy
              state = 3;
              //return lreal
              char *lexeme = malloc((f-b+1)*sizeof(char));
              const char* from = buff;
              strncpy(lexeme, from+b, f-b);
              lexeme[f-b] = '\0';
              struct machOut out = {f, 0, lexeme, LREAL, 0};
              struct numsOut numOut = {out, xx, yy, zz,lead1, trail2, lead3, state};
              return numOut;
            }
            else{
              f--;
              //trail2 = buff[f-1];
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
              struct numsOut numOut = {out, xx, yy, zz,lead1, trail2, lead3, state};
              return numOut;
            }
          }
          else{
            //trail2 = buff[f-1];
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
            struct numsOut numOut = {out, xx, yy, zz,lead1, trail2, lead3, state};
            return numOut;
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
          struct numsOut numOut = {out, xx, yy, zz,lead1, trail2, lead3, state};
          return numOut;
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
        struct numsOut numOut = {out, xx, yy, zz,lead1, trail2, lead3, state};
        return numOut;
      }
    }
    else{
      state = 1;//int
      char *lexeme = malloc((f-b+1)*sizeof(char));
      const char* from = buff;
      strncpy(lexeme, from+b, f-b);
      lexeme[f-b] = '\0';
      struct machOut out = {f, 0, lexeme, INT, 0};
      struct numsOut numOut = {out, xx, yy, zz,lead1, trail2, lead3, state};
      return numOut;
    }
  }
  else{
    struct machOut block = {BLOCK, -1, "\0", -1, -1};
    struct numsOut blockOut = {block};
    return blockOut;
  }
}

struct machOut number(int b, int end, char *buff, FILE *listFile){
  struct numsOut numOut = numbers(b,end,buff,listFile);
  //check for all errors!
  if(numOut.state == 1){//int
    if(numOut.xx > 10){
      struct machOut out = numOut.out;
      struct machOut err = {out.b, INTTOOLONG, out.lexeme};
      return err;
    }
    else if(numOut.lead1 == '0'){
      struct machOut out = numOut.out;
      struct machOut err = {out.b, LEADZERO, out.lexeme};
      return err;
    }
    else{
      return numOut.out;
    }
  }
  else if(numOut.state == 2){//SREAL
    if(numOut.xx > 5){
      struct machOut out = numOut.out;
      struct machOut err = {out.b, SREAL1TOOLONG, out.lexeme};
      return err;
    }
    else if(numOut.yy > 5){
      struct machOut out = numOut.out;
      struct machOut err = {out.b, SREAL2TOOLONG, out.lexeme};
      return err;
    }
    else if(numOut.trail2 == '0'){
      struct machOut out = numOut.out;
      struct machOut err = {out.b, DECTRAILZERO, out.lexeme};
      return err;
    }
    else if(numOut.lead1 == '0'){
      struct machOut out = numOut.out;
      struct machOut err = {out.b, LEADZERO, out.lexeme};
      return err;
    }
    else{
      return numOut.out;
    }
  }
  else if(numOut.state == 3){
    printf("zz: %d\n", numOut.zz);
    if(numOut.xx > 5){
      struct machOut out = numOut.out;
      struct machOut err = {out.b, LREAL1TOOLONG, out.lexeme};
      return err;
    }
    else if(numOut.yy > 5){
      struct machOut out = numOut.out;
      struct machOut err = {out.b, LREAL2TOOLONG, out.lexeme};
      return err;
    }
    else if(numOut.zz > 2){
      struct machOut out = numOut.out;
      struct machOut err = {out.b, LREAL3TOOLONG, out.lexeme};
      return err;
    }
    else if(numOut.trail2 == '0'){
      struct machOut out = numOut.out;
      struct machOut err = {out.b, DECTRAILZERO, out.lexeme};
      return err;
    }
    else if(numOut.lead1 == '0'){
      struct machOut out = numOut.out;
      struct machOut err = {out.b, LEADZERO, out.lexeme};
      return err;
    }
    else if(numOut.lead3 == '0'){
      struct machOut out = numOut.out;
      struct machOut err = {out.b, EXPLEADZERO, out.lexeme};
      return err;
    }
    else{
      return numOut.out;
    }
  }
  else{
    return numOut.out;
  }
}
