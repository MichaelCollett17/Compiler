#include <stdio.h>
#include <stdbool.h>
#include "../tokens.h"
#include "../LinkedLists/TokenLLV2.h"
#include "./productions.h"
#include "../reservedWords.h"
#include "../Parser.h"

void simple_expression_prime(){
  struct resWord do_ = getTokAndAtt("do");
  struct resWord then = getTokAndAtt("then");
  struct resWord end = getTokAndAtt("end");
  struct resWord else_ = getTokAndAtt("else");
  struct resWord or_ = getTokAndAtt("or");
  if(tok.tokenType == ADDOP){
    if(tok.attribute == ADD){
      match(ADDOP, ADD, "+");
    }
    else if(tok.attribute == or_.attributeResWord){
      match(or_.tokenResWord,or_.attributeResWord, or_.lexResWord);
    }
    else{
      match(ADDOP, SUB, "-");
    }
    term();
    simple_expression_prime();
  }
  else if((((tok.tokenType == GROUPING) && (tok.attribute == RBRACK))) ||
    (((tok.tokenType == do_.tokenResWord) && (tok.attribute == do_.attributeResWord))) ||
    (((tok.tokenType == then.tokenResWord) && (tok.attribute == then.attributeResWord))) ||
    (((tok.tokenType == PUNCTUATION) && (tok.attribute == COMMA))) ||
    (((tok.tokenType == GROUPING) && (tok.attribute == RPAR))) ||
    (((tok.tokenType == PUNCTUATION) && (tok.attribute == SEMICOLON))) ||
    (((tok.tokenType == end.tokenResWord) && (tok.attribute == end.attributeResWord))) ||
    (((tok.tokenType == else_.tokenResWord) && (tok.attribute == else_.attributeResWord))) ||
    ((tok.tokenType == RELOP))){
    return;
  }
  else{
    writeSyntaxError("addop relop do then ] , ) ; end else", tok.lexeme);
    while((tok.tokenType != EOFTOKEN) &&
      (!((tok.tokenType == GROUPING) && (tok.attribute == RBRACK))) &&
      (!((tok.tokenType == do_.tokenResWord) && (tok.attribute == do_.attributeResWord))) &&
      (!((tok.tokenType == then.tokenResWord) && (tok.attribute == then.attributeResWord))) &&
      (!((tok.tokenType == PUNCTUATION) && (tok.attribute == COMMA))) &&
      (!((tok.tokenType == GROUPING) && (tok.attribute == RPAR))) &&
      (!((tok.tokenType == PUNCTUATION) && (tok.attribute == SEMICOLON))) &&
      (!((tok.tokenType == end.tokenResWord) && (tok.attribute == end.attributeResWord))) &&
      (!((tok.tokenType == else_.tokenResWord) && (tok.attribute == else_.attributeResWord))) &&
      ((tok.tokenType != RELOP))){
        getToken();
    }
  }
}
