#include <stdio.h>
#include <string.h>
#include <ctype.h>

#include "tokens.h"
#include "./Machines/machines.h"


//malloc dynamically allocate --read more
//realloc reallocate variable size
//calloc and pragma
int machines(char *buff, FILE *listFile){
  int b = 0;//back
  int f = 0;//front
  int end = strlen(buff);
  struct machOut out;
  while(b<end){
    b = whitespace(b, end, buff);
    out = idres(b, end, buff, listFile);

  }
  return 0;
}

//Loads the next line into buffer... eof will return NULL
char* loadBuffer(char *buff, FILE *fp){
  return fgets(buff, 72, (FILE*)fp);
}

//
int printBuffer(char *buff, FILE *listFile, int lineNum){
  return fprintf(listFile, "%d.\t%s", lineNum, buff);
}

int main()
{
  char *eof;
  FILE *rfp;
  FILE *listFile;
  char buff[72];

  rfp = fopen("./PascalExample.pas", "r");
  listFile = fopen("./ListingFile.txt", "w+");

  eof = loadBuffer(buff,rfp);
  int lineNum = 1;
  while(eof!=NULL){
    printBuffer(buff,listFile,lineNum);
    machines(buff, listFile);
    eof = loadBuffer(buff,rfp);
    lineNum++;
  }

  fclose(rfp);
  return 0;
}
