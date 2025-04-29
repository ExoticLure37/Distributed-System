#include<stdlib.h>
#include<stdio.h>
#include<unistd.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<string.h>

#define PORT 5000

int main(){
    int server_fd,client_fd;
    struct sockaddr_in serveraddr,clientaddr;
    socklen_t addrlen=sizeof(clientaddr);

    char buffer[1024],result[1024];

    server_fd=socket(AF_INET,SOCK_STREAM,0);

    serveraddr.sin_family=AF_INET;
    serveraddr.sin_addr.s_addr=INADDR_ANY;
    serveraddr.sin_port=PORT;

    bind(server_fd,(struct sockaddr*)&serveraddr,sizeof(serveraddr));
    listen(server_fd,5);

    printf("server listening on the port: %d\n",PORT);

    client_fd=accept(server_fd,(struct sockaddr*)&clientaddr,&addrlen);

    int nn=recv(client_fd,buffer,sizeof(buffer),0);
    buffer[nn]='\0';

    int number = atoi(buffer);

    printf("client connected..\n");
    printf("Number recieved: %d\n",number);

    int i=number,product=1;
    for(i=number;i>=2;i--){
        product=product*i;
    }

    sprintf(result,"%d",product);

    send(client_fd,result,sizeof(result),0);

    close(client_fd);
    close(server_fd);

    return 0;
}