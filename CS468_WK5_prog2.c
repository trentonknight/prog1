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

void processOne(int *fd1, char word[]);
void processTwo(int *fd1, int *fd2);


int main()
{
char word[10];
int fd1[2];
int fd2[2];
int fd3[2];
int f1_pid;
int f2_pid;
pipe(fd1);
pipe(fd2);
pipe(fd3);
getInput(word);
f1_pid = fork();
if(f1_pid == 0){
printf("Creating piped message fd1...\n");
processOne(fd1,word);
}
sleep(5);
kill(f1_pid, SIGSTOP);
f2_pid = fork();
if(f2_pid == 0){
printf("Reading pipe from f1_pid...\n");
processTwo(fd1,fd2);
}
sleep(5);
kill(f2_pid, SIGINT);
kill(f1_pid, SIGINT);
return 0;
}
void processOne(int *fd1, char word[]){
close(fd1[READ]);
sleep(2);
write(fd1[WRITE],word,strlen(word) + 1);
sleep(1);
close(fd1[WRITE]);
}
void processTwo(int *fd1,int *fd2){
int recieved;
static char message[10];
static char nmessage[10];
close(fd1[WRITE]);
recieved = read(fd1[READ], message, 100);
if(recieved){
printf("\nMessage recieved from pipe fd1: %s\n\n", message);
strcpy(nmessage,revChars(message));
printf("Reversed to: %s\n\n", nmessage);
}
close(fd1[READ]);
printf("\nClosed fd1 and opening fd2...\n");
close(fd2[READ]);
sleep(2);
write(fd2[WRITE],nmessage,strlen(nmessage) + 1);
sleep(1);
close(fd2[WRITE]);
}

