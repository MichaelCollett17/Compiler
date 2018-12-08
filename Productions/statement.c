#include <stdio.h>
#include <stdbool.h>
#include "../tokens.h"
#include "../LinkedLists/TokenLLV2.h"
#include "./productions.h"
#include "../reservedWords.h"
#include "../Parser.h"

void statement(){
  struct resWord call = getTokAndAtt("call");
  struct resWord begin = getTokAndAtt("begin");
  struct resWord while_ = getTokAndAtt("while");
  struct resWord if_ = getTokAndAtt("if");
  //id
  if(tok.tokenType == ID){
    variable();
    match(ASSIGNOP, 0, ":=");
    expression();
  }
  //call
  else if(tok.tokenType==call.tokenResWord){
    procedure_statement();
  }
  //begin
  else if((tok.tokenType == begin.tokenResWord) && (tok.attribute == begin.attributeResWord)){
    compound_statement();
  }
  //while
  else if((tok.tokenType == while_.tokenResWord) && (tok.attribute == while_.attributeResWord)){
    struct resWord do_ = getTokAndAtt("do");
    match(while_.tokenResWord, while_.attributeResWord,while_.lexResWord);
    expression();
    match(do_.tokenResWord, do_.attributeResWord, do_.lexResWord);
    statement();
  }
  //if
  else if((tok.tokenType == if_.tokenResWord) && (tok.attribute == if_.attributeResWord)){
    struct resWord then = getTokAndAtt("then");
    match(if_.tokenResWord, if_.attributeResWord, if_.lexResWord);
    expression();
    match(then.tokenResWord,then.attributeResWord,then.lexResWord);
    statement();
    statement_prime();
  }
  else{
    //; end else
    struct resWord end = getTokAndAtt("end");
    struct resWord else_ = getTokAndAtt("else");
    writeSyntaxError("ID, call, begin, while, if",tok.lexeme);
    while((tok.tokenType != EOFTOKEN) &&
    (!((tok.tokenType == end.tokenResWord) && (tok.attribute == end.attributeResWord)))
    && (!((tok.tokenType == else_.tokenResWord) && (tok.attribute == else_.attributeResWord)))
    && (!((tok.tokenType == PUNCTUATION) && (tok.attribute == SEMICOLON)))){
      getToken();
    }
  }
}
