#include <stdio.h>
#include <stdbool.h>
#include "../tokens.h"
#include "../LinkedLists/TokenLLV2.h"
#include "./productions.h"
#include "../reservedWords.h"
#include "../Parser.h"

void compound_statement(){
  struct resWord begin = getTokAndAtt("begin");
  if((tok.tokenType == begin.tokenResWord)
    &&(tok.attribute == begin.attributeResWord)){
    match(begin.tokenResWord, begin.attributeResWord, begin.lexResWord);
    compound_statement_prime();
  }
  else{
    struct resWord end = getTokAndAtt("end");
    struct resWord else_ = getTokAndAtt("else");
    writeSyntaxError(begin.lexResWord, tok.lexeme);
    while((tok.tokenType != EOFTOKEN) &&
      (!((tok.tokenType == end.tokenResWord)&&(tok.attribute == end.attributeResWord))) &&
      (!((tok.tokenType == else_.tokenResWord)&&(tok.attribute == else_.attributeResWord))) &&
      (!((tok.tokenType == PUNCTUATION)&&(tok.attribute == PERIOD))) &&
      (!((tok.tokenType == PUNCTUATION)&&(tok.attribute == SEMICOLON)))){
      getToken();
    }
  }
}
