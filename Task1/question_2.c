#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>

int main(int argc, char *argv[])
{
    char *sourcePath = argv[1];
    char *destinationPath = argv[2];

    // check if source file exists
    int doesExist = access(sourcePath, F_OK);
    if (doesExist != 0)
    {
        perror("Error");
        return 0;
    }

    int fdSource = open(sourcePath, O_RDONLY);
    if (fdSource == -1)
    {
        perror("Error");
        return 1;
    }

    int fdDestination = open(destinationPath, O_WRONLY | O_CREAT, 0777);
    if (fdDestination == -1)
    {
        perror("Error");
        return 1;
    }

    // Read and copy to destination file
    char buf[1];
    while (read(fdSource, buf, 1))
    {
        write(fdDestination, buf, 1);
    }

    close(fdSource);
    close(fdDestination);

    return 0;
}