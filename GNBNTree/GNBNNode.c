#include <stdio.h>
#include <stdbool.h>
#include "./GNBNNode.h"
#include <stdlib.h>


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
  return -200;
}

void popStack(){

}

void checkNoParams(){

}

void checkParam(int type){

}
