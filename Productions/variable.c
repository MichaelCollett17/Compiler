#include <stdio.h>
#include <stdbool.h>
#include "../tokens.h"
#include "../LinkedLists/TokenLLV2.h"
#include "./productions.h"
#include "../reservedWords.h"
#include "../Parser.h"

void variable(){
  if(tok.tokenType == ID){
    match(ID, 0, "ID");
    variable_prime();
  }
  else{
    writeSyntaxError("ID",tok.lexeme);
    while((tok.tokenType != EOFTOKEN)
    && (tok.tokenType != ASSIGNOP)){
      getToken();
    }
  }
}
