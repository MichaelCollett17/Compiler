#include <stdio.h>
#include <stdbool.h>
#include "../tokens.h"
#include "../LinkedLists/TokenLLV2.h"
#include "./productions.h"
#include "../reservedWords.h"
#include "../Parser.h"

void sign(){
  if(tok.tokenType == ADDOP && tok.attribute == ADD){
    match(ADDOP, ADD, "+");
  }
  else if(tok.tokenType == ADDOP && tok.attribute == SUB){
    match(ADDOP, ADD, "-");
  }
  else{
    writeSyntaxError("+/-", tok.lexeme);
    struct resWord not = getTokAndAtt("not");
    while((tok.tokenType != EOFTOKEN) &&
    (tok.tokenType!=ID) && (tok.tokenType != INT) && (tok.tokenType != SREAL)
    && (tok.tokenType != LREAL) && (!((tok.tokenType == GROUPING) && (tok.attribute == LPAR)))
    && (!((tok.tokenType == not.tokenResWord) && (tok.attribute == not.attributeResWord)))){
      getToken();
    }
  }
}
