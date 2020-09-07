#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>

int main(int argc, char *argv[])
{
    char *filePath = argv[1];
    int fp;

    fp = open(filePath, O_RDWR | O_CREAT, 0777);

    return 0;
}