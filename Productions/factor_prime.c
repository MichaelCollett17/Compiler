#include <stdio.h>
#include <stdbool.h>
#include "../tokens.h"
#include "../LinkedLists/TokenLLV2.h"
#include "./productions.h"
#include "../reservedWords.h"
#include "../Parser.h"

int factor_prime(int i){
  struct resWord do_ = getTokAndAtt("do");
  struct resWord then = getTokAndAtt("then");
  struct resWord end = getTokAndAtt("end");
  struct resWord else_ = getTokAndAtt("else");
  if((tok.tokenType == GROUPING) && (tok.attribute == LBRACK)){
    match(GROUPING,LBRACK,"[");
    int etype = expression();
    match(GROUPING,RBRACK,"]");

    //Semantics
    if(etype == INTEGER){
      if(i == AINT){
        printf("Returning Integer here\n");
        return INTEGER;
      }
      else if(i == AREAL){
        return REAL;
      }
      else{
        if(i != ERR){
          writeSemanticError("Not of type array");
        }
        return ERR;
      }
    }
    else if(etype == ERR){
      return etype;
    }
    else{
      writeSemanticError("Array access requires an integer");
      return ERR;
    }
  }
  else if((((tok.tokenType == GROUPING) && (tok.attribute == RBRACK))) ||
    (((tok.tokenType == do_.tokenResWord) && (tok.attribute == do_.attributeResWord))) ||
    (((tok.tokenType == then.tokenResWord) && (tok.attribute == then.attributeResWord))) ||
    (((tok.tokenType == PUNCTUATION) && (tok.attribute == COMMA))) ||
    (((tok.tokenType == GROUPING) && (tok.attribute == RPAR))) ||
    (((tok.tokenType == PUNCTUATION) && (tok.attribute == SEMICOLON))) ||
    (((tok.tokenType == end.tokenResWord) && (tok.attribute == end.attributeResWord))) ||
    (((tok.tokenType == else_.tokenResWord) && (tok.attribute == else_.attributeResWord))) ||
    ((tok.tokenType == RELOP)) ||
    (tok.tokenType == ADDOP) ||
    (tok.tokenType == MULOP)){
      return i;
  }
  else{
    writeSyntaxError("[ mulop addop relop do then ] , ) ; end else", tok.lexeme);
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
