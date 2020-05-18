
# choose your compiler
CC=gcc
#CC=gcc -Wall

mysh: sh.o get_path.o main.c dll.o
	$(CC) -g main.c sh.o get_path.o dll.o -o mysh -lpthread
#	$(CC) -g main.c sh.o get_path.o bash_getcwd.o -o mysh

dll.o: sh.c sh.h main.c get_path.h get_path.c dll.h dll.c
	$(CC) -g -c dll.c

sh.o: sh.c sh.h
	$(CC) -g -c sh.c

get_path.o: get_path.c get_path.h
	$(CC) -g -c get_path.c

clean:
	rm -rf sh.o get_path.o mysh
