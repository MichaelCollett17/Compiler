#include <stdio.h>
#include <stdbool.h>
#include "../tokens.h"
#include "../LinkedLists/TokenLLV2.h"
#include "./productions.h"
#include "../reservedWords.h"
#include "../Parser.h"

void variable_prime(){
  if((tok.tokenType == GROUPING) && (tok.attribute == LBRACK)){
    match(GROUPING,LBRACK, "[");
    //expression();
    match(GROUPING,RBRACK, "]");
  }
  else if(tok.tokenType == ASSIGNOP){
    return;
  }
  else{
    writeSyntaxError("[, :=",tok.lexeme);
    while((tok.tokenType != EOFTOKEN)
    && (tok.tokenType != ASSIGNOP)){
      getToken();
    }
  }
}
