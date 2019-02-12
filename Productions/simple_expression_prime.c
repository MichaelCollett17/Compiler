#include <stdio.h>
#include <stdbool.h>
#include "../tokens.h"
#include "../LinkedLists/TokenLLV2.h"
#include "./productions.h"
#include "../reservedWords.h"
#include "../Parser.h"

int simple_expression_prime(int i){
  struct resWord do_ = getTokAndAtt("do");
  struct resWord then = getTokAndAtt("then");
  struct resWord end = getTokAndAtt("end");
  struct resWord else_ = getTokAndAtt("else");
  struct resWord or_ = getTokAndAtt("or");
  if(tok.tokenType == ADDOP){
    int op = 0;
    if(tok.attribute == ADD){
      match(ADDOP, ADD, "+");
      op = ADD;
    }
    else if(tok.attribute == or_.attributeResWord){
      match(or_.tokenResWord,or_.attributeResWord, or_.lexResWord);
      op = or_.attributeResWord;
    }
    else{
      match(ADDOP, SUB, "-");
      op = SUB;
    }
    int term_type = term();
    int se_type = 0;
    if((term_type == ERR) || (i == ERR)){
      se_type = ERR;
    }
    else{
      if(op == or_.attributeResWord){
        if((term_type == BOOL) && (i == BOOL)){
          se_type = BOOL;
        }
        else{
          writeSemanticError("or statement must be surrounded by two bools");
          se_type = ERR;
        }
      }
      else{//op is either sub or add
        if((term_type == INTEGER) && (i == INTEGER)){
          se_type = INTEGER;
        }
        else if((term_type == REAL) && (i == REAL)){
          se_type = REAL;
        }
        else{
          writeSemanticError("addition and subtraction types must match and be either int or real");
          se_type = ERR;
        }
      }
    }
    int type_ = simple_expression_prime(se_type);
    return type_;
  }
  else if((((tok.tokenType == GROUPING) && (tok.attribute == RBRACK))) ||
    (((tok.tokenType == do_.tokenResWord) && (tok.attribute == do_.attributeResWord))) ||
    (((tok.tokenType == then.tokenResWord) && (tok.attribute == then.attributeResWord))) ||
    (((tok.tokenType == PUNCTUATION) && (tok.attribute == COMMA))) ||
    (((tok.tokenType == GROUPING) && (tok.attribute == RPAR))) ||
    (((tok.tokenType == PUNCTUATION) && (tok.attribute == SEMICOLON))) ||
    (((tok.tokenType == end.tokenResWord) && (tok.attribute == end.attributeResWord))) ||
    (((tok.tokenType == else_.tokenResWord) && (tok.attribute == else_.attributeResWord))) ||
    ((tok.tokenType == RELOP))){
    return i;
  }
  else{
    writeSyntaxError("addop relop do then ] , ) ; end else", tok.lexeme);
    while((tok.tokenType != EOFTOKEN) &&
      (!((tok.tokenType == GROUPING) && (tok.attribute == RBRACK))) &&
      (!((tok.tokenType == do_.tokenResWord) && (tok.attribute == do_.attributeResWord))) &&
      (!((tok.tokenType == then.tokenResWord) && (tok.attribute == then.attributeResWord))) &&
      (!((tok.tokenType == PUNCTUATION) && (tok.attribute == COMMA))) &&
      (!((tok.tokenType == GROUPING) && (tok.attribute == RPAR))) &&
      (!((tok.tokenType == PUNCTUATION) && (tok.attribute == SEMICOLON))) &&
      (!((tok.tokenType == end.tokenResWord) && (tok.attribute == end.attributeResWord))) &&
      (!((tok.tokenType == else_.tokenResWord) && (tok.attribute == else_.attributeResWord))) &&
      ((tok.tokenType != RELOP))){
        getToken();
    }
    return ERR;
  }
}
