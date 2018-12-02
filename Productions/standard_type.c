#include <stdio.h>
#include <stdbool.h>
#include "../tokens.h"
#include "../LinkedLists/TokenLLV2.h"
#include "./productions.h"
#include "../reservedWords.h"
#include "../Parser.h"

void standard_type(){
  struct resWord real = getTokAndAtt("real");
  struct resWord integer = getTokAndAtt("integer");
  if(tok.tokenType == integer.tokenResWord){
    match(integer.tokenResWord, integer.attributeResWord, integer.lexResWord);
  }
  else if(tok.tokenType == real.tokenResWord){
    match(real.tokenResWord, real.attributeResWord, real.lexResWord);
  }
  else{
    //synch
    writeSyntaxError("real or integer", tok.lexeme);
    while(tok.tokenType != EOFTOKEN && (!((tok.tokenType == GROUPING) && (tok.attribute == RPAR))) && (!((tok.tokenType == PUNCTUATION) && (tok.attribute == SEMICOLON)))){
      getToken();
    }
  }
}
