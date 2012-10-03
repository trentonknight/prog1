#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <signal.h>
#include <string.h>
#include <ctype.h>
//#include <fcntl.h>
//#include <pthread.h>

/*check threads*/
 void processInfo()
 {
 printf("Parent is: %d...\n",getppid());
 printf("Fork running is: %d...\n",getpid());
 }
/*get user input*/
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
/*reverse char*/
char* revChars(char revword[]){
int ten = 0;
int flip = strlen(revword);
int loopr = flip + 1;
static char newWord[10] = {0};
for(ten = 0; ten < loopr; ten++){
flip--;
newWord[flip] = revword[ten];
}
return newWord;
}


