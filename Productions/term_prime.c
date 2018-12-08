#include <stdio.h>
#include <stdbool.h>
#include "../tokens.h"
#include "../LinkedLists/TokenLLV2.h"
#include "./productions.h"
#include "../reservedWords.h"
#include "../Parser.h"

void term_prime(){
  struct resWord do_ = getTokAndAtt("do");
  struct resWord then = getTokAndAtt("then");
  struct resWord end = getTokAndAtt("end");
  struct resWord else_ = getTokAndAtt("else");
  struct resWord div_ = getTokAndAtt("div");
  struct resWord mod_ = getTokAndAtt("mod");
  struct resWord and_ = getTokAndAtt("and");
  if(tok.tokenType==MULOP){
    if(tok.attribute==MULT){
      match(MULOP,MULT,"*");
    }
    else if(tok.attribute == div_.attributeResWord){
      match(div_.tokenResWord,div_.attributeResWord,div_.lexResWord);
    }
    else if(tok.attribute == mod_.attributeResWord){
      match(mod_.tokenResWord,mod_.attributeResWord,mod_.lexResWord);
    }
    else if(tok.attribute == and_.attributeResWord){
      match(and_.tokenResWord,and_.attributeResWord,and_.lexResWord);
    }
    else{
      match(MULOP,DIV,"/");
    }
    factor();
    term_prime();
  }
  else if((((tok.tokenType == GROUPING) && (tok.attribute == RBRACK))) ||
    (((tok.tokenType == do_.tokenResWord) && (tok.attribute == do_.attributeResWord))) ||
    (((tok.tokenType == then.tokenResWord) && (tok.attribute == then.attributeResWord))) ||
    (((tok.tokenType == PUNCTUATION) && (tok.attribute == COMMA))) ||
    (((tok.tokenType == GROUPING) && (tok.attribute == RPAR))) ||
    (((tok.tokenType == PUNCTUATION) && (tok.attribute == SEMICOLON))) ||
    (((tok.tokenType == end.tokenResWord) && (tok.attribute == end.attributeResWord))) ||
    (((tok.tokenType == else_.tokenResWord) && (tok.attribute == else_.attributeResWord))) ||
    ((tok.tokenType == RELOP)) ||
    (tok.tokenType == ADDOP)){
    return;
  }
  else{
    writeSyntaxError("mulop addop relop do then ] , ) ; end else", tok.lexeme);
    while((tok.tokenType != EOFTOKEN) &&
      (!((tok.tokenType == GROUPING) && (tok.attribute == RBRACK))) &&
      (!((tok.tokenType == do_.tokenResWord) && (tok.attribute == do_.attributeResWord))) &&
      (!((tok.tokenType == then.tokenResWord) && (tok.attribute == then.attributeResWord))) &&
      (!((tok.tokenType == PUNCTUATION) && (tok.attribute == COMMA))) &&
      (!((tok.tokenType == GROUPING) && (tok.attribute == RPAR))) &&
      (!((tok.tokenType == PUNCTUATION) && (tok.attribute == SEMICOLON))) &&
      (!((tok.tokenType == end.tokenResWord) && (tok.attribute == end.attributeResWord))) &&
      (!((tok.tokenType == else_.tokenResWord) && (tok.attribute == else_.attributeResWord))) &&
      ((tok.tokenType != RELOP)) &&
      (tok.tokenType != ADDOP)){
        getToken();
    }
  }
}
