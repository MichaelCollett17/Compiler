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
struct gbnode *greens_head = NULL;
struct gbnode *greens_tail = NULL;
struct gbnode *param_checker = NULL;

void checkAddBlueNode(char *lex_in, int type){
  //have to add check for if same name exists
  struct gbnode checker = *eye;
  int cond = 1;
  while((checker.upleft != NULL) && (cond==1) && (checker.borg==0)){
    if(strcmp(checker.lex, lex_in)==0){
      cond = 0;
      writeSemanticError("Cannot have duplicate variable until and up to the nearest procedure/program");
      return;
    }
    else{
      checker = *checker.upleft;
    }
  }
  //add node
  if(cond==1){
    struct gbnode *link = (struct gbnode*) malloc(sizeof(struct gbnode));
    link->borg = 0;
    link->lex = lex_in;
    link->type = type;
    link->type2 = -1;
    link->upleft = eye;
    link->right = NULL;
    link->down = NULL;
    eye->right = link;
    printf("Blue node from: %s to: %s\n",eye->lex,link->lex);
    eye = link;
  }
}

void checkAddBlueNodeParam(char *lex_in, int type, int paramtype){
  //have to add check for if same name exists
  struct gbnode checker = *eye;
  int cond = 1;
  while((checker.upleft != NULL) && (cond==1) && (checker.borg==0)){
    if(strcmp(checker.lex, lex_in)==0){
      cond = 0;
      writeSemanticError("Cannot have duplicate variable until and up to the nearest procedure/program");
      return;
    }
    else{
      checker = *checker.upleft;
    }
  }
  //add node
  if(cond==1){
    struct gbnode *link = (struct gbnode*) malloc(sizeof(struct gbnode));
    link->borg = 0;
    link->lex = lex_in;
    link->type = type;
    link->type2 = paramtype;
    link->upleft = eye;
    link->right = NULL;
    link->down = NULL;
    eye->right = link;
    printf("Blue node from: %s to: %s\n",eye->lex,link->lex);
    eye = link;
  }
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
    progHead->nextGreen = NULL;
    gnpointer = progHead;
    eye = progHead;
    greens_head = progHead;
    greens_tail = progHead;
  }
  else{
    //check if gn already exists
    struct gbnode checker = *greens_head;
    int condit = 0;
    while((checker.nextGreen != NULL) && (condit ==0)){
      if(strcmp(checker.lex,lex_in)==0){
        writeSemanticError("Cannot have duplicate procedure/program names");
        condit = 1;
      }
      else{
        checker = *checker.nextGreen;
      }
    }
    if((strcmp(checker.lex,lex_in)==0) && (condit==0)){
      writeSemanticError("Cannot have duplicate procedure/program names");
    }
    //add green node
    struct gbnode *link = (struct gbnode*) malloc(sizeof(struct gbnode));
    link->borg = 1;
    link->lex = lex_in;
    link->type = type;
    link->upleft = eye;
    link->right = NULL;
    link->down = NULL;
    link->nextGreen = NULL;
    greens_tail->nextGreen = link;
    greens_tail = link;
    eye->down = link;
    gnpointer = link;
    eye = link;
  }
}

void procedureCall(char *lex_in){
  struct gbnode *call_checker = greens_head;
  int condit = 0;
  while((call_checker->nextGreen!= NULL) && (condit == 0)){
    if(strcmp(call_checker->lex,lex_in)==0){
      condit=1;
    }
    else{
      call_checker = call_checker->nextGreen;
    }
  }
  if((strcmp(call_checker->lex,lex_in)!=0) && (condit==0)){
    writeSemanticError("Procedure not found");
    param_checker = NULL;
    return;
  }
  else{
    param_checker = call_checker;
  }
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
  struct gbnode *curr = gnpointer;
  if(gnpointer->upleft != NULL){
    eye = gnpointer->upleft;
    struct gbnode *hold = (struct gbnode*) malloc(sizeof(struct gbnode));
    hold->borg = 0;
    hold->lex = "HOLD_DONT_USE_AS_VAR_NAME";
    hold->type = HOLDER;
    hold->upleft = eye;
    hold->right = NULL;
    hold->down = NULL;
    eye->right = hold;
    printf("Blue node hold from: %s to: hold\n",eye->lex);
    eye = hold;
  }
  else{
    printf("Damn it's null\n");
  }
  int cond = 1;
  while(cond == 1){
    if(curr->upleft != NULL){
      curr = curr->upleft;
      printf("named: %s\n",curr->lex);
      if(curr->borg == 1){//then its a green node
        cond = 0;
        gnpointer = curr;
        printf("FOUND A GREEN NODE CALLED: %s\n",gnpointer->lex);
      }
    }
    else{
      printf("Ruh Roh ran out of Green nodes!\n");
    }
  }
}

void checkNoParams(){
  if(param_checker == NULL){
    return;
  }
  if(param_checker->right == NULL){
    return;
  }
  else{
    struct gbnode isparam = *param_checker->right;
    if(isparam.type2 == PPPARAM){
      writeSemanticError("Parameters of caller do not match procedure");
    }
  }
}

void checkParam(int type){
  if(param_checker == NULL){
    return;
  }
  //advance param_checker to the right and check it's a thing
  if(param_checker->right == NULL){
    writeSemanticError("Parameters of caller do not match procedure");
  }
  else{
    param_checker = param_checker->right;
    if((param_checker->type == type) && (param_checker->type2 == PPPARAM)){
      return;
    }
    else{
      writeSemanticError("Parameter type of caller do not match procedure parameter type");
    }
  }
}

void checkNoMoreParams(){
  if(param_checker->right != NULL){
    param_checker = param_checker->right;
    if(param_checker->type2 == PPPARAM){
      writeSemanticError("Parameters of caller do not match parameters of procedure");
    }
    param_checker = NULL;
  }
}
