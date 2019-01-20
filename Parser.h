#ifndef PARSER
#define PARSER
struct tw{
  int t;
  int w;
};


void writeSyntaxError(char *expecting, char *received);
void writeSemanticError(char *error);
void getToken();
#endif
