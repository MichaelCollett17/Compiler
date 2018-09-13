#ifndef SYMBOLTABLE
#define SYMBOLTABLE
struct symbol{
  char *lexeme;
  int key;
  struct symbol *nextSymbol;
};

void addSymbol(char *lexeme);
struct symbol getSymbol(int key);
void printSymbols();

#endif
