## List of relevant files
* Client.c
* Server.c
* test.txt

## Compilation instructions
* gcc server.c -o server
* gcc client.c -o client

## Running instructions
* Use ./server to start the server, then use ./client to start up the client.
* After the client has connected to the server, the client will ask for a file name.
* After providing a file name to the client, the file name will be sent to the server.
* The server will check if the file exists, if it doesn't exist, a message will be sent back to the client acknowledging that.
* If the file exists, the contents will be sent from the server to the client.
* A test file called "test.txt" containing the phrase "Hello world" is included.