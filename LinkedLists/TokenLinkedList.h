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
void reverseTokens(struct node** AnotherHead);
struct node getNextToken();
#endif
