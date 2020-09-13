#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>

int main(int argc, char *argv[])
{
    char *sourcePath = argv[1];
    char *destinationPath = argv[2];

    int doesExist = access(sourcePath, F_OK);

    if (doesExist != 0)
    {
        if (errno == ENOENT)
            printf("%s does not exist\n", sourcePath);
        else if (errno == EACCES)
            printf("%s is not accessible\n", sourcePath);
        return 0;
    }

    int fdSrc = open(sourcePath, O_RDONLY);
    if (fdSrc == -1)
    {
        perror("When opening source file");
        return 1;
    }

    int fdDestination = open(destinationPath, O_WRONLY | O_CREAT, 0777);
    if (fdDestination == -1)
    {
        perror("When opening destination file");
        return 1;
    }

    char buf[1];
    while (read(fdSrc, buf, 1))
    {
        write(fdDestination, buf, 1);
    }

    return 0;
}