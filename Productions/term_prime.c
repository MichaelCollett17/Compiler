#include <stdio.h>
#include <stdbool.h>
#include "../tokens.h"
#include "../LinkedLists/TokenLLV2.h"
#include "./productions.h"
#include "../reservedWords.h"
#include "../Parser.h"

int term_prime(int i){
  struct resWord do_ = getTokAndAtt("do");
  struct resWord then = getTokAndAtt("then");
  struct resWord end = getTokAndAtt("end");
  struct resWord else_ = getTokAndAtt("else");
  struct resWord div_ = getTokAndAtt("div");
  struct resWord mod_ = getTokAndAtt("mod");
  struct resWord and_ = getTokAndAtt("and");
  if(tok.tokenType==MULOP){
    int op = 0;
    if(tok.attribute==MULT){
      match(MULOP,MULT,"*");
      op = MULT;
    }
    else if(tok.attribute == div_.attributeResWord){
      match(div_.tokenResWord,div_.attributeResWord,div_.lexResWord);
      op = div_.attributeResWord;
    }
    else if(tok.attribute == mod_.attributeResWord){
      match(mod_.tokenResWord,mod_.attributeResWord,mod_.lexResWord);
      op = mod_.attributeResWord;
    }
    else if(tok.attribute == and_.attributeResWord){
      match(and_.tokenResWord,and_.attributeResWord,and_.lexResWord);
      op = and_.attributeResWord;
    }
    else{
      match(MULOP,DIV,"/");
      op = DIV;
    }
    int f_type = factor();
    int type_in;
    if((f_type == ERR) || (i == ERR)){
      type_in = ERR;
    }
    else{
      if(op == and_.attributeResWord){
        if((f_type == BOOL) && (i == BOOL)){
          type_in = BOOL;
        }
        else{
          writeSemanticError("The AND operator must be between two Booleans");
          type_in = ERR;
        }
      }
      else if(op == mod_.attributeResWord){
        if((f_type == INTEGER) && (i == INTEGER)){
          type_in = INTEGER;
        }
        else{
          writeSemanticError("Modulus operator only works on integers");
          type_in = ERR;
        }
      }
      else if(f_type == i){
        return f_type;
      }
      else{
        writeSemanticError("Terms between operator must be the same type");
        type_in = ERR;
      }
    }
    int type_ = term_prime(type_in);
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
    ((tok.tokenType == RELOP)) ||
    (tok.tokenType == ADDOP)){
    return i;
  }
  else{
    writeSyntaxError("mulop addop relop do then ] , ) ; end else", tok.lexeme);
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
      (tok.tokenType != ADDOP)){
        getToken();
    }
    return ERR;
  }
}
