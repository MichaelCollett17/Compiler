#include <stdio.h>
#include <stdbool.h>
#include "../tokens.h"
//#include "../LinkedLists/TokenLinkedList.h"
#include "../LinkedLists/TokenLLV2.h"
#include "./productions.h"
#include "../reservedWords.h"
#include "../Parser.h"
#include "../GNBNTree/GNBNNode.h"

void program(){
  struct resWord program = getTokAndAtt("program");
  if(tok.tokenType == program.tokenResWord) {
    match(program.tokenResWord, program.attributeResWord, program.lexResWord);
    char *idlex = match(ID, 0, "ID");
    match(GROUPING, LPAR, "(");
    //semantic start
    offset = 0;//may need to be int offset!
    checkAddGreenNode(idlex, PGNAME);
    //semantic end
    idlst();
    match(GROUPING, RPAR, ")");
    match(PUNCTUATION,SEMICOLON, ";");
    program_prime();
  }
  else{
    //synch
    writeSyntaxError(program.lexResWord, tok.lexeme);
    while(tok.tokenType != EOFTOKEN){
      getToken();
    }
  }
}
