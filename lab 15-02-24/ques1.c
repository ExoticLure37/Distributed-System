//Aryan Maurya
//20223054
//calculating factorial by reading number through pipe call

#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
int factorial(int n){
if(n==1||n==0)
return 1;

else
return n*factorial(n-1);
}

int main()
{
   int fd[2];
   int num;
   pid_t pid;

  //creating pipe
   pipe(fd);

   //Creating parent and child process
   pid=fork();

    //parent process
    if(pid>0){
     close(fd[0]);
     printf("enter a positve number: ");
     scanf("%d",&num);
     write(fd[1],&num,sizeof(num));
     close(fd[1]);
   }
   
    //child process
     else if(pid==0){
      close(fd[1]);
      read(fd[0],&num,sizeof(num));
      printf("factorial of %d is %d\n",num,factorial(num));                 
      close(fd[0]);
   }

    return 0;
}
