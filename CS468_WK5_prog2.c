#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <signal.h>
#include <string.h>
#include <ctype.h>

#define READ 0
#define WRITE 1

void getProcessInfo();



int main()
{
int fd[2];
int fork1_pid = 0;
int fork2_pid = 0;
char word[10], ch = '0x0';
int count = 0;
 
pipe(fd);

fork1_pid = fork();
getProcessInfo();
if(fork1_pid == 0){
fputs("Enter up to ten characters: ", stdout);
fflush(stdout);
if(fgets(word, sizeof word, stdin) != NULL)
{
char *newline = strchr(text, '\n');
if(newline != NULL)
{
*newline = '\0';
}
}
printf("\nword was: \"%s\" \n", word);
}
return 0;
}

void getProcessInfo()
{
printf("Parent is: %d...\n",getppid());
printf("Fork running is: %d...\n",getpid());
}
