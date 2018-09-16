#include <stdlib.h>
#include <stdio.h>
#include "TokenLinkedList.h"
#include "../tokens.h"

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

void reverseTokens(struct node** AnotherHead){
  struct node* prev = NULL;
  struct node* current = *AnotherHead;
  struct node* next;

  while(current != NULL){
    next  = current->next;
      current->next = prev;
      prev = current;
      current = next;
  }
    *AnotherHead = prev;
}

void printList(FILE *tokFile) {
  reverseTokens(&head);
  struct node *ptr = head;
  fprintf(tokFile, "%-12s\t%-20s\t%-12s\t%s\n", "Line No.", "Lexeme", "Token Type", "Attribute");
  while(ptr != NULL){
    fprintf(tokFile, "%-12d\t%-20s\t%-12d\t%d\n", ptr->lineNo, ptr->lexeme, ptr->tokenType,ptr->attribute);
    ptr = ptr -> next;
  }
  //print EOF
  fprintf(tokFile, "%-12d\t%-20s\t%-12d\t%d\n", EOF, "EOF", EOFTOKEN, 0);
}
