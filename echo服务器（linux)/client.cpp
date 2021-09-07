#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <string.h>
#include <ctype.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <iostream>

using namespace std;

const int SERVER_PORT = 666;
#define SERVER_IP  "192.168.1.19" 

int main(int argc, char *argv[] )
{
    int sockfd;
    char *message; 
    struct sockaddr_in servaddr;
    int n;
    char buf[64];

    if(argc !=2)
    {
        fputs("Usage: ./echo_client message \n",stderr);
	    exit(1);
    }
    
    message = argv[1];
    cout << "message: " << message << endl;

    //创建客户端socket
    sockfd = socket(AF_INET, SOCK_STREAM, 0);

    memset(&servaddr, '\0', sizeof(struct sockaddr_in));

    servaddr.sin_family = AF_INET;
    inet_pton(AF_INET, SERVER_IP, &servaddr.sin_addr);
    servaddr.sin_port = htons(SERVER_PORT);

    //建立连接
    connect(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr));

    write(sockfd, message, strlen(message));

    n = read(sockfd, buf, sizeof(buf)-1);

    if(n>0)
    {
        buf[n] = '\0';
	    cout << "receive: " << buf << endl;
    }
    else
    {
        perror("error!!!");
    } 
    cout << "finished." << endl;
	
    close(sockfd);
    return 0;
}
