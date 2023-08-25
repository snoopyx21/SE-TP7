#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define MAX 1000
int main(void)
{
    
    int tube[2];  
    pid_t pid1;
    pid_t pid2; 
    if( pipe(tube) == -1) perror("pipe");
    pid1=fork();
    switch(fork())
    {
        case -1 : 
            perror("fork()");
            exit(1);
        case 0 :
            if(close(tube[0]) == -1)
            { 
                perror("close");
                return -1;
            }
            if (dup2(tube[1],1)==-1) perror("dup2");
            if (close(tube[1]) ==-1) perror("close");
            execlp("ps", "ps", "eaux",NULL);
            perror("execlp");
            exit(1);
        default :
            break;
    }
    int tube2[2];
    if (pipe(tube2) == -1) perror("pipe");
    pid2=fork();
    switch(pid2)
    {
        case -1 :
            perror("fork()");
            exit(1);
        case 0 :
            if (close(tube[1]) ==-1) perror("close"); 
            if (close(tube2[0])==-1) perror("close");
            if (dup2(tube2[1],1)==-1) perror("dup2"); 
            if (close(tube2[1]) == -1) perror("close");
            if (dup2(tube[0],0)==-1) perror("dup2");
            if (close(tube[0]) ==-1) perror("close");
            execlp("grep", "grep", "^root",NULL);
            perror("execlp");
            exit(1);
        default :
            if(close(tube[1]) ==-1) perror("close");    
            if (close(tube[0]) ==-1) perror("close");
            if(close(tube2[1]) ==-1) perror("close");
            if (dup2(tube2[0],0) ==-1) perror("dup2");
                
            if (close(tube2[0])==-1) perror("close");
            execlp("wc","wc","-l",NULL);
            perror("execlp");
            exit(1);
            
    }
    return 0;
}

