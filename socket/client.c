#include<stdlib.h>
#include<stdio.h>
#include<unistd.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<string.h>

#define PORT 5000

int main(){
    int sock;
    struct sockaddr_in serveraddr;
    // socklen_t addrlen=sizeof(clientaddr);

    char buffer[1024],result[1024];

    sock=socket(AF_INET,SOCK_STREAM,0);

    serveraddr.sin_family=AF_INET;
    serveraddr.sin_addr.s_addr=INADDR_ANY;
    serveraddr.sin_port=PORT;

    connect(sock,(struct sockaddr*)&serveraddr,sizeof(serveraddr));
    // listen(server_fd,5);

    printf("client listening on the port: %d\n",PORT);

    // client_fd=accept(server_fd,(struct sockaddr*)&clientaddr,&addrlen);
    printf("enter a number : ");
    int nn;
    scanf("%d",&nn);

    sprintf(buffer,"%d",nn);

    send(sock,buffer,sizeof(buffer),0);

    read(sock,result,sizeof(result));
    // result[res]='\0';

    printf("received output from server: %s\n",result);

    close(sock);
    // close(server_fd);

    return 0;
}