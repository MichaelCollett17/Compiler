#include <stdio.h>
#include <stdbool.h>
#include "./GNBNNode.h"
#include <stdlib.h>
#include "../tokens.h"
#include <string.h>
#include "../Parser.h"

struct gbnode *gnpointer = NULL;
struct gbnode *eye = NULL;
struct gbnode *progHead = NULL;

void checkAddBlueNode(char *lex_in, int type){
  //have to add check for if same name exists
  struct gbnode *link = (struct gbnode*) malloc(sizeof(struct gbnode));
  link->borg = 0;
  link->lex = lex_in;
  link->type = type;
  link->upleft = eye;
  link->right = NULL;
  link->down = NULL;
  eye->right = link;
  printf("Blue node from: %s to: %s\n",eye->lex,link->lex);
  eye = link;
}

void checkAddGreenNode(char *lex_in, int type){
  if(progHead == NULL){
    progHead = (struct gbnode*) malloc(sizeof(struct gbnode));
    progHead->borg = 1;
    progHead->lex = lex_in;
    progHead->type = type;
    progHead->upleft = NULL;
    progHead->right = NULL;
    progHead->down = NULL;
    gnpointer = progHead;
    eye = progHead;
  }
  else{
    //have to add check for if holder is necessary and add holder
    //have to add check for if same name exists
    struct gbnode *link = (struct gbnode*) malloc(sizeof(struct gbnode));
    link->borg = 1;
    link->lex = lex_in;
    link->type = type;
    link->upleft = eye;
    link->right = NULL;
    link->down = NULL;
    eye->down = link;
    gnpointer = link;
    eye = link;
  }
}

void procedureCall(){

}

int getType(char* id_lex){
  struct gbnode tracer = *eye;
  while(tracer.upleft != NULL){
    if(strcmp(tracer.lex, id_lex)==0){
      return tracer.type;
    }
    else{
      tracer = *tracer.upleft;
    }
  }
  writeSemanticError("Variable is not within scope or hasn't been declared");
  return ERR;
}

void popStack(){
  struct gbnode curr = *gnpointer;
  printf("psst... is this it?\n");
  printf("this gn called: %s\n",gnpointer->lex);
  eye = gnpointer->upleft;
  printf("this mah eye: %s\n", eye->lex);
  int cond = 1;
  while(cond == 1){
    if(curr.upleft != NULL){
      curr = *curr.upleft;
      if(curr.borg == 1){//then its a green node
        cond = 0;
        gnpointer = &curr;
        printf("FOUND A GREEN NODE CALLED: %s\n",gnpointer->lex);
      }
    }
    else{
      printf("Ruh Roh ran out of Green nodes!\n");
    }
  }
}

void checkNoParams(){

}

void checkParam(int type){

}
