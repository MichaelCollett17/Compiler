#include <stdio.h>
#include <stdbool.h>
#include "../tokens.h"
#include "../LinkedLists/TokenLLV2.h"
#include "./productions.h"
#include "../reservedWords.h"
#include "../Parser.h"

void subdeclaration(){
  struct resWord procedure = getTokAndAtt("procedure");
  if(tok.tokenType == procedure.tokenResWord){
    subprogram_head();
    subdeclaration_prime();
  }
  else{
    writeSyntaxError("procedure", tok.lexeme);
    while(tok.tokenType != EOFTOKEN && (!(tok.attribute==SEMICOLON))){
      getToken();
    }
  }
}
