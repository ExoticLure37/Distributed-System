//Aryan Maurya
//20223054
//interchanging the case of the letters by communicates with child process via pipe

#include <stdio.h>
#include<string.h>
#include <sys/types.h>
#include <unistd.h>

#define BUFFER_SIZE 1024
 
int main()
{
   int fd1[2];
   int fd2[2];
   char buffer[BUFFER_SIZE];
   char message[BUFFER_SIZE];
     
   pid_t pid;
  
  //creating two pipes
   pipe(fd1);
   pipe(fd2);

   
   //Creating parent and child process
   pid=fork();

   //parent process
   if(pid>0){
     close(fd1[0]);
     //get the message from user
     printf("enter a message : ");
     scanf("%[^\n]s",message);

     //writing the message to the child
     write(fd1[1],message,strlen(message));
     close(fd1[1]);

     close(fd2[1]);
     //reading the modified message from the child
     read(fd2[0],message,BUFFER_SIZE);
     printf("%s\n",message);
     close(fd2[0]);
     
   }
   
   //child process
   else if(pid==0){
      close(fd1[1]);
      //read the message from parent
      read(fd1[0],buffer,BUFFER_SIZE);


      //changing the case of message
      int i=0;
      while(buffer[i]!='\0'){
        if(buffer[i]>=65&&buffer[i]<=91)
           buffer[i]=buffer[i]+32;
        else if(buffer[i]>=97 && buffer[i]<=123)
          buffer[i]=buffer[i]-32;

          i++;
      }
      close(fd1[0]);

      close(fd2[0]);
      //writing the modified message to the parent
      write(fd2[1],buffer,strlen(buffer));
      close(fd2[1]);
     
   }
    return 0;
}
