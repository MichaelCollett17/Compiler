#include <stdio.h>
#include <stdbool.h>
#include "./GNBNNode.h"
#include <stdlib.h>


struct gbnode *gnpointer = NULL;
struct gbnode *eye = NULL;
struct gbnode *progHead = NULL;

void checkAddBlueNode(char *lex_in, int type){

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
  }
  else{
    struct gbnode *link = (struct gbnode*) malloc(sizeof(struct gbnode));
    link->borg = 1;
    link->lex = lex_in;
    link->type = type;
    link->upleft = eye;
    link->right = NULL;
    link->down = NULL;
    eye->down = link;//may need deref and may need to check if eye already has something down, but idk if he'll check that
    gnpointer = link;//may need dereference
    eye = link;//may need dereference
  }
}

void procedureCall(){

}

int getType(){
  return -200;
}

void popStack(){

}
