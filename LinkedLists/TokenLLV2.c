#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "TokenLLV2.h"
#include "../tokens.h"

struct tokenNode *tokenHead= NULL;
struct tokenNode *tokenPrev = NULL;
struct tokenNode *tokCurr = NULL;
struct tokenNode *nullNode = NULL;

void insertToken(int lineNo, char *lexeme, int tokenType, int attribute) {
  if(tokenHead==NULL){
    tokenHead = (struct tokenNode*) malloc(sizeof(struct tokenNode));
    nullNode = (struct tokenNode*) malloc(sizeof(struct tokenNode));
    nullNode ->lineNo = -10;
    tokenHead->lineNo = lineNo;
    tokenHead->lexeme = lexeme;
    tokenHead->tokenType = tokenType;
    tokenHead->attribute = attribute;
    tokenHead->next=NULL;
    tokenPrev = tokenHead;
    return;
  }
  else{
    struct tokenNode *link = (struct tokenNode*) malloc(sizeof(struct tokenNode));
    //link->key = key;
    link->lineNo = lineNo;
    link->lexeme = lexeme;
    link->tokenType = tokenType;
    link->attribute = attribute;
    link->next=NULL;

    tokenPrev->next = link;
    tokenPrev = link;
  }
}

void printList(FILE *tokFile) {
  //insertToken(EOF, "EOF", EOFTOKEN, 0);
  struct tokenNode *ptr = tokenHead;
  fprintf(tokFile, "%-12s\t%-20s\t%-12s\t%s\n", "Line No.", "Lexeme", "Token Type", "Attribute");
  while(ptr != NULL){
    if(ptr->tokenType == 1){
      fprintf(tokFile, "%-12d\t%-20s\t%-12d\t%p\n", ptr->lineNo, ptr->lexeme, ptr->tokenType,(void *)(ptr->lexeme));
    }
    else{
      fprintf(tokFile, "%-12d\t%-20s\t%-12d\t%d\n", ptr->lineNo, ptr->lexeme, ptr->tokenType,ptr->attribute);
    }
    ptr = ptr -> next;
  }
}

struct tokenNode getNextToken(){
  if(tokCurr == NULL){
    tokCurr = tokenHead;
    return *tokCurr;
  }
  //struct tokenNode *temp = tokCurr;
  printf("Current Tok:%s\n", tokCurr -> lexeme);
  if(tokCurr -> next != NULL){
    tokCurr = tokCurr -> next;
    return *tokCurr;
  }
  else{
    return *nullNode;
  }
}
