#include <stdio.h>
#include <stdbool.h>
#include "../tokens.h"
#include "../LinkedLists/TokenLLV2.h"
#include "./productions.h"
#include "../reservedWords.h"
#include "../Parser.h"

void arguments(){
  if((tok.tokenType == GROUPING) && (tok.attribute == LPAR)){
    match(GROUPING, LPAR, "(");
    parameter_list();
    match(GROUPING, RPAR, ")");
  }
  else{
    writeSyntaxError("(", tok.lexeme);
    while(tok.tokenType != EOFTOKEN && (!(tok.attribute==SEMICOLON))){
      getToken();
    }
  }
}
