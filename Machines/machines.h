#ifndef MACHINES
#define MACHINES
#include "../tokens.h"
/*this way we can compile individual machines c files but it isn't inefficiently
 compiling the whole program*/
int whitespace(int b, int end, char *buff);
//Struct where to put
struct machOut
{
  int b;
  int error;
  char *lex[20];
};

struct machOut idres(int b, int end, char *buff, FILE *listFile);
#endif
