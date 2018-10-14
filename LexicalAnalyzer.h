#ifndef LEXICALANALYZER
#define LEXICALANALYZER
int printBuffer(char *buff, FILE *listFile, int lineNum);
char* loadBuffer(char *buff, FILE *fp);
int machines(char *buff, FILE *listFile, int lineNum);
int processMachineOutput(struct machOut out, int lineNum, int b);
int stringLength(char *s);
#endif
