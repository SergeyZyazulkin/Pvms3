#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char **argv) 
{
    int sock, bytes_count;
    struct sockaddr_in server;
    char buf[1024];
    FILE* out;

    if (argc != 3) {
        puts("Invalid count of parameters");
        return -1;
    }
     
    //Create socket
    sock = socket(AF_INET , SOCK_STREAM , 0);

    if (sock == -1) {
        puts("Error: could not create socket");
    }

    puts("Socket created");
     
    server.sin_addr.s_addr = inet_addr(argv[1]);
    server.sin_family = AF_INET;
    server.sin_port = htons(8888);
 
    //Connect to remote server
    if (connect(sock , (struct sockaddr *)&server , sizeof(server)) < 0) {
        puts("Error: connect failed");
        return -1;
    }
     
    puts("Connected");
     
    //Communicate with server
    if (send(sock, argv[2], sizeof(argv[2]) / sizeof(argv[2][0]), 0) < 0) {
        puts("Error: send failed");
    } else {
        out = fopen("Output", "w");

        if (out == NULL) {
            puts("Error: could not create output file");
        } else {
            while (bytes_count = recv(sock, buf, sizeof(buf)/sizeof(buf[0]), 0) > 0) {
                fwrite(buf, 1, strlen(buf), out);
            }

            fclose(out);    
        }
    }
     
    puts("Disconnected");
    close(sock);
    return 0;
}
