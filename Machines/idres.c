#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>
#include "machines.h"

struct machOut idres(int b, int end, char *buff, FILE *listFile){
  int f = b;

  //starting character
  if(isalpha(buff[f])){
    f++;
  }
  else{
    struct machOut block = {BLOCK, -1, "\0"};
    return block;
  }

  //subsequent characters
  while(isalnum(buff[f])){
    f++;
  }

  char lexeme[f-b+1];
  const char* from = buff;
  strncpy(lexeme, from+b,f-b);
  lexeme[f-b] = '\0';
  if((f-b) > 10){
    struct machOut out = {f, IDTOOLONG, lexeme};//when there is an error f-b will denote the lexeme size
    fprintf(listFile, "%-12s%-30s%s\n", "LEXERR:", "IDTOOLONG", lexeme);
    printf("%-11s%-35s%s\n", "LEXERR:", "IDTOOLONG", lexeme);
    return out;
  }
  struct machOut out = {f, 0, lexeme};
  return out;
}
