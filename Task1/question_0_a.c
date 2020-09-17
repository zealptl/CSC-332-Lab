#include <stdio.h>
#include <unistd.h>
#include <errno.h>

int main(int argc, char *argv[])
{
    char *filepath = argv[1];

    // Check file existence
    int doesExist = access(filepath, F_OK);

    if (doesExist == 0)
        printf("%s exists\n", filepath);
    else
    {
        if (errno == ENOENT)
            printf("%s does not exist\n", filepath);
        else if (errno == EACCES)
            printf("%s is not accessible\n", filepath);
        return 0;
    }

    // Check read access ...
    int readAccess = access(filepath, R_OK);
    if (readAccess == 0)
        printf("%s is readable\n", filepath);
    else
    {
        if (errno == EACCES)
            printf("%s is not readable\n", filepath);
    }

    // Check write access ...
    int writeAccess = access(filepath, W_OK);
    if (writeAccess == 0)
        printf("%s is writable\n", filepath);
    else
    {
        if (errno == EACCES)
            printf("%s is not writable\n", filepath);
        return 0;
    }
    return 0;
}