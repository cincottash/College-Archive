#include <unistd.h> 
#include <stdio.h> 
#include <sys/socket.h> 
#include <stdlib.h> 
#include <netinet/in.h> 
#include <string.h> 
#define PORT 8080 
/*
This file contains code needed to:
    Create a socket for the server
    Bind a socket to an address
    Listen for an incoming connection
    Accept an incoming connection
    Read filename message from client
    Check if filename exists on server
    If file exists, send conent to client
    Else tell client the file doesn't exist.
*/

int main(int argc, char const *argv[]){ 
    int server_fd, new_socket, valread; 
    
    //holds the socet and server address.
    struct sockaddr_in address; 
    
    int opt = 1; 
    int addrlen = sizeof(address); 
    
    //contains the message sent to server by the client
    char clientMessageBuffer[1024] = {0}; 
    
    //used to store the response of the server when the client requests a filename.
    char *serverResponse; 
    
    //used to hold the conents of the file if it exists
    char *serverBuffer;
    
    //the file that the client is requesting.
    FILE * fp;

    //the number of bytes of fp
    long numbytes;

       
    /*

        int server_fd = socket(domain, type, protocol)

        server_fd: socket descriptor, an integer (like a file-handle)
        domain: integer, communication domain e.g., AF_INET (IPv4 protocol) , AF_INET6 (IPv6 protocol)
        type: communication type- SOCK_STREAM: TCP(reliable, connection oriented)
        protocol: Protocol value for Internet Protocol(IP), which is 0. 

    */
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0){ 
        perror("socket failed"); 
        exit(EXIT_FAILURE); 
    } 
       
    /*
        int setsockopt(int sockfd, int level, int optname, const void *optval, socklen_t optlen);

        helps in reuse of address and port. Prevents error such as: “address already in use”.

    */
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))){ 
        perror("setsockopt"); 
        exit(EXIT_FAILURE); 
    } 

    address.sin_family = AF_INET; 
    address.sin_addr.s_addr = INADDR_ANY; 
    address.sin_port = htons( PORT ); 
       
    /*
    
        int bind(int sockfd, const struct sockaddr *addr, socklen_t addrlen);
        
        bind function binds the socket to the address and port number specified in addr

    */
    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address))<0){ 
        perror("bind failed"); 
        exit(EXIT_FAILURE); 
    } 

    /*
        int listen(int sockfd, int backlog);

        It puts the server socket in a passive mode, where it waits for the client to approach the server to make a connection.

        The backlog, defines the maximum length to which the queue of pending connections for sockfd may grow
        
    */
    if (listen(server_fd, 3) < 0){ 
        perror("listen"); 
        exit(EXIT_FAILURE); 
    } 
    
    /*
        int new_socket= accept(int sockfd, struct sockaddr *addr, socklen_t *addrlen);

        It extracts the first connection request on the queue of pending connections for the listening socket, sockfd, 
        creates a new connected socket, and returns a new file descriptor referring to that socket

         At this point, connection is established between client and server
    */
    if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen))<0){ 
        perror("accept"); 
        exit(EXIT_FAILURE); 
    } 

    valread = read( new_socket , clientMessageBuffer, 1024); 
    //clientMessageBuffer contains the message sent to server by the client
    printf("File name received from client: %s\n", clientMessageBuffer ); 

    //Check if file exists
    if( access( clientMessageBuffer, F_OK ) != -1 ) {// file exists
        serverResponse = "File found\n";
        send(new_socket , serverResponse , strlen(serverResponse) , 0 ); 

        fp = fopen(clientMessageBuffer, "r");

        //Get the number of bytes from start of file
        fseek(fp, 0L, SEEK_END);
        numbytes = ftell(fp);


        /* reset the file position indicator to 
        the beginning of the file */
        fseek(fp, 0L, SEEK_SET);
        //send(new_socket , serverResponse , strlen(serverResponse) , 0 ); 

        /* grab sufficient memory for the 
        serverBuffer to hold the file information to send*/
        serverBuffer = (char*)calloc(numbytes, sizeof(char)); 

        /* copy all the text into the buffer */
        fread(serverBuffer, sizeof(char), numbytes, fp);

        fclose(fp);

        send(new_socket , serverBuffer , strlen(serverResponse) , 0 );

        printf("Sent %ld bytes of data to client", numbytes);

        free(serverBuffer);
    } 
    else{
        // file doesn't exist
        serverResponse = "Error, file not found\n";
        send(new_socket , serverResponse , strlen(serverResponse) , 0 ); 
    }

    return 0; 
} 