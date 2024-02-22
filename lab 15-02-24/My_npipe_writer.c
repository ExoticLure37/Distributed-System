// Aryan Maurya
// 20223054

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

#define BUFFER_SIZE 1024

int main() {
    char buffer[BUFFER_SIZE];
    int fd;

    // Open the named pipe for writing
    fd = open("mypipe.txt", O_WRONLY);

    if (fd == -1) {
        perror("open");
        exit(EXIT_FAILURE);
    }

    while (1) {
        printf("Enter Input: ");
        fgets(buffer, BUFFER_SIZE, stdin);

        // Write the string to the named pipe
        ssize_t bytesWritten = write(fd, buffer, strlen(buffer));

        if (bytesWritten == -1) {
            perror("write");
            close(fd);
            exit(EXIT_FAILURE);
        }

        if (strcmp(buffer, "exit\n") == 0) {
            printf("Exiting\n");
            break;
        }

        printf("Writing buffer to pipe...done\n");
    }

    // Close the named pipe
    close(fd);

    return 0;
}

