#include <stdio.h>
#include <stdbool.h>
#include "../tokens.h"
#include "../LinkedLists/TokenLLV2.h"
#include "./productions.h"
#include "../reservedWords.h"
#include "../Parser.h"
#include "../GNBNTree/GNBNNode.h"

void declarations(){
  struct resWord var = getTokAndAtt("var");
  if(tok.tokenType ==var.tokenResWord){
    match(var.tokenResWord, var.attributeResWord, "var");
    char *id_lex = match(ID, 0, "ID");
    match(TYPE, 0, ":");
    struct tw type_width = type();
    //semstart
    int type_ = type_width.t;
    //printAddress(id_lex,offset);
    checkAddBlueNode(id_lex,type_,offset,1);
    offset = offset + type_width.w;
    //semend
    match(PUNCTUATION,SEMICOLON, ";");
    declarations_prime();
  }
  else{
    writeSyntaxError(var.lexResWord, tok.lexeme);
    struct resWord procedure = getTokAndAtt("procedure");
    struct resWord begin = getTokAndAtt("begin");
    while(tok.tokenType != EOFTOKEN && (!((tok.tokenType == begin.tokenResWord)
      &&(tok.attribute == begin.attributeResWord))) && (!(tok.tokenType == procedure.tokenResWord))){
      getToken();
    }
  }
}
