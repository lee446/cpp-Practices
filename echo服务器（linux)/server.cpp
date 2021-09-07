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

#define SERVER_PORT 666

int main()
{
    int sock,ret;
    struct sockaddr_in server_addr;

    //专用socket地址结构体
    memset(&server_addr, 0, sizeof(server_addr)); //清空
    server_addr.sin_family = AF_INET; //选择协议IPV4
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY); //监听本地所有IP地址 本机字节序转换成网络字节序
    server_addr.sin_port = htons(SERVER_PORT); //绑定端口号

    //创建socket
    sock = socket(AF_INET, SOCK_STREAM, 0);   //底层协议族选择IPv4 服务类型选择流服务 

    //命名socket
    ret = bind(sock, (const struct sockaddr *)&server_addr, sizeof(server_addr));

    //监听socket
    ret = listen(sock, 128);  //监听队列最长为128

    cout << "请等待客户端的连接：" << endl;

    while(true)
    {
        struct sockaddr_in client;
        int client_sock, len;
        char client_ip[64];
	    char buf[256];

        socklen_t client_addr_len;
        client_addr_len = sizeof(client);

        //接受连接
        client_sock =  accept(sock, (struct sockaddr *)&client, &client_addr_len);

        //读取数据
        len = read(client_sock, buf, sizeof(buf)-1);
        buf[len] = '\0';

        cout << "revive: " << buf << endl;

        //写入内容
        len = write(client_sock, buf, len);

        cout << "Finished!" << endl; 

        //关闭
        close(client_sock);

    }

    return 0;
}
