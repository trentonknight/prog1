#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <signal.h>

int main()

{
int pid1 = 0,
pid2 = 0,
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
exit(0);
 }

kill (pid1, SIGSTOP);
 printf("Parent process [ %d ] suspended first child process [ %d ]...\n", getppid(), getpid());
 //pid2 = fork();
if(pid2 == 0){
printf("Second child process [ %d ] starting...\n", getpid());
printf("Second child's parent process is [ %d ].\n", getppid());
printf("Process [ %d ] will display process status:\n", getpid());
exit(0);
 }
kill (pid1, SIGCONT);
//kill (pid1, SIGINT);
//kill (pid2, SIGINT);
return 0;
}
