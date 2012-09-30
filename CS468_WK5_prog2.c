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
void getInput(char word[]);


int main()
{
int fd[2];
int fork1_pid = 0;
int fork2_pid = 0;
char word[10];
int count = 0;
 
pipe(fd);

fork1_pid = fork();
getProcessInfo();
getInput(word);
printf("\nword was: \"%s\" \n", word);
fflush(stdout);
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
