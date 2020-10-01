#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

int main()
{
    int a = 10, b = 25, fq = 0, fr = 0;

    fq = fork();
    if (fq == 0)
    {
        a = a + b;
        printf("a: %d, b: %d, process_id: %d\n", a, b, getpid());
        fr = fork();
        if (fr != 0)
        {
            b = b + 20;
            printf("a: %d, b: %d, process_id: %d\n", a, b, getpid());
        }
        else
        {
            a = (a * b) + 30;
            printf("a: %d, b: %d, process_id: %d\n", a, b, getpid());
        }
    }
    else
    {
        b = a + b - 5;
        printf("a: %d, b: %d, process_id: %d\n", a, b, getpid());
    }

    return 0;
}