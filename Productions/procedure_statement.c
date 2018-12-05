#include <stdio.h>
#include <stdbool.h>
#include "../tokens.h"
#include "../LinkedLists/TokenLLV2.h"
#include "./productions.h"
#include "../reservedWords.h"
#include "../Parser.h"

void procedure_statement(){
  struct resWord call = getTokAndAtt("call");
  if(tok.tokenType==call.tokenResWord){
    match(call.tokenResWord, call.attributeResWord, call.lexResWord);
    match(ID, 0 ,"ID");
    procedure_statement_prime();
  }
  else{
    //; end else
    struct resWord else_ = getTokAndAtt("else");
    struct resWord end = getTokAndAtt("end");
    writeSyntaxError("call",tok.lexeme);
    while((tok.tokenType != EOFTOKEN) &&
    (!((tok.tokenType == end.tokenResWord) && (tok.attribute == end.attributeResWord)))
    && (!((tok.tokenType == else_.tokenResWord) && (tok.attribute == else_.attributeResWord)))
    && (!((tok.tokenType == PUNCTUATION) && (tok.attribute == SEMICOLON)))){
      getToken();
    }
  }
}
