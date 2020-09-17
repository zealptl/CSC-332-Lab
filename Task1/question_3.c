#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>

int main(int argc, char *argv[])
{
    char *sourcePath = argv[1];
    char *destinationPath = argv[2];

    // Check if source file exists
    int doesExist = access(sourcePath, F_OK);
    if (doesExist != 0)
    {
        perror("Error: ");
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

    // start copying
    char buf[75], temp;
    int count = 0;
    do
    {
        count = 0;
        for (int i = 0; i < 75; i++)
        {
            if (read(fdSource, &temp, 1))
            {
                count++;
                if (temp == '5')
                    buf[i] = 'O';
                else
                    buf[i] = temp;
            }
            else
            {
                break; // nothing more left to read
            }
        }
        write(fdDestination, buf, count); // write 75 read characters onto the file
        write(fdDestination, "ABC", 3);
    } while (count == 75);

    close(fdSource);
    close(fdDestination);
    return 0;
}