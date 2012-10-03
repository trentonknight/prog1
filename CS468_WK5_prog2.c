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
void processThree(int *fd2, int *fd3);
void processFin(int *fd3,int *fd1);


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
printf("\nProcess Two: %s\n\n", message);
strcpy(nmessage,revChars(message));
printf("Reversed to: %s\n\n", nmessage);
}
close(fd1[READ]);
close(fd2[READ]);
sleep(2);
write(fd2[WRITE],nmessage,strlen(nmessage) + 1);
sleep(1);
close(fd2[WRITE]);
}
void processThree(int *fd2,int *fd3){
int recieved;
static char message[10];
static char up[10];
close(fd2[WRITE]);
recieved = read(fd2[READ], message, 100);
if(recieved){
printf("\nProcess Three: %s\n\n", message);
strcpy(up,upperCase(message));
printf("Set characters to uppercase: %s\n\n", up);
}
close(fd2[READ]);
close(fd3[READ]);
sleep(2);
write(fd3[WRITE],up,strlen(up) + 1);
sleep(1);
close(fd3[WRITE]);
}
void processFin(int *fd3,int *fd1){
int recieved;
static char message[10];
static char up[10];
close(fd3[WRITE]);
recieved = read(fd3[READ], message, 100);
if(recieved){
printf("\nProcess Three: %s\n\n", message);
strcpy(up,upperCase(message));
printf("Set characters to uppercase: %s\n\n", up);
}
close(fd3[READ]);
close(fd1[READ]);
sleep(2);
write(fd1[WRITE],up,strlen(up) + 1);
sleep(1);
close(fd1[WRITE]);
}
