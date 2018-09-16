#include <stdlib.h>
#include <stdio.h>
#include "TokenLinkedList.h"

struct node *head = NULL;
struct node *current = NULL;

void insert(int lineNo, char *lexeme, int tokenType, int attribute) {
   //create a link
   struct node *link = (struct node*) malloc(sizeof(struct node));

   //link->key = key;
   link->lineNo = lineNo;
   link->lexeme = lexeme;
   link->tokenType = tokenType;
   link->attribute = attribute;

   //point it to old first node
   link->next = head;

   //point first to new first node
   head = link;
}

void printList() {
  struct node *ptr = head;
  while(ptr != NULL){
    printf("%d\t%d\t%d\n", ptr->lineNo,ptr->tokenType,ptr->attribute);
    ptr = ptr -> next;
  }
}
