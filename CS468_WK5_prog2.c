#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <signal.h>
#include <string.h>
#include <ctype.h>
#include <fcntl.h>
#include <pthread.h>
#include "processinf.h"

#define READ 0
#define WRITE 1

//void getInput(char word[]);
void processOne(int *fd, char word[]);
void processTwo(int *fd);
//char* revChars(char revword[]);


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
printf("Creating piped message...\n");
processOne(fd,word);
}
sleep(5);
kill(f1_pid, SIGSTOP);
f2_pid = fork();
if(f2_pid == 0){
printf("Reading pipe from f1_pid...\n");
processTwo(fd);
}
sleep(5);
kill(f2_pid, SIGINT);
kill(f1_pid, SIGINT);
return 0;
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
int message[10];
close(fd[WRITE]);
recieved = read(fd[READ], message, 100);
if(recieved){
printf("\nMessage recieved from pipe: %s\n\n", message);
printf("revChar call: %s\n\n", revChars(message));
}
close(fd[READ]);
}

