#include <stdio.h>
#include <stdbool.h>
#include "../tokens.h"
#include "../LinkedLists/TokenLLV2.h"
#include "./productions.h"
#include "../reservedWords.h"
#include "../Parser.h"
#include "../GNBNTree/GNBNNode.h"

void statement(){
  struct resWord call = getTokAndAtt("call");
  struct resWord begin = getTokAndAtt("begin");
  struct resWord while_ = getTokAndAtt("while");
  struct resWord if_ = getTokAndAtt("if");
  //id
  if(tok.tokenType == ID){
    int var_type = variable();
    match(ASSIGNOP, 0, ":=");
    int exp_type = expression();
    if(!((var_type == ERR) || (exp_type == ERR) || (var_type == exp_type))){
      writeSemanticError("incorrect types, variable and expression must be of the same type");
      printUpLeftChain();
      printf("%d, and %d\n", var_type,exp_type);
    }
  }
  //call
  else if(tok.tokenType==call.tokenResWord){
    procedure_statement();
  }
  //begin
  else if((tok.tokenType == begin.tokenResWord) && (tok.attribute == begin.attributeResWord)){
    compound_statement();
  }
  //while
  else if((tok.tokenType == while_.tokenResWord) && (tok.attribute == while_.attributeResWord)){
    struct resWord do_ = getTokAndAtt("do");
    match(while_.tokenResWord, while_.attributeResWord,while_.lexResWord);
    int exp_type = expression();
    if(exp_type != ERR && exp_type !=BOOL){
      writeSemanticError("Expression type must be a boolean expression");
    }
    match(do_.tokenResWord, do_.attributeResWord, do_.lexResWord);
    statement();
  }
  //if
  else if((tok.tokenType == if_.tokenResWord) && (tok.attribute == if_.attributeResWord)){
    struct resWord then = getTokAndAtt("then");
    match(if_.tokenResWord, if_.attributeResWord, if_.lexResWord);
    int exp_type = expression();
    if(exp_type != ERR && exp_type !=BOOL){
      writeSemanticError("Expression type must be a boolean expression");
    }
    match(then.tokenResWord,then.attributeResWord,then.lexResWord);
    statement();
    statement_prime();
  }
  else{
    //; end else
    struct resWord end = getTokAndAtt("end");
    struct resWord else_ = getTokAndAtt("else");
    writeSyntaxError("ID, call, begin, while, if",tok.lexeme);
    while((tok.tokenType != EOFTOKEN) &&
    (!((tok.tokenType == end.tokenResWord) && (tok.attribute == end.attributeResWord)))
    && (!((tok.tokenType == else_.tokenResWord) && (tok.attribute == else_.attributeResWord)))
    && (!((tok.tokenType == PUNCTUATION) && (tok.attribute == SEMICOLON)))){
      getToken();
    }
  }
}
