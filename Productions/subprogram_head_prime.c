#include <stdio.h>
#include <stdbool.h>
#include "../tokens.h"
#include "../LinkedLists/TokenLLV2.h"
#include "./productions.h"
#include "../reservedWords.h"
#include "../Parser.h"

void subprogram_head_prime(){
  if((tok.tokenType == PUNCTUATION) && (tok.attribute == SEMICOLON)){
    match(PUNCTUATION,SEMICOLON, ";");
  }
  else if((tok.tokenType == GROUPING)&&(tok.attribute == LPAR)){
    arguments();
    match(PUNCTUATION,SEMICOLON, ";");
  }
  else{
    writeSyntaxError("; or )", tok.lexeme);
    struct resWord procedure = getTokAndAtt("procedure");
    struct resWord begin = getTokAndAtt("begin");
    struct resWord var = getTokAndAtt("var");
    while(tok.tokenType != EOFTOKEN && (!((tok.tokenType == begin.tokenResWord)
      &&(tok.attribute == begin.attributeResWord))) && (!(tok.tokenType == procedure.tokenResWord))
      &&(tok.tokenType != var.tokenResWord)){
      getToken();
    }
  }
}
