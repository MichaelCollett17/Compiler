#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

#include "tokens.h"
#include "./Machines/machines.h"
//#include "./LinkedLists/TokenLinkedList.h"
#include "./LinkedLists/TokenLLV2.h"
#include "reservedWords.h"
#include "LexicalAnalyzer.h"
#include "./Productions/productions.h"

FILE *listFile;
char *eof;

void writeSyntaxError(char *expecting, char *received){
  fprintf(listFile, "-SYNTAX ERROR-\n\tExpecting: %s\n\tReceived: %s\n",
    expecting, received);
}

void parse(){
  tok = getNextToken();
  program();
  match(EOFTOKEN, 0, "EOF");//match($)
  return;
}

int main()
{
  FILE *rfp;
  FILE *tokFile;
  char buff[72];

  rfp = fopen("./InputFiles/ParserTesting.pas", "r");
  listFile = fopen("./OutputFiles/ListingFileParserTest.txt", "w+");
  tokFile = fopen("./OutputFiles/TokenFileParserTest.txt", "w+");

  loadReservedWords();

  eof = loadBuffer(buff,rfp);
  int lineNum = 1;
  while(eof!=NULL){
    printBuffer(buff,listFile,lineNum);
    machines(buff, listFile, lineNum);
    //parse();
    eof = loadBuffer(buff,rfp);
    lineNum++;
    //break;
  }
  printList(tokFile);
  fclose(rfp);
  return 0;
}
