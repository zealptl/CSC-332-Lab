#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

int main()
{
    pid_t child;

    child = fork();
    if (child < 0)
    {
        fprintf(stderr, "Error occured while forking\n");
        return -1;
    }
    else if (child == 0)
    {
        printf("I am child one, my pid is: %d\n", getpid());
        exit(0);
    }
    else
    {
        printf("Parent is waiting\n");
        waitpid(child);
        printf("Parent is done waiting\n");
    }

    child = fork();
    if (child < 0)
    {
        fprintf(stderr, "Error occured while forking\n");
        return -1;
    }
    else if (child == 0)
    {
        printf("I am child two, my pid is: %d\n", getpid());
        exit(0);
    }
    else
    {
        printf("Parent is waiting\n");
        waitpid(child);
        printf("Parent is done waiting\n");
    }

    return 0;
}