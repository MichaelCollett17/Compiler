#include <stdio.h>
#include <stdbool.h>
#include "../tokens.h"
#include "../LinkedLists/TokenLLV2.h"
#include "./productions.h"
#include "../reservedWords.h"
#include "../Parser.h"

void factor(){
  struct resWord not = getTokAndAtt("not");
  if(tok.tokenType == ID){
    match(ID, 0, "ID");
    factor_prime();
  }
  else if((tok.tokenType == INT) || (tok.tokenType == SREAL) || (tok.tokenType == LREAL) ){
    matchNum();
  }
  else if((tok.tokenType == GROUPING) && (tok.attribute == LPAR)){
    match(GROUPING,LPAR,"(");
    expression();
    match(GROUPING,RPAR,")");
  }
  else if((tok.tokenType == not.tokenResWord) && (tok.attribute == not.attributeResWord)){
    match(not.tokenResWord, not.attributeResWord, not.lexResWord);
    factor();
  }
  else{
    writeSyntaxError("id num not (", tok.lexeme);
    struct resWord do_ = getTokAndAtt("do");
    struct resWord then = getTokAndAtt("then");
    struct resWord end = getTokAndAtt("end");
    struct resWord else_ = getTokAndAtt("else");
    while((tok.tokenType != EOFTOKEN) &&
      (!((tok.tokenType == GROUPING) && (tok.attribute == RBRACK))) &&
      (!((tok.tokenType == do_.tokenResWord) && (tok.attribute == do_.attributeResWord))) &&
      (!((tok.tokenType == then.tokenResWord) && (tok.attribute == then.attributeResWord))) &&
      (!((tok.tokenType == PUNCTUATION) && (tok.attribute == COMMA))) &&
      (!((tok.tokenType == GROUPING) && (tok.attribute == RPAR))) &&
      (!((tok.tokenType == PUNCTUATION) && (tok.attribute == SEMICOLON))) &&
      (!((tok.tokenType == end.tokenResWord) && (tok.attribute == end.attributeResWord))) &&
      (!((tok.tokenType == else_.tokenResWord) && (tok.attribute == else_.attributeResWord))) &&
      ((tok.tokenType != RELOP)) &&
      (tok.tokenType != ADDOP) &&
      (tok.tokenType != MULOP)){
        getToken();
    }
  }
}
