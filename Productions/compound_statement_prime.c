#include <stdio.h>
#include <stdbool.h>
#include "../tokens.h"
#include "../LinkedLists/TokenLLV2.h"
#include "./productions.h"
#include "../reservedWords.h"
#include "../Parser.h"

void compound_statement_prime(){
  struct resWord end = getTokAndAtt("end");
  struct resWord id = getTokAndAtt("id");
  struct resWord call = getTokAndAtt("call");
  struct resWord begin = getTokAndAtt("begin");
  struct resWord while_ = getTokAndAtt("while");
  struct resWord if_ = getTokAndAtt("if");
  //id call begin while if
  if(((tok.tokenType == begin.tokenResWord)&&(tok.attribute == begin.attributeResWord)) &&
    ((tok.tokenType == id.tokenResWord)&&(tok.attribute == id.attributeResWord)) &&
    ((tok.tokenType == call.tokenResWord)&&(tok.attribute == call.attributeResWord)) &&
    ((tok.tokenType == while_.tokenResWord)&&(tok.attribute == while_.attributeResWord)) &&
    ((tok.tokenType == if_.tokenResWord)&&(tok.attribute == if_.attributeResWord))){
      optional_statements();
      match(end.tokenResWord, end.attributeResWord, end.lexResWord);
  }
  else if((tok.tokenType == end.tokenResWord)&&(tok.attribute == end.attributeResWord)){//end
    match(end.tokenResWord, end.attributeResWord, end.lexResWord);
  }
  else{//synch $ . ; end else
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
