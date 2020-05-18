#include <string.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <fcntl.h>
#define BUFFERSIZE 4096
#include <stdlib.h>

int main(int argc, char *argv[]){
	char *source_file = argv[1];
	char *dest_file = argv[2];
	char buffer[BUFFERSIZE];

	//mycat
	if (argc != 3){
		printf("Not enough arguments\n");
		exit(-1);
	}

	//does the source file exit?
	if((access(source_file, F_OK) !=0)){
		printf("Source file does not exist\n");
		exit(-1);
	}

	//does the dest file exit? If it does, do we want to overwrite it?
	if(access(dest_file, F_OK) == 0){
		printf("Do you want to overwrite file? yes/no\n");
		fgets(buffer, BUFFERSIZE, stdin);	//putting their input into buffer
		buffer[(int) strlen(buffer)-1] = '\0';	//strings end wit \0
		if(strcmp(buffer, "yes\0") !=0){
			return(0);
		}


	}
	
	//Can we open the source file to read its contents?
	int source_fd = open(source_file, O_RDONLY);
	if(source_fd < 0){
		printf("Error in opening source file\n");
		exit(-1);
	}

	struct stat state;
	if(stat(source_file, &state) < 0) {
		printf("Error with permissions");
		exit(-1);
	}


	char *file_contents = (char *) malloc(BUFFERSIZE *((int)sizeof(char))+1);

	mode_t permis = state.st_mode;
	int dest_fd = open(dest_file, O_WRONLY | O_CREAT, permis);	//open in write only, or create if dest doesn't exit
	int bytes_read;

	printf("Copying...\n");

	//write to the file while there are still bytes to read from the source
	while((bytes_read = read(source_fd, file_contents, BUFFERSIZE)) > 0){
		write(dest_fd, file_contents, bytes_read);

	}

	int source_file_close = close(source_fd);
	int dest_file_close = close(dest_fd);

	if(source_file_close != 0){
		printf("Error closing source file/n");
	}

	else{
	  printf("Source file closed successfully\n");
	}


	if(dest_file_close !=0){
		printf("Error closing destination file");
	}

	else{
	  printf("Destination file closed successfully\n");
	}

	free(file_contents);
}




