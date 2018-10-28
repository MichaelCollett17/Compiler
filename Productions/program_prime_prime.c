#include <stdio.h>
#include "../tokens.h"
//#include "../LinkedLists/TokenLinkedList.h"
#include "../LinkedLists/TokenLLV2.h"
#include "./productions.h"
#include "../reservedWords.h"
#include "../Parser.h"

void program_prime_prime(){
  struct resWord procedure = getTokAndAtt("procedure");
  struct resWord begin = getTokAndAtt("begin");
  if(tok.tokenType == procedure.tokenResWord){
    subdeclarations();
    //compound_statement();
    match(PUNCTUATION, PERIOD, ".");
  }
  else if((tok.tokenType == begin.tokenResWord)&&(tok.attribute == begin.attributeResWord)){
    //compound_statement();
    match(PUNCTUATION, PERIOD, ".");
  }
  else{
    writeSyntaxError("procedure or begin", tok.lexeme);
    while(tok.tokenType != EOFTOKEN){
      getToken();
    }
  }
}
