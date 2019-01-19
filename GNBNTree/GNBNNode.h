#ifndef GNBNNODE
#define GNBNNODE

struct gbnode{
    struct gbnode *upleft;
    struct gbnode *right;
    struct gbnode *down;
    char *lex;
    char *type;
    int borg;// 0 for blue 1 for green
    int array_size;//for aints or areals
};

void checkAddGreenNode(char *lex_in, char *type);
void checkAddBlueNode();
void procedureCall();
int getType();
void popStack();

#endif
