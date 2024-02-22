//Aryan Maurya
//20223054

/*Implement  a  system  that  consists  of  two  processes;  parent  and  child, communicates  via  Named  pipe.  The  parent requests the  user  to  enter  a sentence,  then  it  will  write  this  sentence  into  the  pipe.  The  child  reads  this sentence,  count  the  number  of  vowel  letters  in  it,  print  the  sentence  on  the screen and the number of vowels letters in it.The output will be something like this
Parent process: Please enter a sentence: Welcome to OS lab 
Parent process: Write the sentence into the pipe.
Child process: Read Welcome to OS lab, number of vowels =6*/
#include <stdio.h>
#include<stdlib.h>
#include<string.h>
#include <sys/types.h>
#include<sys/wait.h>
#include <unistd.h>
#include<fcntl.h>
#include <sys/stat.h>

#define BUFFER_SIZE 1024
 
int main()
{
   
   int fd[2];
   char buffer[BUFFER_SIZE];
   char sentence[BUFFER_SIZE];
   // FIFO file path
   char *fifo = "fifo";
   pid_t pid;
  
    // Creating the named file(FIFO)
    // mkfifo(<pathname>, <permission>)
    
   mkfifo(fifo,0666);
   
  //Creating parrent and child process
   pid=fork();

   //parent process
   if(pid>0){
    // Open the named pipe for writing
     fd[1] = open(fifo, O_WRONLY);
     close(fd[0]);
     //get the sentence from user
     printf("Please enter a sentence : ");
     scanf("%[^\n]s",sentence);

     //writing the sentence to the child
     printf("Wrting the sentence into the pipe.\n");
     write(fd[1],sentence,strlen(sentence));
     close(fd[1]);

     wait(0);
    }

   else if(pid==0){
      
      // Open the named pipe for reading
      fd[0]=open(fifo,O_RDONLY);
      
      close(fd[1]);
      //read the sentence from parent
      read(fd[0],buffer,BUFFER_SIZE);

      //counting number of vowels in sentence
      int i=0,count=0;
      while(buffer[i]!='\0'){
           if(buffer[i]=='a'||buffer[i]=='e'||buffer[i]=='i'||buffer[i]=='o'||buffer[i]=='u'||buffer[i]=='A'||buffer[i]=='E'||buffer[i]=='I'||buffer[i]=='O'||buffer[i]=='U'){

            count++;
           }
        i++;
      }
      //printing the sentence and number of vowels
      printf("Read %s, number of vowels = %d\n",buffer,count);
      close(fd[0]);
      exit(0);
   }
  
  //remove the named pipe
     unlink(fifo);

    return 0;
}
