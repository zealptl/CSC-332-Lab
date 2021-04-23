#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <time.h>

void *smoker(void *arg);
void *agent();

pthread_t agent_thread, paper_thread, tobacco_thread, match_thread;
pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t agent_mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t paper_mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t tobacco_mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t match_mutex = PTHREAD_MUTEX_INITIALIZER;

int main()
{
  srand(time(NULL));

  // Initialize mutexes
  pthread_mutex_lock(&agent_mutex);
  pthread_mutex_lock(&paper_mutex);
  pthread_mutex_lock(&tobacco_mutex);
  pthread_mutex_lock(&match_mutex);

  // to determine turn of smoker
  char *paper_id = "0";
  char *tobacco_id = "1";
  char *match_id = "2";

  // create threads
  pthread_create(&agent_thread, NULL, agent, NULL);
  pthread_create(&paper_thread, NULL, smoker, (void *)paper_id);
  pthread_create(&tobacco_thread, NULL, smoker, (void *)tobacco_id);
  pthread_create(&match_thread, NULL, smoker, (void *)match_id);

  // wait for agent thread to finish
  pthread_join(agent_thread, NULL);

  exit(0);
}

void *smoker(void *arg)
{
  const char *turn = (char *)arg;
  int id = atoi(turn);

  while (1)
  {
    // Put smoker to sleep according to turn
    if (id == 0)
    {
      pthread_mutex_lock(&paper_mutex);
    }
    else if (id == 1)
    {
      pthread_mutex_lock(&tobacco_mutex);
    }
    else if (id == 2)
    {
      pthread_mutex_lock(&match_mutex);
    }

    pthread_mutex_lock(&lock);

    // roll cigarette according to turn
    if (id == 0)
    {
      printf("paper_thread rolled a cigarette\n");
    }
    else if (id == 1)
    {
      printf("tobacco_thread rolled a cigarette\n");
    }
    else if (id == 2)
    {
      printf("match_thread rolled a cigarette\n");
    }

    pthread_mutex_unlock(&agent_mutex);
    pthread_mutex_unlock(&lock);
  }
}

void *agent()
{
  for (int i = 0; i < 20; i++)
  {
    pthread_mutex_lock(&lock);
    int random = rand() % 3; // pick random smoker

    // wake up thread according to turn
    if (random == 0)
    {
      printf("Agent wakes up paper_thread\n");
      pthread_mutex_unlock(&paper_mutex);
    }
    else if (random == 1)
    {
      printf("Agent wakes up tobacco_thread\n");
      pthread_mutex_unlock(&tobacco_mutex);
    }
    else if (random == 2)
    {
      printf("Agent wakes up match_thread\n");
      pthread_mutex_unlock(&match_mutex);
    }
    int remaining = 20 - i;
    printf("Remaining to give: %d\n", remaining);
    printf("------------------------------------\n");
    pthread_mutex_unlock(&lock);
    pthread_mutex_lock(&agent_mutex);
  }

  printf("Smokers are sleeping and waiting for indredients\n");
  printf("Agent is done giving indredients to smokers\n");

  pthread_mutex_lock(&lock);
  pthread_cancel(paper_thread);
  pthread_cancel(tobacco_thread);
  pthread_cancel(match_thread);
  pthread_mutex_unlock(&lock);

  printf("Agent canceled all smoker threads\n");
}