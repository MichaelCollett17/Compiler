#include <stdio.h>
#include <stdbool.h>
#include "../tokens.h"
//#include "../LinkedLists/TokenLinkedList.h"
#include "../LinkedLists/TokenLLV2.h"
#include "./productions.h"
#include "../reservedWords.h"
#include "../Parser.h"

void idlst_prime(){
  if((tok.tokenType == PUNCTUATION) && (tok.attribute == COMMA)){
    match(PUNCTUATION, COMMA, ",");
    match(ID, 0, "ID");
    idlst_prime();
  }
  else if((tok.tokenType == GROUPING)&&(tok.attribute == RPAR)){
    return;
  }
  else{
    writeSyntaxError("ID",tok.lexeme);
    while((tok.tokenType != EOFTOKEN) ||
    !((tok.tokenType == GROUPING) && (tok.attribute == RPAR))){
      getToken();
    }
  }
}
