#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "TokenLLV2.h"
#include "../tokens.h"

struct tokenNode *tokenHead= NULL;
struct tokenNode *tokenPrev = NULL;
struct tokenNode *tokTmp = NULL;

void insertHead(int lineNo, char *lexeme, int tokenType, int attribute) {
  printf("%s\n", "insertHead");
  tokenHead->lineNo = lineNo;
  tokenHead->lexeme = lexeme;
  tokenHead->tokenType = tokenType;
  tokenHead->attribute = attribute;
  tokenHead->next=NULL;
  tokenPrev = tokenHead;
}

void insertToken(int lineNo, char *lexeme, int tokenType, int attribute) {
  printf("%s\n", tokenHead==NULL ? "true" : "false");
  if(tokenHead==NULL){
    tokenHead = (struct tokenNode*) malloc(sizeof(struct tokenNode));
    tokenHead->lineNo = lineNo;
    tokenHead->lexeme = lexeme;
    tokenHead->tokenType = tokenType;
    tokenHead->attribute = attribute;
    tokenHead->next=NULL;
    tokenPrev = tokenHead;
    printf("Token prev: %s\n", tokenPrev->lexeme);
    return;
  }
  else{
    struct tokenNode *link = (struct tokenNode*) malloc(sizeof(struct tokenNode));
    printf("Token prev else: %s\n", tokenPrev->lexeme);
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
  insertToken(EOF, "EOF", EOFTOKEN, 0);
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
  if(tokTmp == NULL){
    tokTmp = tokenHead;
  }
  struct tokenNode *temp = tokTmp;
  struct tokenNode *nextCheck = tokTmp -> next;
  if(nextCheck != NULL){
    tokTmp = tokTmp -> next;
    return *temp;
  }
  else{
    return *nextCheck;
  }
}
