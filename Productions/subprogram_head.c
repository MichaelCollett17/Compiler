#include <stdio.h>
#include <stdbool.h>
#include "../tokens.h"
#include "../LinkedLists/TokenLLV2.h"
#include "./productions.h"
#include "../reservedWords.h"
#include "../Parser.h"

void subprogram_head(){
  struct resWord procedure = getTokAndAtt("procedure");
  if(tok.tokenType == procedure.tokenResWord){
    match(procedure.tokenResWord, procedure.attributeResWord, procedure.lexResWord);
    match(ID, 0, "ID");
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
