#ifndef PRODUCTIONS
#define PRODUCTIONS
struct tokenNode tok;
void program();
void idlst();
void match(int tokenToMatch, int attributeToMatch, char *lexeme);
void idlst_prime();
void program_prime();

#endif
