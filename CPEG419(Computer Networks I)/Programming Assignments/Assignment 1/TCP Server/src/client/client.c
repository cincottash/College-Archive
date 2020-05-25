#include <stdio.h> 
#include <sys/socket.h> 
#include <arpa/inet.h> 
#include <unistd.h> 
#include <string.h> 
#define PORT 8080 

/*
This file contains code needed to:
    Create a socket for the client
    Connect to the server
    Send messages to the server
    Receive message from the server
*/

int main(int argc, char const *argv[]){ 
    
    int sock = 0, valread; 
    
    //holds the socet and server address.
    struct sockaddr_in serv_addr; 
    
    //used to hold the file name the client sends to the server
    char *fileName;
    
    //holds data sent to the client by the server
    char clientBuffer[1024] = {0}; 
    
    //creating socket
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0){ 
        printf("\n Socket creation error \n"); 
        return -1; 
    } 
   
    serv_addr.sin_family = AF_INET; 
    serv_addr.sin_port = htons(PORT); 
       
    // Convert IPv4 and IPv6 addressesto binary form 
    if(inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr)<=0){ 
        printf("\nInvalid address\n"); 
        return -1; 
    } 
   
    /*

        int connect(int sockfd, const struct sockaddr *addr, socklen_t addrlen);

        The connect() system call connects the socket referred to by the file descriptor sockfd to the address specified by addr. 
        Server’s address and port is specified in addr.

    */
    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0){ 
        printf("\nConnection Failed \n"); 
        return -1; 
    } 
    
    printf("Enter the requested file name\n");
    scanf("%s", fileName);
    
    send(sock , fileName , strlen(fileName) , 0 ); 
    
    //printf("Message sent from client to server: %s\n", fileName); 
    
    valread = read( sock , clientBuffer, 1024); 
    //Contains the server's response to us regarding if file exists or not
    printf("Messged receieved from server: %s\n", clientBuffer); 

    //if the file exists, the server will send the contents to us, we then read the contents and print them to screen
    if(strncmp(clientBuffer, "File found", 9) == 0){

        valread = read( sock , clientBuffer, 1024); 
        
        //Contains the server's response to us
        printf("Messged receieved from server: %s\n", clientBuffer); 
        //notice that this line prints 1024, because we didnt use the whole clientBuffer but got it anyways
        printf("Size of message is %ld\n", sizeof(clientBuffer));
    }
    
    return 0; 
} 