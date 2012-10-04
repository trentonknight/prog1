#include <signal.h>
#include "processinf.h"

#define READ 0
#define WRITE 1
/**uncomment the printfs below for more verbous output*/

/**write of pipe one*/
void processOne(int *fd1, char word[]){
close(fd1[READ]);
sleep(2);
write(fd1[WRITE],word,strlen(word) + 1);
sleep(1);
close(fd1[WRITE]);
}
/**read pipe one and write pipetwo*/
void processTwo(int *fd1,int *fd2){
int recieved;
static char message[10];
static char nmessage[10];
close(fd1[WRITE]);
recieved = read(fd1[READ], message, 100);
if(recieved){
//printf("\nProcess Two: %s\n\n", message);
strcpy(nmessage,revChars(message));
//printf("Reversed to: %s\n\n", nmessage);
}
close(fd1[READ]);
close(fd2[READ]);
sleep(2);
write(fd2[WRITE],nmessage,strlen(nmessage) + 1);
sleep(1);
close(fd2[WRITE]);
}
/**read of pipe two and write to pipe three*/
void processThree(int *fd2,int *fd3){
int recieved;
static char message[10];
static char up[10];
close(fd2[WRITE]);
recieved = read(fd2[READ], message, 100);
if(recieved){
//printf("\nProcess Three: %s\n\n", message);
strcpy(up,upperCase(message));
//printf("Set characters to uppercase: %s\n\n", up);
}
close(fd2[READ]);
close(fd3[READ]);
sleep(2);
write(fd3[WRITE],up,strlen(up) + 1);
sleep(1);
close(fd3[WRITE]);
}
/**read pipe three and close the end of pipes back at fd1*/
void processFin(int *fd3,int *fd1){
int recieved;
static char message[10];
static char up[10];
close(fd3[WRITE]);
recieved = read(fd3[READ], message, 100);
if(recieved){
printf("\nEnd of Pipes: %s\n\n", message);
}
close(fd3[READ]);
close(fd1[READ]);
sleep(2);
write(fd1[WRITE],up,strlen(up) + 1);
sleep(1);
close(fd1[WRITE]);
}

