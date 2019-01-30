#include <stdio.h>
#include <stdbool.h>
#include "../tokens.h"
#include "../LinkedLists/TokenLLV2.h"
#include "./productions.h"
#include "../reservedWords.h"
#include "../Parser.h"
#include "../GNBNTree/GNBNNode.h"

void procedure_statement_prime(){
  struct resWord else_ = getTokAndAtt("else");
  struct resWord end = getTokAndAtt("end");
  if((tok.tokenType == GROUPING)&&(tok.attribute == LPAR)){
    match(GROUPING, LPAR, "(");
    expression_list();
    match(GROUPING, RPAR, ")");
  }
  else if(((tok.tokenType == end.tokenResWord) && (tok.attribute == end.attributeResWord))
  || ((tok.tokenType == else_.tokenResWord) && (tok.attribute == else_.attributeResWord))
  || ((tok.tokenType == PUNCTUATION) && (tok.attribute == SEMICOLON))){
    checkNoParams();
    return;
  }
  else{
    //; end else
    writeSyntaxError("(, ;, end, else",tok.lexeme);
    while((tok.tokenType != EOFTOKEN) &&
    (!((tok.tokenType == end.tokenResWord) && (tok.attribute == end.attributeResWord)))
    && (!((tok.tokenType == else_.tokenResWord) && (tok.attribute == else_.attributeResWord)))
    && (!((tok.tokenType == PUNCTUATION) && (tok.attribute == SEMICOLON)))){
      getToken();
    }
  }
}
