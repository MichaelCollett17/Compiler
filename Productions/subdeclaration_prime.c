#include <stdio.h>
#include <stdbool.h>
#include "../tokens.h"
#include "../LinkedLists/TokenLLV2.h"
#include "./productions.h"
#include "../reservedWords.h"
#include "../Parser.h"

void subdeclaration_prime(){
  struct resWord procedure = getTokAndAtt("procedure");
  struct resWord begin = getTokAndAtt("begin");
  struct resWord var = getTokAndAtt("var");
  if(tok.tokenType == procedure.tokenResWord){
    subdeclarations();
    compound_statement();
  }
  else if((tok.tokenType == begin.tokenResWord)
    &&(tok.attribute == begin.attributeResWord)){
      compound_statement();
  }
  else if(tok.tokenType == var.tokenResWord){
    declarations();
    subdeclaration_prime_prime();
  }
  else{
    writeSyntaxError("procedure, begin or var", tok.lexeme);
    while(tok.tokenType != EOFTOKEN && (!(tok.attribute==SEMICOLON))){
      getToken();
    }
  }
}
