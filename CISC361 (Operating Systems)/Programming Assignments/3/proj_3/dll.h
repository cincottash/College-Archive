#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Node { 
    char* userName; // Name of tracked user
	char* tty;
    struct Node* next; // Pointer to next node in DLL 
    struct Node* prev; // Pointer to previous node in DLL 
};

void delet(char* artist_n); // delete user

void displayForward();

void push(char* newName, char* newTty );

void addUser(char *name);

void delet2(char *artist_n,char *oldTty); // delete tty

int findTty(char* TTY);

//void *firstRun(void *vargp);
