#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <signal.h>
#include <string.h>
#include <ctype.h>
#include <fcntl.h>
#include <pthread.h>

#define READ 0
#define WRITE 1

void getProcessInfo();
void getInput(char word[]);
void processOne(int *fd, char word[]);
void processTwo(int *fd);
void processThree();

int main()
{
char word[10];
int fd[2];
int f1_pid;
int f2_pid;
pipe(fd);
getInput(word);
f1_pid = fork();
if(f1_pid == 0){
printf("Sending piped message...\n");
processOne(fd,word);
}
sleep(5);
kill(f1_pid, SIGSTOP);
f2_pid = fork();
getProcessInfo();
if(f2_pid == 0){
printf("Reading piped message...\n");
processTwo(fd);
}
sleep(5);
kill(f2_pid, SIGINT);
kill(f1_pid, SIGINT);
return 0;
}

void getProcessInfo()
{
printf("Parent is: %d...\n",getppid());
printf("Fork running is: %d...\n",getpid());
}
void getInput(char word[])
{
fputs("Enter up to ten characters: ", stdout);
fflush(stdout);
if(fgets(word, sizeof word, stdin) != NULL)
{
char *newline = strchr(word, '\n');
if(newline != NULL)
{
*newline = '\0';
}
}
}
void processOne(int *fd, char word[]){
close(fd[READ]);
sleep(2);
write(fd[WRITE],word,strlen(word) + 1);
sleep(1);
close(fd[WRITE]);
}
void processTwo(int *fd){
int recieved;
int ten = 0;
int message[10];
int newWord[10];
close(fd[WRITE]);
for(ten = 0; ten < 10; ten++){
recieved = read(fd[READ], message, 1);
printf("\nMessage recieved from pipe: %s", message);
newWord[ten] = message[0];
}
}
void processThree(){
}
