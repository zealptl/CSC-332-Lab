#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void parse_command(char *command, char *commandv[]);

int main(int argc, char *argv[])
{
  size_t MAX_LEN = 200;
  char *command = malloc(MAX_LEN * sizeof(char));
  char *commandv[20];

  do
  {
    printf("### ");

    getline(&command, &MAX_LEN, stdin);
    parse_command(command, commandv);

    if (strcmp(commandv[0], "quit") == 0)
    {
      exit(0);
    }

    if (fork() == 0)
    {
      execvp(commandv[0], commandv);
    }

    wait(NULL);
  } while (1);

  exit(0);
}

void parse_command(char *command, char *commandv[])
{
  int iterator = 0;
  int i = 0;

  do
  {
    while (command[iterator] == ' ' || command[iterator] == '\0')
    {
      iterator++;
    }

    if (command[iterator] == '\n')
    {
      break;
    }

    commandv[i] = &command[iterator];

    while (command[iterator] != ' ' && command[iterator] != '\n')
    {
      iterator++;
    }

    if (command[iterator] == '\n')
    {
      command[iterator] = '\0';
      i++;
      break;
    }

    command[iterator] = '\0';
    i++;

  } while (1);

  commandv[i] = (char *)NULL;
  return;
}