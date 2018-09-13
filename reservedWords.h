#ifndef RESWORDS
#define RESWORDS

struct resWord{
  char *lexResWord;
  int tokenResWord;
  int attributeResWord;
  struct resWord *nextResWord;
};

void loadReservedWords();
struct resWord getTokAndAtt(char *lexeme);

#endif
