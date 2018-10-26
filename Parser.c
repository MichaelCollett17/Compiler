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
FILE *rfp;
FILE *tokFile;
char buff[72];
int lineNum;


void writeSyntaxError(char *expecting, char *received){
  fprintf(listFile, "-SYNTAX ERROR-\n\tExpecting: %s\n\tReceived: %s\n",
    expecting, received);
  printf("-SYNTAX ERROR-\n\tExpecting: %s\n\tReceived: %s\n",
    expecting, received);
}

void getToken(){
  struct tokenNode check = getNextToken();
  if(check.lineNo != -10){
    tok = check;
  }
  else{
    if(eof!=NULL){
      eof = loadBuffer(buff,rfp);
      lineNum++;
      printBuffer(buff,listFile,lineNum);
      machines(buff, listFile, lineNum);
      getToken();//calls self because the previous call needed getToken still!
    }
    else{
      //DELTE THIS WHOLE ELSE STATEMENT SHOULDN'T BE USEFUL ONCE DONE
      printf("PARSE OVER\n");
      insertToken(EOF, "EOF", EOFTOKEN, 0);
    }
  }
}

void parse(){
  getToken();
  program();
  match(EOFTOKEN, 0, "EOF");//match($)
  return;
}

int main()
{
  rfp = fopen("./InputFiles/ParserTesting.pas", "r");
  listFile = fopen("./OutputFiles/ListingFileParserTest.txt", "w+");
  tokFile = fopen("./OutputFiles/TokenFileParserTest.txt", "w+");

  loadReservedWords();

  eof = loadBuffer(buff,rfp);
  lineNum = 1;
  if(eof!=NULL){
    printBuffer(buff,listFile,lineNum);
    machines(buff, listFile, lineNum);
    parse();
    //eof = loadBuffer(buff,rfp);
    //lineNum++;
    //break;
  }
  printList(tokFile);
  fclose(rfp);
  return 0;
}
