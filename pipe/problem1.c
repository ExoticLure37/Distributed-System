#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<string.h>
#include<stdlib.h>

int main(){
    //pipe 0->read 1->write

    int fd1[2];     //for process 1
    int fd2[2];     //for process 2

    char output_str[100];
    char fixed_str[]="Aryan-Maurya";

    pid_t p;

    if(pipe(fd1)==-1){
        printf("error in creation of pipe1 ");
        return 0;
    }
    
    if(pipe(fd2)==-1){
        printf("error in creation of pipe2 ");
        return 0;
    }

    p=fork();

    if(p<0){
        printf("fork failed.");
        return 0;
    }
    else if(p>0){       // process 1
        char input_str[100];  //buffer
        
        printf("enter the string: ");
        scanf("%s",input_str);

        close(fd1[0]);
        write(fd1[1],input_str,sizeof(input_str)+1);
        close(fd1[1]);

        wait(NULL);     //waiting for the child to finish

        close(fd2[1]);
        read(fd2[0],output_str,sizeof(output_str));
        close(fd2[0]);
        printf("updated string ... %s\n", output_str);

    }
    else{
        char tmp_str[100];
        
        close(fd1[1]);
        read(fd1[0],tmp_str,sizeof(tmp_str));
        close(fd1[0]);

        int k=strlen(tmp_str);
        tmp_str[k]=' ';
        k++;

        for(int i=0;i<strlen(fixed_str);i++){
            tmp_str[k++] = fixed_str[i];
        }

        tmp_str[k]='\0';

        close(fd2[0]);
        write(fd2[1],tmp_str,sizeof(tmp_str)+1);
        close(fd2[1]);
        
        exit(0);
    }
}
