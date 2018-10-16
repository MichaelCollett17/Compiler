#include <stdio.h>
#include <stdbool.h>
#include "../tokens.h"
#include "../LinkedLists/TokenLinkedList.h"
#include "./productions.h"
#include "../reservedWords.h"
#include "../Parser.h"

void program(){
  struct resWord program = getTokAndAtt("program");
  if(tok.tokenType == program.tokenResWord) {
    match(program.tokenResWord, program.attributeResWord, program.lexResWord);
    match(ID, 0, "ID");
    match(GROUPING, LPAR, "(");
    idlst();
    match(GROUPING, RPAR, ")");
    match(PUNCTUATION,SEMICOLON, ";");
    //declarations();
    //subdeclarations();
    //compound_statement();
    match(PUNCTUATION, PERIOD, ".");
  }
  else{
    //synch
    writeSyntaxError(program.lexResWord, tok.lexeme);
    while(tok.tokenType != EOFTOKEN){
      tok = getNextToken();
    }
  }
}
