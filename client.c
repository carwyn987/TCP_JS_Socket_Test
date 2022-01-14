// Referencing https://www.geeksforgeeks.org/socket-programming-cc/
// Compile with "gcc client.c -o client"

// Client side C/C++ program to demonstrate Socket programming
#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#define PORT 59898
   
int main(int argc, char const *argv[])
{
    int sock = 0, valread;
    struct sockaddr_in serv_addr;
    // Buffer to store send msg in
    char *exitString = "exit";
    int sendBufLength = 100;
    char sendStr[sendBufLength];
    char* sendStrPtr = &sendStr[0];

    // Buffer to store response in
    char buffer[1024] = {0};
    
    // Attempt to create a socket, if successful, move on, else error.
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        printf("\n Socket creation error \n");
        return -1;
    }
   
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);
       
    // Convert IPv4 and IPv6 addresses from text to binary form
    if(inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr)<=0) 
    {
        printf("\nInvalid address/ Address not supported \n");
        return -1;
    }
   
    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
    {
        printf("\nConnection Failed \n");
        return -1;
    }

    while(1){
        // Wait for input to be sent
        printf("Enter a string to send to server :\n");
        // Reads the input from the standard input stream stdin and scans that input according to the format provided.
        scanf("%s", sendStr);

        // If exit is entered, return.
        if(strncmp(exitString, sendStr, 4) == 0){
            break;
        }

        send(sock, sendStr, sendBufLength, 0);
        printf("Message sent\n");
        // Gets the return value from the socket descriptor and places it into buffer
        valread = read(sock , buffer, 1024);
        printf("Response: \n%s\n",buffer);
    }

    return 0;
}