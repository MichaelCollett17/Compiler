#include <ctype.h>
int whitespace(int b, char *buff){
  while(isspace(buff[b])){
    b++;
  }
  return b;
}
