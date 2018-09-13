#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "SymbolTable.h"

struct symbol *symbolHead = NULL;
struct symbol nextSymbolNull = {"",-1};
int currentSymbolKey = 0;

void addSymbol(char *lexeme){
 struct symbol *link = (struct symbol*) malloc(sizeof(struct symbol));
 link->lexeme = lexeme;
 link->key = currentSymbolKey;
 currentSymbolKey++;
 link->nextSymbol = symbolHead;
 symbolHead = link;
}

struct symbol getSymbol(int key){
  struct symbol *ptr = symbolHead;
  while(ptr){
    if(ptr->key == key){
      return *ptr;
    }
    if(ptr ->nextSymbol){
      ptr = ptr->nextSymbol;
    }
    else{
      return nextSymbolNull;
    }
  }
  return *ptr;
}

void printSymbols(){
  struct symbol *ptr = symbolHead;
  while(ptr){
    printf("%s\t%d\n", ptr->lexeme,ptr->key);
    ptr = ptr -> nextSymbol;
  }
}
