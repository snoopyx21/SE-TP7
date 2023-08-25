#include <errno.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>
#define MAX 1000

int main(void)
{
    char buffer[MAX];
    int tube[2];   
    int n;
    int status;
    int descripteur;
    if (mkfifo("~/cours_L2/semestre2/SE/TP7/exercice9_6/fifo", 0777) ==-1)
    {
        perror("mkfifo");
        return 1;
    }
    if (descripteur=open("toto",O_RDONLY | O_WRONLY) ==-1)
    {
        perror("open");
        return 1;
    }        
    while( (n=read("toto",buffer,MAX)) > 0 )
    {
        if ( write("toto",buffer,n) == -1)
        {
            perror("write");
        }
    }
    return 0;
}

