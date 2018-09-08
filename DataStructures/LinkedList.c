#include <stdlib.h>
#include <stdio.h>
#include "LinkedList.h"
void insert(int lineNo, char *lexeme, int tokenType, char *tokenString, int attribute) {
   //create a link
   struct node *link = (struct node*) malloc(sizeof(struct node));

   //link->key = key;
   link->lineNo = lineNo;
   link->lexeme = lexeme;
   link->tokenType = tokenType;
   link->tokenString = tokenString;
   link->attribute = attribute;

   //point it to old first node
   link->next = head;

   //point first to new first node
   head = link;
}

void printList() {
  struct node *ptr = head;
  while(ptr != NULL){
    printf("%d\t%d\t%d", ptr->lineNo,ptr->tokenType,ptr->attribute);
  }
}
