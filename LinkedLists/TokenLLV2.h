#ifndef TOKENLINKEDLISTV2
#define TOKENLINKEDLISTV2

struct tokenNode {
  int lineNo;
  char *lexeme;
  int tokenType;
  int attribute;
  struct tokenNode *next;
};

void insertHead(int lineNo, char *lexeme, int tokenType, int attribute);
void insertToken(int lineNo, char *lexeme, int tokenType, int attribute);
void printList(FILE *tokFile);
struct tokenNode getNextToken();

#endif
