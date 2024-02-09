//Aryan Maurya
//20223054
//Write a program in C that creates a child process, waits for the termination of the child and lists
//process ID (PID), together with the state in which the process was terminated (in decimal and
//hexadecimal).

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>

int main(){
	pid_t pid ;		//datatype to store the process id
	pid = fork();	//calling the fork system call
	int child_status;	//declaring a var for storing child status
	//pid == -1	
	if(pid<0){		
		printf("child process creation unsuccessfull\n");
		exit(EXIT_FAILURE);
	}
	//child process created successfully
	else if(pid==0){
		printf("child process created successfully\n");
		exit(EXIT_SUCCESS);
	}
	
	else {
		printf("Parent process started, PID: %d\n", getpid());
		printf("Child process started, PID: %d\n", pid);
		printf("Waiting for child process to terminate...\n");
		wait(&child_status);	//calling wait() for the child process
		printf("Child process terminated, PID: %d, \nstatus:-\n\tdecimal: %d \n\thexadecimal: x(%#x)\n", pid, WEXITSTATUS(child_status), 															WEXITSTATUS(child_status));
	}
	return 0;
}
