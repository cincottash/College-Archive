#include <pthread.h>
#include <utmpx.h>
#include <stdio.h>
#include <string.h>
#include <strings.h>
#include <limits.h>
#include <unistd.h>
#include <stdlib.h>
#include <pwd.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
#include "sh.h"
#include <glob.h>
#include <sys/time.h>
#include "dll.h"

struct Node* head;
struct Node* tail;


void push(char* newName,char* newTty ) // Adds another node infront of the DLL
{ 
	printf("\n\npoint4 push user & tty\n\n");
    /* 1. allocate node */
    struct Node* new_node = (struct Node*)malloc(sizeof(struct Node)); 
	struct Node* temp;
	printf("\n Adding User Name: %s , TTY: %s \n",newName,newTty);
	
    /* 2. put in the data  */
	
	new_node->userName = malloc(strlen(newName)+1);
	
	new_node->tty = malloc(strlen(newTty)+1);
	
	strcpy(new_node->userName, newName);  
	strcpy(new_node->tty, newTty);
	
	printf("\n Added User Name: %s , TTY: %s \n",new_node->userName,new_node->tty);
	

	if(head == NULL && tail == NULL){ // first node case
		head = new_node;
	} else if (head != NULL && tail == NULL) { // second node case
		tail = new_node;
		tail->next = NULL;
		tail->prev = head;
		head->next = tail;
		head->prev = NULL;
	} else { // later nodes case
		new_node->next = head;
		new_node->prev = NULL;
		head->prev = new_node;
		head = new_node;
	}
	printf("\n\n Added Name: %s , TTY: %s \n\n",new_node->userName,new_node->tty);
	
	displayForward();
	
	/*return;
    /* 3. Make next of new node as head and previous as NULL 
    new_node->next = head; //(*head_ref); 
    new_node->prev = NULL; 
  
    /* 4. change prev of head node to new node 
    if (head != NULL){ // ((*head_ref) != NULL) 
        head->prev = new_node; 
	}
    /* 5. move the head to point to the new node 
    head = new_node; 
	printf("\n\npoint5\n\n");*/
}

void displayForward() { // prints DLL

   //start from the beginning
	struct Node *ptr = head;
	//struct Node *ptr = tail;
   //navigate till the end of the list
   //printf("\n[ ");
	while(ptr != NULL) {        
		printf("\nDLL -- list: User :%s , TTY: %s \n",ptr->userName,ptr->tty);
		ptr = ptr->next;
	}
}


void delet(char *artist_n){ // Delets user from watch list
	struct Node *temp;
	temp = head;
	while (temp != NULL) {
		if(strcmp(temp->userName,artist_n)==0) {
			if((temp->prev != NULL)&&(temp->next != NULL)){
				temp->prev->next = temp->next;
				temp->next->prev = temp->prev;
			} else if((temp->prev == NULL)&&(temp->next != NULL)){
				head = temp->next;
				temp->next->prev = NULL;
			} else if((temp->prev != NULL)&&(temp->next == NULL)){
				tail = temp->prev;
				temp->prev->next = NULL;
			} else{
				head = NULL;
				tail = NULL;
			}
			free(temp->userName);  // first free name inside user record
			free(temp->tty); // free user tty
			free(temp);        // then free user record
		}
		temp = temp->next;
	}
}

void addUser(char *name){ // Adds user to watch list
	//printf("These are all the users currently logged in ... \n");
	printf("\n\npoint3 adduser\n\n");
	struct utmpx *up;
	setutxent();			// start at beginning  setutxent
	while (up = getutxent()) {	/* get an entry */
		if ( up->ut_type == USER_PROCESS ) {	/* only care about users */
			//printf("%s has logged on %s from %s\n", up->ut_user, up->ut_line, up ->ut_host);
			if(strcmp(name,up->ut_user) == 0){ // check if this tty is of same user 
				push(name,up->ut_line);
			}
		}
	}
}


void delet2(char *artist_n,char *oldTty){ // get rid of specific user tty
	printf("\n\n\n\nwarning delete2 has been ran!!!\n\n\n");
	struct Node *temp;
	temp = head;
	while (temp != NULL) {
		if(strcmp(temp->userName,artist_n)==0 && strcmp(temp->tty,oldTty)==0) {
			if((temp->prev != NULL)&&(temp->next != NULL)){
				temp->prev->next = temp->next;
				temp->next->prev = temp->prev;
			}
			else if((temp->prev == NULL)&&(temp->next != NULL)){
				head = temp->next;
				temp->next->prev = NULL;
			} else if((temp->prev != NULL)&&(temp->next == NULL)){
				tail = temp->prev;
				temp->prev->next = NULL;
			} else{
				head = NULL;
				tail = NULL;
			}
			free(temp->userName);  // first free name inside MP3 record
			free(temp->tty);
			free(temp);        // then free MP3 record
			return;
		}
		temp = temp->next;
	}
}



int findTty(char* TTY){ // This finction will find if there is any instance of a tty in the DLL
	struct Node* temp = head;
	while(temp != NULL){
		if(strcmp(temp->tty,TTY) == 0){ // Checking the TTY
			return 1;
		}
		temp = temp->next;
	}
	return -1;
}




