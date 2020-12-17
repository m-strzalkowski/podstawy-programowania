#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#define PORT 50000


int main(int argc, char const *argv[])
{
    int sock = 0, valread;
    struct sockaddr_in serv_addr;
    char outbuffer[4096] = {0};
    char inbuffer[4096] = {0};
    scanf("%s", outbuffer);
    printf("wysylam %s...", outbuffer);

    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        printf("\n Blad tworzenia socketa \n");
        return -1;
    }

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);

    // Convert IPv4 and IPv6 addresses from text to binary form
    if(inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr)<=0)
    {
        printf("\nNiewlasciwy adres\n");
        return -1;
    }

    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
    {
        printf("\nConnection Failed \n");
        return -1;
    }
    send(sock , outbuffer , strlen(outbuffer) , 0 );
    printf("wyslano\n");
    valread = read( sock , inbuffer, 1024);
    printf("ODPOWIEDZ:\n%s",inbuffer );
    return 0;
}
