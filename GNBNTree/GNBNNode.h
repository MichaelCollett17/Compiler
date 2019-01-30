#ifndef GNBNNODE
#define GNBNNODE

struct gbnode{
    struct gbnode *upleft;
    struct gbnode *right;
    struct gbnode *down;
    char *lex;
    int type;
    int borg;// 0 for blue 1 for green
    int array_size;//for aints or areals
};

void checkAddGreenNode(char *lex_in, int type);
void checkAddBlueNode(char *lex_in, int type);
void procedureCall(char* id_lex);
void checkNoParams();
void checkParam(int type);
int getType(char* id_lex);
void popStack();

#endif
