#ifdef PSTHREADS_H_INCLUDED
#define PSTHREADS_H_INCLUDED
void processOne(int *fd1, char word[]);
void processTwo(int *fd1,int *fd2);
void processThree(int *fd2,int *fd3);
void processFin(int *fd3,int *fd1);
#endif
