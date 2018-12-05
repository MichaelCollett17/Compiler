#include <stdio.h>
#include <stdbool.h>
#include "../tokens.h"
#include "../LinkedLists/TokenLLV2.h"
#include "./productions.h"
#include "../reservedWords.h"
#include "../Parser.h"

void expression_prime(){
  struct resWord do_ = getTokAndAtt("do");
  struct resWord then = getTokAndAtt("then");
  struct resWord end = getTokAndAtt("end");
  struct resWord else_ = getTokAndAtt("else");
  if(tok.tokenType == RELOP){
    if(tok.attribute == LTEQ){
      match(RELOP, LTEQ,"<=");
    }
    else if(tok.attribute == NEQ){
      match(RELOP, NEQ, "<>");
    }
    else if(tok.attribute == LT){
      match(RELOP, LT, "<");
    }
    else if(tok.attribute == EQ){
      match(RELOP, EQ, "=");
    }
    else if(tok.attribute == GTEQ){
      match(RELOP, GTEQ, ">=");
    }
    else{
      match(RELOP, GT, ">");
    }
    simple_expression();
  }
  else if((((tok.tokenType == GROUPING) && (tok.attribute == RBRACK))) ||
  (((tok.tokenType == do_.tokenResWord) && (tok.attribute == do_.attributeResWord))) ||
  (((tok.tokenType == then.tokenResWord) && (tok.attribute == then.attributeResWord))) ||
  (((tok.tokenType == PUNCTUATION) && (tok.attribute == COMMA))) ||
  (((tok.tokenType == GROUPING) && (tok.attribute == RPAR))) ||
  (((tok.tokenType == PUNCTUATION) && (tok.attribute == SEMICOLON))) ||
  (((tok.tokenType == end.tokenResWord) && (tok.attribute == end.attributeResWord))) ||
  (((tok.tokenType == else_.tokenResWord) && (tok.attribute == else_.attributeResWord)))){
    return;
  }
  else{
    writeSyntaxError("RELOP ] do then , ) ; end else", tok.lexeme);
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
