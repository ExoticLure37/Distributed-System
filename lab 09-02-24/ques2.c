//ARYAN MAURYA
//20223054
//analysing the value of a pre-declared variable before and after the system call
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
// #include<sys/wait.h>

int main(){
	//declaring a variable x having initial value 1000
	int x = 1000;
	printf("\nvalue of x before system call: %d\n",x);	//printing the value before the system call
	printf("Parent process: x = %d, PID = %d\n", x, getpid());	//printing the parent process id
	pid_t pid = fork();		//caling fork()
	//if child process is not created
	if(pid<0){		
		printf("child process creation unsuccessfull\n");
		exit(EXIT_FAILURE);
	}
	//child process created successfully
	else if(pid==0){
		printf("child process created successfully\n");
		x++;		//altering the value of x 
		printf("value of x in child process : %d\n",x);
	}
	x++;		//altering the value of x after fork() call
	printf("value of x after system call: %d\n",x);
	return 0;
}