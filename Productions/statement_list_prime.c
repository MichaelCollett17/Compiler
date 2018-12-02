#include <stdio.h>
#include <stdbool.h>
#include "../tokens.h"
#include "../LinkedLists/TokenLLV2.h"
#include "./productions.h"
#include "../reservedWords.h"
#include "../Parser.h"

void statement_list_prime(){
  struct resWord end = getTokAndAtt("end");
  if((tok.tokenType == PUNCTUATION) && (tok.attribute == SEMICOLON)){
    match(PUNCTUATION,SEMICOLON, ";");
    statement();
    statement_list_prime();
  }
  else if((tok.tokenType == end.tokenResWord) && (tok.attribute == end.attributeResWord)){
    return;
  }
  else{
    writeSyntaxError("ID, call, begin, while, if",tok.lexeme);
    while((tok.tokenType != EOFTOKEN) &&
    !((tok.tokenType == end.tokenResWord) && (tok.attribute == end.attributeResWord))){
      getToken();
    }
  }
}
