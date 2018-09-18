#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "SymbolTable.h"

struct symbol *symbolHead = NULL;
struct symbol nextSymbolNull = {"",-1};
int currentSymbolKey = 0;

//when you instantiate something it will retain the values in that memory location
//when creating a variable you either assign it a value immediately or set it to NULL
//same with structs
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

/*
 * ptr is being dereferenced when I return it so it is returning
 * a copy of the symbol
 *
 */
struct symbol* checkSymbolExists(char *lexeme){
    struct symbol *ptr = symbolHead;
    while(ptr){
        if(strcmp(ptr->lexeme, lexeme)==0){
            return ptr;
        }
        if(ptr -> nextSymbol){
            ptr = ptr->nextSymbol;
        }
        else{
            return NULL;
        }
    }
    return NULL;
}

void printSymbols(){
  struct symbol *ptr = symbolHead;
  while(ptr){
    printf("%s\t%d\n", ptr->lexeme,ptr->key);
    ptr = ptr -> nextSymbol;
  }
}
