#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>

int main(int argc, char *argv[])
{
    char *filepath = argv[1];

    // check if file exists
    int doesExist = access(filepath, F_OK);

    if (doesExist != 0)
    {
        perror("Error");
        return 0;
    }

    int fd = open(filepath, O_RDONLY);

    char buf[1];
    while (read(fd, buf, 1))
    {
        printf("%s", buf);
    }
    printf("\n");

    close(fd);

    return 0;
}