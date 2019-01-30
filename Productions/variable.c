#include <stdio.h>
#include <stdbool.h>
#include "../tokens.h"
#include "../LinkedLists/TokenLLV2.h"
#include "./productions.h"
#include "../reservedWords.h"
#include "../Parser.h"
#include "../GNBNTree/GNBNNode.h"

int variable(){
  if(tok.tokenType == ID){
    char * idlex = match(ID, 0, "ID");
    int type_id = getType(idlex);
    int type_ = variable_prime(type_id);
    return type_;
  }
  else{
    writeSyntaxError("ID",tok.lexeme);
    while((tok.tokenType != EOFTOKEN)
    && (tok.tokenType != ASSIGNOP)){
      getToken();
    }
    return ERR;
  }
}
