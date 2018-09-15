#ifndef MACHINES
#define MACHINES
#include "../tokens.h"
/*this way we can compile individual machines c files but it isn't inefficiently
 compiling the whole program*/
struct machOut
{
  int b;
  int error;
  char *lexeme;
  int tokenType;
  int attribute;
};
int whitespace(int b, char *buff);
struct machOut idres(int b, int end, char *buff, FILE *listFile);
struct machOut catchall(int b, int end, char *buff, FILE *listFile);
struct machOut relop(int b, int end, char *buff, FILE *listFile);

#endif
