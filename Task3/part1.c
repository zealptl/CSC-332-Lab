#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <stdio.h>

int main()
{
  pid_t pid = fork();

  if (pid == 0)
  {
    printf("Child created! My pid is %d\n", getpid());
    fflush(stdout);
    execl("/bin/date", "date", NULL);
  }

  wait(NULL);
  exit(0);
}