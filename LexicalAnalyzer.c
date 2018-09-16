#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

#include "tokens.h"
#include "./Machines/machines.h"
#include "./LinkedLists/TokenLinkedList.h"
#include "reservedWords.h"

int stringLength(char *s){
  int n;
  for(n=0; *s != '\0'; s++)
    n++;
  return n;
}

int processMachineOutput(struct machOut out, int lineNum, int b){
    b = out.b;
    if(out.error>99){
      insert(lineNum, out.lexeme, LEXERR, out.error);
      printf("%d. %s\t%d\t%d\n", lineNum, out.lexeme, LEXERR, out.error);
    }
    else{
      insert(lineNum, out.lexeme, out.tokenType, out.attribute);
      printf("%d. %s\t%d\t%d\n", lineNum, out.lexeme, out.tokenType, out.attribute);
    }
    return b;
}

//malloc dynamically allocate --read more
//realloc reallocate variable size
//calloc and pragma
int machines(char *buff, FILE *listFile, int lineNum){
  int b = 0;//back
  int f = 0;//front
  int end = strlen(buff);
  struct machOut out;
  while(b<end){
    //Whitespace
    b = whitespace(b, buff);
    if(b==end){
        continue;
    }
    //idres
    out = idres(b, end, buff, listFile);
    if(out.b!=BLOCK){
        b = processMachineOutput(out, lineNum, b);
        continue;
    }
    //catchall
    out = catchall(b, end, buff, listFile);
    if(out.b!=BLOCK){
        b = processMachineOutput(out, lineNum, b);
        continue;
    }
    //nums
    out = number(b, end, buff, listFile);
    if(out.b!=BLOCK){
        b = processMachineOutput(out, lineNum, b);
        continue;
    }
    //relops
    out = relop(b, end, buff, listFile);
    if(out.b!=BLOCK){
        b = processMachineOutput(out, lineNum, b);
        continue;
    }
    //Unrecognized symbol
    char *lexeme = malloc(2*sizeof(char));
    lexeme[0] = buff[b];
    lexeme[1] = '\0';
    struct machOut unrecog = {b+1, UNRECOGSYMB,lexeme};
    b = processMachineOutput(unrecog, lineNum, b);
    fprintf(listFile, "%-12s%-30s%s\n", "LEXERR:", "UnrecognizedSymbol", lexeme);
  }
  return 0;
}

//Loads the next line into buffer... eof will return NULL
char* loadBuffer(char *buff, FILE *fp){
  return fgets(buff, 72, (FILE*)fp);
}

//Prints next line into Listing file
int printBuffer(char *buff, FILE *listFile, int lineNum){
  return fprintf(listFile, "%d.\t%s", lineNum, buff);
}

int main()
{
  char *eof;
  FILE *rfp;
  FILE *listFile;
  char buff[72];

  //rfp = fopen("./PascalExample.pas", "r");
  rfp = fopen("./InputFiles/ErrorFile.pas", "r");
  listFile = fopen("./OutputFiles/ErrorFile.txt", "w+");
  loadReservedWords();

  eof = loadBuffer(buff,rfp);
  int lineNum = 1;
  while(eof!=NULL){
    printBuffer(buff,listFile,lineNum);
    machines(buff, listFile, lineNum);
    eof = loadBuffer(buff,rfp);
    lineNum++;
    //break;
  }

  fclose(rfp);
  return 0;
}
