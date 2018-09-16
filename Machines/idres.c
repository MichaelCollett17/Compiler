#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>
#include "machines.h"
#include "../reservedWords.h"
#include "../LinkedLists/SymbolTable.h"

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
  //char lexeme[f-b+1];
  //Kyle being my hero
  char *lexeme = malloc((f-b+1)*sizeof(char));
  const char* from = buff;
  strncpy(lexeme, from+b,f-b);
  lexeme[f-b] = '\0';
  if((f-b) > 10){
    struct machOut out = {f, IDTOOLONG, lexeme};//when there is an error f-b will denote the lexeme size
    fprintf(listFile, "%-12s%-30s%s\n", "LEXERR:", "IDTOOLONG", lexeme);
    //printf("%-12s%-30s%s\n", "LEXERR:", "IDTOOLONG", lexeme);
    return out;
  }
  struct resWord rw = getTokAndAtt(lexeme);
  //if not found in reserved words
  //how to pass lexeme in a struct CONTINUE
  if(rw.tokenResWord==-1 && rw.attributeResWord==-1){
    int check = checkSymbolExists(lexeme);
    if(check==-1) {
      int key = addSymbol(lexeme);
      struct machOut out = {f, 0, lexeme, ID, key};//ptrToSymbol table uses key 0+
      //printSymbols();
      return out;
    }
    else{
      struct machOut out = {f, 0, lexeme, ID, check};//ptrToSymbol table uses key 0+
      //printSymbols();
      return out;
    }
  }
  else{
    char* p = lexeme;
    struct machOut out = {f, 0, lexeme, rw.tokenResWord, rw.attributeResWord};
    return out;
  }
}
