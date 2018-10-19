#include <stdio.h>
#include "../tokens.h"
//#include "../LinkedLists/TokenLinkedList.h"
#include "../LinkedLists/TokenLLV2.h"
#include "productions.h"
#include "../Parser.h"

void match(int tokenToMatch, int attributeToMatch, char *lexeme){
  if((tok.tokenType == tokenToMatch)&& (tok.attribute == attributeToMatch) &&(tok.tokenType != EOFTOKEN)){
    tok = getNextToken();
  }
  else if((tok.tokenType == tokenToMatch) && (tok.attribute == attributeToMatch) && (tok.tokenType == EOFTOKEN)){
    printf("TODO: END OF PARSE!");
  }
  else{
    writeSyntaxError(lexeme, tok.lexeme);
    tok = getNextToken();
  }
}
