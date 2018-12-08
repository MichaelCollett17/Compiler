#include <stdio.h>
#include <stdbool.h>
#include "../tokens.h"
#include "../LinkedLists/TokenLLV2.h"
#include "./productions.h"
#include "../reservedWords.h"
#include "../Parser.h"

void statement_prime(){
  struct resWord else_ = getTokAndAtt("else");
  struct resWord end = getTokAndAtt("end");
  if((tok.tokenType == else_.tokenResWord) && (tok.attribute == else_.attributeResWord)){
    match(else_.tokenResWord, else_.attributeResWord, else_.lexResWord);
    statement();
  }
  else if(((tok.tokenType == end.tokenResWord) && (tok.attribute == end.attributeResWord))
  || ((tok.tokenType == else_.tokenResWord) && (tok.attribute == else_.attributeResWord))
  || ((tok.tokenType == PUNCTUATION) && (tok.attribute == SEMICOLON))){
    return;
  }
  else{
    //; end else
    writeSyntaxError("else end ; else",tok.lexeme);
    while((tok.tokenType != EOFTOKEN) &&
    (!((tok.tokenType == end.tokenResWord) && (tok.attribute == end.attributeResWord)))
    && (!((tok.tokenType == else_.tokenResWord) && (tok.attribute == else_.attributeResWord)))
    && (!((tok.tokenType == PUNCTUATION) && (tok.attribute == SEMICOLON)))){
      getToken();
    }
  }
}
