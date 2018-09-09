#ifndef LINKEDLIST
#define LINKEDLIST

struct node {
  int lineNo;
  char *lexeme;
  int tokenType;
  int attribute;
  struct node *next;
};

void insert(int lineNo, char *lexeme, int tokenType, int attribute);
void printList();

#endif
