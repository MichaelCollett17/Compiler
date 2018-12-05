#include <stdio.h>
#include <stdbool.h>
#include "../tokens.h"
#include "../LinkedLists/TokenLLV2.h"
#include "./productions.h"
#include "../reservedWords.h"
#include "../Parser.h"

void expression_list(){
  struct resWord not = getTokAndAtt("not");
  //id num ( not + -
  if((tok.tokenType==ID) || (tok.tokenType == INT) || (tok.tokenType == SREAL)
  || (tok.tokenType == LREAL) || ((tok.tokenType == GROUPING) && (tok.attribute == LPAR))
  || ((tok.tokenType == not.tokenResWord) && (tok.attribute == not.attributeResWord))
  || (tok.tokenType == ADDOP && tok.attribute == ADD)
  || (tok.tokenType == ADDOP && tok.attribute == SUB)){
    expression();
    expression_list_prime();
  }
  else{
    writeSyntaxError("id num ( not + -", tok.lexeme);
    while((tok.tokenType != EOFTOKEN) &&
    !((tok.tokenType == GROUPING) && (tok.attribute == RPAR))){
      getToken();
    }
  }

}
