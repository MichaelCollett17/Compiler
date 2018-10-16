#ifndef PRODUCTIONS
#define PRODUCTIONS
struct node tok;
void program();
void idlst();
void match(int tokenToMatch, int attributeToMatch, char *lexeme);
#endif
