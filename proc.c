#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main() 
{
    pid_t ppid;
    ppid = getpid();
    printf("Root pid: %d, His parent: %d, Group: %d, Session: %d\n", getpid(), getppid(), getgid(), getsid(getpid()));
    for(int i = 0; i < 2; i++)
    {
        ppid = fork();	
        if(ppid == 0 && i == 0)
        {
            printf("Child pid on level 1: %d, His parent: %d, Group: %d, Session: %d\n", getpid(), getppid(), getgid(), getsid(getpid()));
            for(int j = 0; j < 2; j++)
            {
                ppid = fork();
                if(ppid == 0)
                {
                    printf("Child pid on level 2: %d, His parent: %d, Group: %d, Session: %d\n", getpid(), getppid(), getgid(), getsid(getpid()));
                    sleep(5);
                    wait(NULL);
                    printf("End process %d\n", getpid());
                    exit(0);
                }
                else if(ppid == -1)
                {
                    printf("ERROR!\n");
                    exit(1);
                }
            }
            wait(NULL);
            printf("End process %d\n", getpid());
            exit(0);
        }
        else if(ppid == 0 && i == 1)
        {
            printf("Child pid on level 1: %d, His parent: %d, Group: %d, Session: %d\n", getpid(), getppid(), getgid(), getsid(getpid()));
            ppid = fork();
            if(ppid == 0)
            {
                printf("Child pid on level 2: %d, His parent: %d, Group: %d, Session: %d\n", getpid(), getppid(), getgid(), getsid(getpid()));
                sleep(5);
                wait(NULL);
                printf("End process %d\n", getpid());
                exit(0);
            }
            else if(ppid == -1)
            {
                printf("ERROR!\n");
                exit(1);
            }
            wait(NULL);
            printf("End process %d\n", getpid());
            exit(0);
        }
        else if(ppid == -1)
        {
            printf("ERROR!\n");
            exit(1);
        }
    }
    wait(NULL);
    printf("End process %d\n", getpid());
    exit(0);
}
