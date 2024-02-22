// Aryan Maurya
// 20223054
/*The 'my_npipe_reader' program will set up a named pipe using 'mkfifo()', open it read only, and read strings from it until it receivesthe string 'exit'.*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>

#define BUFFER_SIZE 1024

int main() {
    char buffer[BUFFER_SIZE];
    int fd;

    // Create the named pipe
    if (mkfifo("mypipe.txt", 0666) == -1) {
        perror("mkfifo");
        exit(EXIT_FAILURE);
    }

    // Open the named pipe for reading
    fd = open("mypipe.txt", O_RDONLY);

    if (fd == -1) {
        perror("open");
        exit(EXIT_FAILURE);
    }

    printf("Waiting for input...\n");

    // Read strings from the named pipe until 'exit' is received
    while (1) {
        ssize_t bytesRead = read(fd, buffer, BUFFER_SIZE);

        if (bytesRead == -1) {
            perror("read");
            close(fd);
            exit(EXIT_FAILURE);
        }

        buffer[bytesRead] = '\0';

        if (strcmp(buffer, "exit\n") == 0) {
            printf("Exiting\n");
            break;
        }

        printf("Got it: '%s'", buffer);
    }

    // Close the named pipe
    close(fd);

    // Remove the named pipe
    unlink("mypipe.txt");

    return 0;
}
