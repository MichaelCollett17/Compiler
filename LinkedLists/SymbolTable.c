#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "SymbolTable.h"

struct symbol *symbolHead = NULL;
struct symbol nextSymbolNull = {"",-1};
int currentSymbolKey = 0;

int addSymbol(char *lexeme){
 struct symbol *link = (struct symbol*) malloc(sizeof(struct symbol));
 link->lexeme = lexeme;
 link->key = currentSymbolKey;
 currentSymbolKey++;
 link->nextSymbol = symbolHead;
 symbolHead = link;
 return link->key;
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

int checkSymbolExists(char *lexeme){
    struct symbol *ptr = symbolHead;
    while(ptr){
        if(strcmp(ptr->lexeme, lexeme)==0){
            return ptr->key;
        }
        if(ptr -> nextSymbol){
            ptr = ptr->nextSymbol;
        }
        else{
            return -1;
        }
    }
    return -1;
}

void printSymbols(){
  struct symbol *ptr = symbolHead;
  while(ptr){
    printf("%s\t%d\n", ptr->lexeme,ptr->key);
    ptr = ptr -> nextSymbol;
  }
}
