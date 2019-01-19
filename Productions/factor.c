#include <stdio.h>
#include <stdbool.h>
#include "../tokens.h"
#include "../LinkedLists/TokenLLV2.h"
#include "./productions.h"
#include "../reservedWords.h"
#include "../Parser.h"
#include "../GNBNTree/GNBNNode.h"

int factor(){
  struct resWord not = getTokAndAtt("not");
  if(tok.tokenType == ID){
    idtype = getType(tok.lexeme);
    match(ID, 0, "ID");
    int fac_prime_type = factor_prime(idtype);
    return fac_prime_type;
  }
  else if((tok.tokenType == INT) || (tok.tokenType == SREAL) || (tok.tokenType == LREAL) ){
    int type = INT;
    if((tok.tokenType == SREAL) || (tok.tokenType == LREAL)){
      type = REAL;
    }
    matchNum();
    return type;
  }
  else if((tok.tokenType == GROUPING) && (tok.attribute == LPAR)){
    match(GROUPING,LPAR,"(");
    int type = expression();
    match(GROUPING,RPAR,")");
    return type;
  }
  else if((tok.tokenType == not.tokenResWord) && (tok.attribute == not.attributeResWord)){
    match(not.tokenResWord, not.attributeResWord, not.lexResWord);
    int type = factor();
    if(type == BOOL){
      return type;
    }
    else{
      writeSemanticError("a boolean must follow *not*");
      return ERR;
    }
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
    return ERR;
  }
}
