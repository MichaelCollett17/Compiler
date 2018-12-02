#include <stdio.h>
#include <stdbool.h>
#include "../tokens.h"
#include "../LinkedLists/TokenLLV2.h"
#include "./productions.h"
#include "../reservedWords.h"
#include "../Parser.h"

void statement_list(){
  struct resWord call = getTokAndAtt("call");
  struct resWord begin = getTokAndAtt("begin");
  struct resWord while_ = getTokAndAtt("while");
  struct resWord if_ = getTokAndAtt("if");
  //id call begin while if
  if((tok.tokenType == ID) || (tok.tokenType==call.tokenResWord) ||
    ((tok.tokenType == begin.tokenResWord) && (tok.attribute == begin.attributeResWord))
    || ((tok.tokenType == while_.tokenResWord) && (tok.attribute == while_.attributeResWord))
    || ((tok.tokenType == if_.tokenResWord) && (tok.attribute == if_.attributeResWord))){
    statement();
    statement_list_prime();
  }
  else{
    //end
    struct resWord end = getTokAndAtt("end");
    writeSyntaxError("ID, call, begin, while, if",tok.lexeme);
    while((tok.tokenType != EOFTOKEN) &&
    !((tok.tokenType == end.tokenResWord) && (tok.attribute == end.attributeResWord))){
      getToken();
    }
  }
}
