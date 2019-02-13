#include <stdio.h>
#include <stdbool.h>
#include "../tokens.h"
#include "../LinkedLists/TokenLLV2.h"
#include "./productions.h"
#include "../reservedWords.h"
#include "../Parser.h"
#include "../GNBNTree/GNBNNode.h"

void idlst_prime(){
  if((tok.tokenType == PUNCTUATION) && (tok.attribute == COMMA)){
    match(PUNCTUATION, COMMA, ",");
    char *id_lex = match(ID, 0, "ID");
    checkAddBlueNode(id_lex, PGPARAM, offset, 0);
    idlst_prime();
  }
  else if((tok.tokenType == GROUPING)&&(tok.attribute == RPAR)){
    return;//nop
  }
  else{
    writeSyntaxError("ID",tok.lexeme);
    while((tok.tokenType != EOFTOKEN) &&
    !((tok.tokenType == GROUPING) && (tok.attribute == RPAR))){
      getToken();
    }
  }
}
