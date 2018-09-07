#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>
#include "machines.h"

struct machOut idres(int b, int end, char *buff, FILE *listFile){
  int f = b;
  if(isalpha(buff[f])){
    f++;
  }
  while(isalnum(buff[f])){
    f++;
  }
  char lexeme[f-b];
  const char* from = buff;
  strncpy(lexeme, from+b,f-b);
  if((f-b) > 10){
    struct machOut out = {f, IDTOOLONG, lexeme};//when there is an error f-b will denote the lexeme size
    return out;
  }
  struct machOut out = {f, 0, lexeme};
  return out;
}
