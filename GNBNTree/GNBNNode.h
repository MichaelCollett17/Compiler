#ifndef GNBNNODE
#define GNBNNODE
struct gbnode{
    struct gbnode *upleft;
    struct gbnode *right;
    struct gbnode *down;
    char *lex;
    char *type;
    int borg;// 0 for blue 1 for green
};

#endif
