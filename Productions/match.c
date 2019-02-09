#include <stdio.h>
#include <stdlib.h>
#include "../tokens.h"
//#include "../LinkedLists/TokenLinkedList.h"
#include "../LinkedLists/TokenLLV2.h"
#include "productions.h"
#include "../Parser.h"

char* match(int tokenToMatch, int attributeToMatch, char *lexeme){
  if((tok.tokenType == tokenToMatch)&& (tok.attribute == attributeToMatch) &&(tok.tokenType != EOFTOKEN)){
    char *lex_out = tok.lexeme;
    getToken();
    return lex_out;
  }
  else if((tok.tokenType == tokenToMatch) && (tok.attribute == attributeToMatch) && (tok.tokenType == EOFTOKEN)){
    printf("TODO: END OF PARSE!\n");
    return NULL;
  }
  else{
    writeSyntaxError(lexeme, tok.lexeme);
    getToken();
    return NULL;
  }
}

int matchNum(){//return val or -1 if not an int
  if((tok.tokenType == INT) || (tok.tokenType == SREAL) || (tok.tokenType == LREAL)){
    int out;
    if(tok.tokenType == INT){
      out = atoi(tok.lexeme);
    }
    else{
      out = -1;
    }
    getToken();
    return out;
  }
  else{
    writeSyntaxError("a number", tok.lexeme);
    getToken();
    return -1;
  }
}
