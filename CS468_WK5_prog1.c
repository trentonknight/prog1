#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <signal.h>

int main()

{
int status = 0,
pid1 = 0,
pid2 = 0,
returnChild_pid = 0,
i = 0;

pid1 = fork();

if(pid1 == 0){

printf("First child process [ %d ].\n", getpid());
 printf("\n");
for(i = 1; i < 6; i++){
   printf("Counting...%d\n",i);
   sleep(1);
 }
printf("First child [ %d ] will exit now.\n", getpid());
kill (pid1, SIGSTOP);
exit(0);
}

pid2 = fork();
if(pid2 == 0){
printf("Second child process [ %d ].\n", getpid());
printf("\n");
 for(i = 1; i < 6; i++){
   printf("Counting...%d\n",i);
   sleep(1);
 }
printf("Second child [ %d ] will exit now.\n", getpid());
exit(0);
}


return 0;
}
