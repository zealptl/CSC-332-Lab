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
        if (errno == ENOENT)
            printf("%s does not exist\n", filepath);
        else if (errno == EACCES)
            printf("%s is not accessible\n", filepath);
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