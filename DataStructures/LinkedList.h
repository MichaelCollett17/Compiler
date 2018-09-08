#ifndef LINKEDLIST
#define LINKEDLIST

struct node *head = NULL;
struct node *current = NULL;

struct node {
  int lineNo;
  char *lexeme;
  int tokenType;
  char *tokenString;
  int attribute;
  struct node *next;
};
void insert(int lineNo, char *lexeme, int tokenType, char *tokenString, int attribute);

#endif
