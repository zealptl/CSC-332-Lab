#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/shm.h>
#include <time.h>
#include <sys/ipc.h>
#include <signal.h>
#include <sys/wait.h>
#include "sem.h"

int main()
{
  srand(time(NULL));

  // declare semaphores
  int lock = semget(IPC_PRIVATE, 1, 0666 | IPC_CREAT);
  int agent = semget(IPC_PRIVATE, 1, 0666 | IPC_CREAT);
  int paper_semaphore = semget(IPC_PRIVATE, 1, 0666 | IPC_CREAT);
  int tobacco_semaphore = semget(IPC_PRIVATE, 1, 0666 | IPC_CREAT);
  int match_semaphore = semget(IPC_PRIVATE, 1, 0666 | IPC_CREAT);

  // initialize semaphores
  sem_create(lock, 1);
  sem_create(agent, 0);
  sem_create(paper_semaphore, 0);
  sem_create(tobacco_semaphore, 0);
  sem_create(match_semaphore, 0);

  // fork paper process
  int pid1 = fork();
  if (pid1 == 0)
  {
    while (1)
    {
      P(paper_semaphore);
      P(lock);

      printf("paper rolled a cigarette\n");

      V(agent);
      V(lock);
    }
  }

  // fork tobacco process
  int pid2 = fork();
  if (pid2 == 0)
  {
    while (1)
    {
      P(tobacco_semaphore);
      P(lock);

      printf("tobacco rolled a cigarette\n");

      V(agent);
      V(lock);
    }
  }

  // fork match process
  int pid3 = fork();
  if (pid3 == 0)
  {
    while (1)
    {
      P(match_semaphore);
      P(lock);

      printf("match rolled a cigarette\n");

      V(agent);
      V(lock);
    }
  }

  // agent process
  if (fork() == 0)
  {
    for (int i = 0; i < 20; i++)
    {
      P(lock);
      int random = rand() % 3; // pick random smoker

      // wake up smoker according to tunr
      if (random == 0)
      {
        printf("Agent wakes up paper\n");
        V(paper_semaphore);
      }
      else if (random == 1)
      {
        printf("Agent wakes up tobacco\n");
        V(tobacco_semaphore);
      }
      else if (random == 2)
      {
        printf("Agentt wakes up match\n");
        V(match_semaphore);
      }
      int remaining = 20 - i;
      printf("Remaining to give: %d\n", remaining);
      printf("------------------------------------\n");
      V(lock);
      P(agent);
    }

    printf("Smokers are sleeping and waiting for indredients\n");
    printf("Agent is done giving indredients to smokers\n");

    P(lock);
    kill(pid1, SIGTERM);
    kill(pid2, SIGTERM);
    kill(pid3, SIGTERM);
    V(lock);

    printf("Agent canceled all smoker threads\n");
    exit(0);
  }

  wait(NULL);
  exit(0);
}