#include <stdio.h>
#include <stdbool.h>
#include "../tokens.h"
#include "../LinkedLists/TokenLLV2.h"
#include "./productions.h"
#include "../reservedWords.h"
#include "../Parser.h"
#include "../GNBNTree/GNBNNode.h"

void subprogram_head(){
  struct resWord procedure = getTokAndAtt("procedure");
  if(tok.tokenType == procedure.tokenResWord){
    match(procedure.tokenResWord, procedure.attributeResWord, procedure.lexResWord);
    char *idlex = match(ID, 0, "ID");
    //semstart
    checkAddGreenNode(idlex,PPNAME);
    offset = 0;
    //semend
    subprogram_head_prime();
  }
  else{
    writeSyntaxError("procedure", tok.lexeme);
    struct resWord begin = getTokAndAtt("begin");
    struct resWord var = getTokAndAtt("var");
    while(tok.tokenType != EOFTOKEN && (!((tok.tokenType == begin.tokenResWord)
      &&(tok.attribute == begin.attributeResWord))) && (!(tok.tokenType == procedure.tokenResWord))
      &&(tok.tokenType != var.tokenResWord)){
      getToken();
    }
  }
}
