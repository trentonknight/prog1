#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <signal.h>

int main()

{
int pid1 = 0,
pid2 = 0,
i = 0,
ret = 0,
status = 0;


pid1 = fork();

if(pid1 == 0){

printf("First child process %d .\n", getpid());
printf("\n");
for(i = 1; i < 6; i++){
   printf("Counting...%d\n",i);
   sleep(1);
 }
exit(0);
kill (pid1, SIGSTOP);
printf("Parent process  %d  suspended first child process  %d ...\n", getppid(), getpid());
}
/*sleep and let first child finish...*/
sleep(5);
pid2 = fork();
if(pid2 == 0){
printf("Second child process  %d  starting...\n", getpid());
printf("Second child's parent process is  %d .\n", getppid());
printf("Process  %d  will display process status:\n", getpid());
if ((execl ("/bin/ps", "ps", "-M", NULL)) == -1)
{
perror("execl failed!");
exit(1);
}
exit(0);
}
/*sleep and let second child finish...*/
sleep(5);
kill (pid2, SIGINT);
if(pid2 != 0){
ret = wait(&status);
printf("Second child process %d terminated.\n",ret);
}
kill (pid1, SIGCONT);
//sleep(5);
kill (pid1, SIGINT);
if(pid1 != 0){
ret = wait(&status);
printf("First child process %d terminated.\n", ret);
}
exit(5);
return 0;
}
