#include <stdio.h>
#include <stdbool.h>
#include "../tokens.h"
#include "../LinkedLists/TokenLLV2.h"
#include "./productions.h"
#include "../reservedWords.h"
#include "../Parser.h"

int expression_prime(int i){
  struct resWord do_ = getTokAndAtt("do");
  struct resWord then = getTokAndAtt("then");
  struct resWord end = getTokAndAtt("end");
  struct resWord else_ = getTokAndAtt("else");
  if(tok.tokenType == RELOP){
    if(tok.attribute == LTEQ){
      match(RELOP, LTEQ,"<=");
    }
    else if(tok.attribute == NEQ){
      match(RELOP, NEQ, "<>");
    }
    else if(tok.attribute == LT){
      match(RELOP, LT, "<");
    }
    else if(tok.attribute == EQ){
      match(RELOP, EQ, "=");
    }
    else if(tok.attribute == GTEQ){
      match(RELOP, GTEQ, ">=");
    }
    else{
      match(RELOP, GT, ">");
    }
    int se_type = simple_expression();
    if((se_type == ERR) || (i == ERR)){
      return ERR;
    }
    else if(((se_type == INTEGER) &&(i==INTEGER)) || ((se_type == REAL)&&(se_type == REAL))){
      return BOOL;
    }
    else{
      writeSemanticError("relational operations must be performed on the same type ie. int relop int or real relop real");
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
  (((tok.tokenType == else_.tokenResWord) && (tok.attribute == else_.attributeResWord)))){
    return i;
  }
  else{
    writeSyntaxError("RELOP ] do then , ) ; end else", tok.lexeme);
    while((tok.tokenType != EOFTOKEN) &&
    (!((tok.tokenType == GROUPING) && (tok.attribute == RBRACK))) &&
    (!((tok.tokenType == do_.tokenResWord) && (tok.attribute == do_.attributeResWord))) &&
    (!((tok.tokenType == then.tokenResWord) && (tok.attribute == then.attributeResWord))) &&
    (!((tok.tokenType == PUNCTUATION) && (tok.attribute == COMMA))) &&
    (!((tok.tokenType == GROUPING) && (tok.attribute == RPAR))) &&
    (!((tok.tokenType == PUNCTUATION) && (tok.attribute == SEMICOLON))) &&
    (!((tok.tokenType == end.tokenResWord) && (tok.attribute == end.attributeResWord))) &&
    (!((tok.tokenType == else_.tokenResWord) && (tok.attribute == else_.attributeResWord)))){
      getToken();
    }
    return ERR;
  }
}
