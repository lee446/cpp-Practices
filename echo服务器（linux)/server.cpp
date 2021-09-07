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

    //ר��socket��ַ�ṹ��
    memset(&server_addr, 0, sizeof(server_addr)); //���
    server_addr.sin_family = AF_INET; //ѡ��Э��IPV4
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY); //������������IP��ַ �����ֽ���ת���������ֽ���
    server_addr.sin_port = htons(SERVER_PORT); //�󶨶˿ں�

    //����socket
    sock = socket(AF_INET, SOCK_STREAM, 0);   //�ײ�Э����ѡ��IPv4 ��������ѡ�������� 

    //����socket
    ret = bind(sock, (const struct sockaddr *)&server_addr, sizeof(server_addr));

    //����socket
    ret = listen(sock, 128);  //���������Ϊ128

    cout << "��ȴ��ͻ��˵����ӣ�" << endl;

    while(true)
    {
        struct sockaddr_in client;
        int client_sock, len;
        char client_ip[64];
	    char buf[256];

        socklen_t client_addr_len;
        client_addr_len = sizeof(client);

        //��������
        client_sock =  accept(sock, (struct sockaddr *)&client, &client_addr_len);

        //��ȡ����
        len = read(client_sock, buf, sizeof(buf)-1);
        buf[len] = '\0';

        cout << "revive: " << buf << endl;

        //д������
        len = write(client_sock, buf, len);

        cout << "Finished!" << endl; 

        //�ر�
        close(client_sock);

    }

    return 0;
}
