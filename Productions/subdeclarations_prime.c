#include <stdio.h>
#include "../tokens.h"
#include "../LinkedLists/TokenLLV2.h"
#include "./productions.h"
#include "../reservedWords.h"
#include "../Parser.h"

void subdeclarations_prime(){
  struct resWord procedure = getTokAndAtt("procedure");
  struct resWord begin = getTokAndAtt("begin");
  if(tok.tokenType == procedure.tokenResWord){
    subdeclaration();
    match(PUNCTUATION,SEMICOLON, ";");
    subdeclarations_prime();
  }
  else if((tok.tokenType == begin.tokenResWord)&&(tok.attribute == begin.attributeResWord)){
    return;
  }
  else{
    writeSyntaxError("procedure or begin", tok.lexeme);
    while(tok.tokenType != EOFTOKEN && !((tok.tokenType == begin.tokenResWord)&&(tok.attribute == begin.attributeResWord))){
      getToken();
    }
  }
}
