//Aryan Maurya
//20223054
/*QUESTION 4:-The Collatz conjecture concerns what happens when we take any positive integer n and apply the
following algorithm: n = n/2, if n is even n = 3 * n + 1, if n is odd. The conjecture states that when
this algorithm is continually applied, all positive integers will eventually reach 1. For example, if n
= 35, the sequence is 35, 106, 53, 160, 80, 40, 20, 10, 5, 16, 8, 4, 2, 1. Write a C program using the
fork() system call that generates this sequence in the child process. The starting number will be
provided from the command line. For example, if 8 is passed as a parameter on the Command line,
the child process will output 8, 4, 2, 1. Because the parent and child processes have their own copies
of the data, it will be necessary for the child to output the sequence. Have the parent invoke the
wait() call to wait for the child process to complete before exiting the program.
*/


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
void collatz(int n) {
    // Generate the Collatz sequence for a given starting integer n
    printf("%d ", n);
    if (n == 1) return;
    if (n % 2 == 0) {
        collatz(n/2);
    } 
    else {
        collatz(3*n + 1);
    }
}

int main(int argc, char *argv[]) {
    // Check if the correct number of arguments is provided
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <integer>\n", argv[0]);
        return 1;
    }
    // Convert the command line argument to an integer
    int n = atoi(argv[1]);
    // int n;
    // scanf("%d",&n);
    // Fork the process
    if (fork() == 0) {
    // Child process
        collatz(n);
        printf("\n");
        return 0;
    }
    // Parent process
    wait(NULL);
    return 0;
}
