
//
// adapted from http://www.cprogramming.com/snippets/source-code/singly-linked-list-insert-remove-add-count


#include "mp3.h"
#define  BUFFERSIZE 128

node_t *head;
node_t *tail;

void insert(char *name, int data, char *title, int run_time, int date, char *artist);
void print();
void print2();
void freeNode();
void freeList();
void remove_artist2();
int main()
{
  char title[BUFFERSIZE];
  char artist[BUFFERSIZE];
  int i, date, run_time, num, len;
  struct node *n;
  char buffer[BUFFERSIZE], c;

  head = NULL;

  while (1) {
    printf("\nList Operations\n");
    printf("===============\n");
    printf("(1) Insert\n");
    printf("(2) Display Frowards\n");
    printf("(3) Display Backwards\n");
    printf("(4) Delete\n");
    printf("(5) Exit\n");
    printf("Enter your choice : ");
    if (scanf("%d%c", &i, &c) <= 0) {          // use c to capture \n
        printf("Enter only an integer...\n");
        exit(0);
    } else {
        switch(i)
        {
        case 1: printf("Enter the name to insert : ");
		if (fgets(buffer, BUFFERSIZE , stdin) != NULL) {
                  len = strlen(buffer);
                  buffer[len - 1] = '\0';   // override \n to become \0
                } else {
                    printf("wrong name...");
                    exit(-1);
                  }
                printf("Enter the number to insert : ");
                scanf("%d%c", &num, &c);  // use c to capture \n

		printf("Enter the title to insert : ");
		scanf("%s%c",title, &c);                

		printf("Enter the runtime to insert : ");		
		scanf("%d%c", &run_time, &c);

		printf("Enter an integer date to insert (mm/dd/yyy) : ");
		scanf("%d%c", &date, &c);
		
		printf("Enter an artist to insert : ");
		scanf ("%s%c", artist, &c);

		printf("[%s] [%d] [%s] [%d] [%d] [%s]\n", buffer, num, title, run_time, date, artist);
                insert(buffer, num, title, run_time, date, artist);
                break;
        case 2: if (head == NULL)
                  printf("List is Empty\n");
                else
                  print();
                break;
        
	case 3: if (head == NULL)
		  printf("List is Empty\n");
		else
		  print2();
		break;
        case 4: 
		remove_artist2();
		break;
	case 5: freeList();
                return 0;
        default: printf("Invalid option\n");
        }
    }
  }
  return 0;
}

void remove_artist2(){
	char artist_del[BUFFERSIZE];
	char c[BUFFERSIZE];
	printf("Enter an artist to delete : ");
	scanf("%s%c", artist_del, c);
	
	node_t *temp;
	int i = 0;
	temp = head;
	while(temp != NULL){
		if(strcmp(temp->artist, artist_del) == 0){
			//mp3 is only item in list
			if(temp->prev == NULL && temp->next == NULL){	
				
				temp=head;
				head=head->next;
				printf("freeing mp3");
				free(temp->name);
				free(temp->artist);
				free(temp->title);
				free(temp);
			}//if
		
			//mp3 is the first item in list 
			else if(temp->prev == NULL && temp->next != NULL){
				temp = head;
				head = head->next;
				head->prev = NULL;
				
				printf("freeing mp3");
				free(temp->name);
				free(temp->artist);
				free(temp->title);
				free(temp);
			}//else if 1

			//mp3 is in middle of list
			else if(temp->prev != NULL && temp->next != NULL){
				
				temp->prev->next=temp->next;
				temp->next->prev=temp->prev;
				
				printf("freeing mp3");
				free(temp->name);
				free(temp->artist);
				free(temp->title);
				free(temp);
			}//else if 2
			
			//mp3 is last item in list
			else if(temp->next == NULL && temp->prev != NULL){

				tail=temp->prev;
				temp->prev->next = NULL;
				
				printf("freeing mp3");
				free(temp->name);
				free(temp->artist);
				free(temp->title);
				free(temp);
			}//else if 3

		}//if
	temp=temp->next;
	}//while		
	return;
	
}//remove_artist2


