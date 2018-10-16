#include <stdio.h>
#include <stdbool.h>
#include "../tokens.h"
#include "../LinkedLists/TokenLinkedList.h"
#include "./productions.h"
#include "../reservedWords.h"
void program(){
  // Only one production for program so no need for switch statement
  struct resWord program = getTokAndAtt("program");
  match(program.tokenResWord, program.attributeResWord, program.lexResWord);
  match(ID, 0, "ID");
  match(GROUPING, LPAR, "(");
  //idlst()
  match(GROUPING, RPAR, ")");
  match(PUNCTUATION,SEMICOLON, ";");
  //declarations();
  //subdeclarations();
  //compound_statement();
  match(PUNCTUATION, PERIOD, ".");
  return;
}
