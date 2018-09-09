#ifndef MACHINES
#define MACHINES
#include "../tokens.h"
/*this way we can compile individual machines c files but it isn't inefficiently
 compiling the whole program*/
int whitespace(int b, char *buff);

struct machOut
{
  int b;
  int error;
  char *lexeme;//instead I should pass a pointer to the first address and iterate to end
  int tokenType;
  int attribute;
};

struct machOut idres(int b, int end, char *buff, FILE *listFile);
#endif
