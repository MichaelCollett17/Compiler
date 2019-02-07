#include <stdio.h>
#include <stdbool.h>
#include "../tokens.h"
#include "../LinkedLists/TokenLLV2.h"
#include "./productions.h"
#include "../reservedWords.h"
#include "../Parser.h"
#include "../GNBNTree/GNBNNode.h"

int variable_prime(int i){
  if((tok.tokenType == GROUPING) && (tok.attribute == LBRACK)){
    match(GROUPING,LBRACK, "[");
    int etype = expression();
    match(GROUPING,RBRACK, "]");
    if((etype == ERR)||(i == ERR)){
      return ERR;
    }
    else if(etype == INTEGER){
      if(i == AINT){
        return INTEGER;
      }
      else if(i == AREAL){
        return REAL;
      }
      else{
        writeSemanticError("ID is not of type array");
        return ERR;
      }
    }
    else{
      writeSemanticError("expression inside brackets requires an integer");
      return ERR;
    }
  }
  else if(tok.tokenType == ASSIGNOP){
    return i;
  }
  else{
    writeSyntaxError("[, :=",tok.lexeme);
    while((tok.tokenType != EOFTOKEN)
    && (tok.tokenType != ASSIGNOP)){
      getToken();
    }
    return ERR;
  }
}
