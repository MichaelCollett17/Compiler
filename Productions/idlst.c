#include <stdio.h>
#include <stdbool.h>
#include "../tokens.h"
//#include "../LinkedLists/TokenLinkedList.h"
#include "../LinkedLists/TokenLLV2.h"
#include "./productions.h"
#include "../reservedWords.h"
#include "../Parser.h"

void idlst(){
  if(tok.tokenType == ID){
    match(ID, 0, "ID");
    idlst_prime();
  }
  else{
    writeSyntaxError("ID",tok.lexeme);
    while((tok.tokenType != EOFTOKEN) &&
    !((tok.tokenType == GROUPING) && (tok.attribute == RPAR))){
      getToken();
    }
  }
}
