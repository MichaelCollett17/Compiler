#include <stdio.h>
#include <stdbool.h>
#include "../tokens.h"
#include "../LinkedLists/TokenLLV2.h"
#include "./productions.h"
#include "../reservedWords.h"
#include "../Parser.h"

void expression(){
  struct resWord not = getTokAndAtt("not");
  //id num ( not + -
  if((tok.tokenType==ID) || (tok.tokenType == INT) || (tok.tokenType == SREAL)
  || (tok.tokenType == LREAL) || ((tok.tokenType == GROUPING) && (tok.attribute == LPAR))
  || ((tok.tokenType == not.tokenResWord) && (tok.attribute == not.attributeResWord))
  || (tok.tokenType == ADDOP && tok.attribute == ADD)
  || (tok.tokenType == ADDOP && tok.attribute == SUB)){
    simple_expression();
    expression_prime();
  }
  else{
    struct resWord do_ = getTokAndAtt("do");
    struct resWord then = getTokAndAtt("then");
    struct resWord end = getTokAndAtt("end");
    struct resWord else_ = getTokAndAtt("else");
    writeSyntaxError("ID, num, (, not +, -", tok.lexeme);
    while((tok.tokenType != EOFTOKEN) &&
    (!((tok.tokenType == GROUPING) && (tok.attribute == RBRACK))) &&
    (!((tok.tokenType == do_.tokenResWord) && (tok.attribute == do_.attributeResWord))) &&
    (!((tok.tokenType == then.tokenResWord) && (tok.attribute == then.attributeResWord))) &&
    (!((tok.tokenType == PUNCTUATION) && (tok.attribute == COMMA))) &&
    (!((tok.tokenType == GROUPING) && (tok.attribute == RPAR))) &&
    (!((tok.tokenType == PUNCTUATION) && (tok.attribute == SEMICOLON))) &&
    (!((tok.tokenType == end.tokenResWord) && (tok.attribute == end.attributeResWord))) &&
    (!((tok.tokenType == else_.tokenResWord) && (tok.attribute == else_.attributeResWord)))){
      getToken();
    }
  }
}
