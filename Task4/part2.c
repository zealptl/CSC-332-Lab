#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <ctype.h>

void read_grades_file(char *filepath, int numStudents, int numChapters, int numHomeworks, int grades[numStudents][numChapters * numHomeworks]);
void manager(int numStudents, int numChapters, int numHomeworks, int grades[numStudents][numChapters * numHomeworks], int currChapter);
void worker(int numStudents, int numChapters, int numHomeworks, int grades[numStudents][numChapters * numHomeworks], int currChapter, int currHomework);

int main(int argc, char *argv[])
{
  int numStudents = 0;
  int numChapters = 0;
  int numHomeworks = 0;
  char *filepath = "quiz_grades.txt";

  printf("Enter number of students: ");
  scanf("%d", &numStudents);

  printf("Enter number of chapters: ");
  scanf("%d", &numChapters);

  printf("Enter number of homerworks: ");
  scanf("%d", &numHomeworks);

  int grades[numStudents][numChapters * numHomeworks];
  read_grades_file(filepath, numStudents, numChapters, numHomeworks, grades);

  for (size_t i = 0; i < numChapters; i++)
  {
    if (fork() == 0)
    {
      manager(numStudents, numChapters, numHomeworks, grades, i);
    }
  }

  for (size_t i = 0; i < numChapters; i++)
  {
    wait(NULL);
  }

  exit(0);
}

void read_grades_file(char *filepath, int numStudents, int numChapters, int numHomeworks, int grades[numStudents][numChapters * numHomeworks])
{
  FILE *fp = fopen(filepath, "r");
  size_t MAX_LEN = 200;
  char *line = malloc(MAX_LEN * sizeof(char));
  char *buf;

  for (size_t i = 0; i < numStudents; i++)
  {
    int iterator = 0;
    getline(&line, &MAX_LEN, fp);

    for (size_t j = 0; j < numChapters * numHomeworks; j++)
    {
      while (!isdigit(line[iterator]))
      {
        iterator++;
      }
      buf = &line[iterator];

      while (isdigit(line[iterator]))
      {
        iterator++;
      }

      line[iterator] = '\0';
      iterator++;
      grades[i][j] = atoi(buf);
    }
  }

  free(line);
  fclose(fp);
}

void manager(int numStudents, int numChapters, int numHomeworks, int grades[numStudents][numChapters * numHomeworks], int currChapter)
{
  for (size_t i = 0; i < numHomeworks; i++)
  {
    if (fork() == 0)
    {
      worker(numStudents, numChapters, numHomeworks, grades, currChapter, i);
    }
  }

  for (size_t i = 0; i < numHomeworks; i++)
  {
    wait(NULL);
  }

  exit(0);
}

void worker(int numStudents, int numChapters, int numHomeworks, int grades[numStudents][numChapters * numHomeworks], int currChapter, int currHomework)
{
  float sum = 0.0;

  for (size_t i = 0; i < numStudents; i++)
  {
    sum += grades[i][currChapter * numHomeworks + currHomework];
  }

  float average = sum / numStudents;
  printf("average grade of homework %d in chapter %d: %f\n", currHomework + 1, currChapter + 1, average);
  exit(0);
}