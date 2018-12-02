#include <stdio.h>
#include <stdbool.h>
#include "../tokens.h"
#include "../LinkedLists/TokenLLV2.h"
#include "./productions.h"
#include "../reservedWords.h"
#include "../Parser.h"

void type(){
  struct resWord array = getTokAndAtt("array");
  struct resWord real = getTokAndAtt("real");
  struct resWord integer = getTokAndAtt("integer");
  struct resWord of = getTokAndAtt("of");
  if(tok.tokenType == array.tokenResWord){
    match(array.tokenResWord, array.attributeResWord, "array");
    match(GROUPING, LBRACK, "[");
    matchNum();
    match(ARRAY, 0, "..");
    matchNum();
    match(GROUPING, RBRACK, "]");
    match(of.tokenResWord, of.attributeResWord, of.lexResWord);
    standard_type();
  }
  else if((tok.tokenType == real.tokenResWord) ||
          (tok.tokenType == integer.tokenResWord)){
    standard_type();
  }
  else{
    //synch
    writeSyntaxError("array, real or integer", tok.lexeme);
    while(tok.tokenType != EOFTOKEN && (!((tok.tokenType == GROUPING) && (tok.attribute == RPAR))) && (!((tok.tokenType == PUNCTUATION) && (tok.attribute == SEMICOLON)))){
      getToken();
    }
  }
}
