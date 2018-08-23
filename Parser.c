#include <stdio.h>

char* loadBuffer(char *buff, FILE *fp){
  return fgets(buff, 72, (FILE*)fp);
}

int printBuffer(char *buff, FILE *wfp){
  printf("%s", buff);
  fputs(buff, wfp);
  return 0;
}

int main()
{
  char* eof;
  FILE *rfp;
  FILE *wfp;
  char buff[72];
  rfp = fopen("./PascalExample.pas", "r");
  wfp = fopen("./ListingFile.pas", "w+");

  eof = loadBuffer(buff,rfp);
  while(eof!=NULL){
    printBuffer(buff,wfp);
    eof = loadBuffer(buff,rfp);
  }

  fclose(rfp);
  return 0;
}
