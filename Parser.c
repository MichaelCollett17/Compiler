#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

#include "tokens.h"
#include "./Machines/machines.h"
#include "./LinkedLists/TokenLinkedList.h"
#include "reservedWords.h"
#include "LexicalAnalyzer.h"

int main()
{
  char *eof;
  FILE *rfp;
  FILE *listFile;
  FILE *tokFile;
  char buff[72];

  //rfp = fopen("./PascalExample.pas", "r");
  rfp = fopen("./InputFiles/ShenoiFile.pas", "r");
  listFile = fopen("./OutputFiles/ListingFileShenoi.txt", "w+");
  tokFile = fopen("./OutputFiles/TokenFileShenoi.txt", "w+");

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
  printList(tokFile);
  fclose(rfp);
  return 0;
}
