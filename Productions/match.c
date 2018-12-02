#include <stdio.h>
#include "../tokens.h"
//#include "../LinkedLists/TokenLinkedList.h"
#include "../LinkedLists/TokenLLV2.h"
#include "productions.h"
#include "../Parser.h"

void match(int tokenToMatch, int attributeToMatch, char *lexeme){
  if((tok.tokenType == tokenToMatch)&& (tok.attribute == attributeToMatch) &&(tok.tokenType != EOFTOKEN)){
    getToken();
  }
  else if((tok.tokenType == tokenToMatch) && (tok.attribute == attributeToMatch) && (tok.tokenType == EOFTOKEN)){
    printf("TODO: END OF PARSE!");
  }
  else{
    writeSyntaxError(lexeme, tok.lexeme);
    getToken();
  }
}

void matchNum(){
  if((tok.tokenType == INT) || (tok.tokenType == SREAL) || (tok.tokenType == LREAL)){
    getToken();
  }
  else{
    writeSyntaxError("a number", tok.lexeme);
    getToken();
  }
}
