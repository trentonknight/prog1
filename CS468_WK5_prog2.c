#include <signal.h>
#include "processinf.h"
#include "psthreads.h"
/////////////////////////////////////////////////////////////////////////
/// Compile with: gcc -ggdb CS468_WK5_prog2.c processinf.c psthreads.c///
////////////////////////////////////////////////////////////////////////
int main()
{
char word[10];
int fd1[2];
int fd2[2];
int fd3[2];
int f1_pid;
int f2_pid;
int f3_pid;
int f4_pid;
pipe(fd1);
pipe(fd2);
pipe(fd3);
getInput(word);
f1_pid = fork();
if(f1_pid == 0){
processOne(fd1,word);
}
sleep(5);
kill(f1_pid, SIGSTOP);
f2_pid = fork();
if(f2_pid == 0){
processTwo(fd1,fd2);
}
sleep(5);
kill(f2_pid, SIGSTOP);
f3_pid =  fork();
if(f3_pid == 0){
processThree(fd2,fd3);
}
sleep(5);
kill(f3_pid, SIGSTOP);
f4_pid = fork();
if(f4_pid == 0){
processFin(fd3,fd1);
}
sleep(10);
kill(f4_pid, SIGINT);
kill(f3_pid, SIGINT);
kill(f2_pid, SIGINT);
kill(f1_pid, SIGINT);

return 0;
}
