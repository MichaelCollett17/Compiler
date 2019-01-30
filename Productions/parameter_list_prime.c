#include <stdio.h>
#include <stdbool.h>
#include "../tokens.h"
#include "../LinkedLists/TokenLLV2.h"
#include "./productions.h"
#include "../reservedWords.h"
#include "../Parser.h"
#include "../GNBNTree/GNBNNode.h"

void parameter_list_prime(){
  if((tok.tokenType == PUNCTUATION) && (tok.attribute == SEMICOLON)){
    match(PUNCTUATION,SEMICOLON, ";");
    char *idlex = match(ID, 0, "ID");
    match(TYPE, 0, ":");
    struct tw type_ = type();
    checkAddBlueNode(idlex,type_.t);
    parameter_list_prime();
  }
  else if(tok.tokenType == GROUPING && tok.attribute == RPAR){
    return;
  }
  else{
    writeSyntaxError("; )",tok.lexeme);
    while((tok.tokenType != EOFTOKEN) &&
    !((tok.tokenType == GROUPING) && (tok.attribute == RPAR))){
      getToken();
    }
  }
}
