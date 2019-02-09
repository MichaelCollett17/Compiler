#include <stdio.h>
#include "../tokens.h"
#include "../LinkedLists/TokenLLV2.h"
#include "./productions.h"
#include "../reservedWords.h"
#include "../Parser.h"
#include "../GNBNTree/GNBNNode.h"

void subdeclarations(){
  struct resWord procedure = getTokAndAtt("procedure");
  if(tok.tokenType == procedure.tokenResWord){
    subdeclaration();
    match(PUNCTUATION,SEMICOLON, ";");
    popStack();
    subdeclarations_prime();
  }
  else{
    struct resWord begin = getTokAndAtt("begin");
    writeSyntaxError("procedure", tok.lexeme);
    while(tok.tokenType != EOFTOKEN && !((tok.tokenType == begin.tokenResWord)&&(tok.attribute == begin.attributeResWord))){
      getToken();
    }
  }
}
