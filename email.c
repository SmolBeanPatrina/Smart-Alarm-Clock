#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <time.h>
#include <string.h>
#include <math.h>
#include <stdbool.h>
#include <pthread.h>
#include <unistd.h>
#include <ctype.h>
void runCommand(char *command){
FILE *pipe = popen(command, "r");
char buffer[1024];
while (!feof(pipe) && !ferror(pipe)){
if (fgets(buffer, sizeof(buffer), pipe) == NULL)
break;
}
int exitCode = WEXITSTATUS(pclose(pipe));
if (exitCode != 0){
perror("Unable to execute command:");
printf(" command: %s\n", command);
printf(" exit code: %d\n", exitCode);
}
}


int main(){
    runCommand("echo \"Sorry boss, I can not come to work today because I'm sick\" | mail -s \"Day off\" alexsyc97@gmail.com");

    return 0;
}

