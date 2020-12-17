#include <unistd.h>
#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#define PORT 50000
int main(int argc, char const *argv[])
{
    int server_fd, client_socket, numbytesread;
    struct sockaddr_in address;
    int addrlen = sizeof(address);
    char buffer[1024] = {0};
    char odpowiedz[1024];
    int numer=0;

    // deskryptor
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0)
    {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    //
    int opt = 1;
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt)))
    {
        perror("blad na :setsockopt");
        exit(EXIT_FAILURE);
    }
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons( PORT );

    //zaczepianie socketa na porcie
    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address))<0)
    {
        perror("blad na : bind");
        exit(EXIT_FAILURE);
    }
    if (listen(server_fd, 3) < 0)
    {
        perror("blad na : listen");
        exit(EXIT_FAILURE);
    }
    while(1)
    {
        if ((client_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen))<0)
        {
            perror("blad na : accept");
            exit(EXIT_FAILURE);
        }
        numer++;
        buffer[0]=0;
        numbytesread = read( client_socket , buffer, 1024);
        printf("READ:%s\t len:%d\n",buffer, strlen(buffer));

        sprintf(odpowiedz, "Jestem najglupszym serwerem na swiecie, wiec powiem ci tylko ze wyslales mi %zu znakow.", strlen(buffer));
        send(client_socket , odpowiedz , strlen(odpowiedz) , 0 );
        printf("Wyslano '%s'\n", odpowiedz);
        shutdown( client_socket, SHUT_RDWR );

    }

    return 0;
}


