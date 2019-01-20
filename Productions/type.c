#include <stdio.h>
#include <stdbool.h>
#include "../tokens.h"
#include "../LinkedLists/TokenLLV2.h"
#include "./productions.h"
#include "../reservedWords.h"
#include "../Parser.h"

struct tw type(){
  struct resWord array = getTokAndAtt("array");
  struct resWord real = getTokAndAtt("real");
  struct resWord integer = getTokAndAtt("integer");
  struct resWord of = getTokAndAtt("of");
  if(tok.tokenType == array.tokenResWord){
    match(array.tokenResWord, array.attributeResWord, "array");
    match(GROUPING, LBRACK, "[");
    int num1 = matchNum();
    match(ARRAY, 0, "..");
    int num2 = matchNum();
    match(GROUPING, RBRACK, "]");
    match(of.tokenResWord, of.attributeResWord, of.lexResWord);
    struct tw tw_in = standard_type();
    int type_;
    if(tw_in.t == INTEGER){
      type_ = AINT;
    }
    else if(tw_in.t == REAL){
      type_ = AREAL;
    }
    else{
      type_ = ERR;
    }

    int width;
    if((num1 < 0) || (num2<0)){
      type_ = ERR;
      width = 0;
      writeSemanticError("numbers in array must be integers");
    }
    else if(num2 < num1){
      type_ = ERR;
      width = 0;
      writeSemanticError("second number in array must be larger than first");
    }
    else{
      width = tw_in.w * ((num2-num1)+1);
    }

    struct tw tw_out = {type_, width};
    return tw_out;
  }
  else if((tok.tokenType == real.tokenResWord) ||
          (tok.tokenType == integer.tokenResWord)){
    struct tw tw_in = standard_type();
    return tw_in;
  }
  else{
    //synch
    writeSyntaxError("array, real or integer", tok.lexeme);
    while(tok.tokenType != EOFTOKEN && (!((tok.tokenType == GROUPING) && (tok.attribute == RPAR))) && (!((tok.tokenType == PUNCTUATION) && (tok.attribute == SEMICOLON)))){
      getToken();
    }
    struct tw tw_= {ERR,0};
    return tw_;
  }
}
