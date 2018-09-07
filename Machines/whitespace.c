#include <ctype.h>
int whitespace(int b, int end, char *buff){
  while(isspace(buff[b])){
    b++;
  }
  return b;
}
