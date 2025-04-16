#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/wait.h>

int main(){
    
    int fd1[2],fd2[2];
    int pat1[2][2]={{2,4},{1,29}};
    int pat2[2][2]={{5,1},{5,4}};

    pid_t p;

    if(pipe(fd1)==-1 || pipe(fd2)==-1){
        printf("pipe creation failed ... ");
        return 0;
    }

    p=fork();

    if(p<0){
        printf("fork failed ... ");
        return 0;
    }
    else if(p>0){
        int res[2][2];

        close(fd1[0]);
        write(fd1[1],pat1,sizeof(pat1));
        write(fd1[1],pat2,sizeof(pat2));
        close(fd1[1]);

        wait(NULL);

        close(fd2[1]);
        read(fd2[0],res,sizeof(res));
        close(fd2[0]);

        for(int i=0;i<2;i++){
            for(int j=0;j<2;j++){
                printf("%d ",res[i][j]);
            }
            printf("\n");
        }
    }
    else{
        int res[2][2];

        int t1[2][2],t2[2][2];

        close(fd1[1]);
        read(fd1[0],t1,sizeof(t1));
        read(fd1[0],t2,sizeof(t2));
        close(fd1[0]);

        for(int i=0;i<2;i++){
            for(int j=0;j<2;j++){
                res[i][j]=t1[i][j]+t2[i][j];
            }
        }

        close(fd2[0]);
        write(fd2[1],res,sizeof(res));
        close(fd2[1]);

        exit(0);
    }
}