#ifndef PRODUCTIONS
#define PRODUCTIONS
struct tokenNode tok;
void program();
void idlst();
void match(int tokenToMatch, int attributeToMatch, char *lexeme);
void idlst_prime();
void program_prime();
void program_prime_prime();
void subdeclarations();
void subdeclarations_prime();
void declarations();
void declarations_prime();

#endif
