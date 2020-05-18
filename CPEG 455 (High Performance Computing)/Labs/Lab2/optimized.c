#include <stdlib.h>
#include<string.h> 
#include<pthread.h> 
#include<stdlib.h> 
#include<unistd.h> 
#include <stdio.h>
#include <sys/time.h> 
int i; 

pthread_t tid;
int counter = 0; 
pthread_mutex_t lock1;  
pthread_mutex_t lock2;  
  
struct node *head;
struct node *tail;

struct node{
  int v;
  struct node *prev;
  struct node *next;
};

void add(int data){

  struct node *temp, *linkedList;

  linkedList = (struct node *) malloc(sizeof(struct node));        // malloc space for LL     
  linkedList->next = NULL;

  linkedList-> v = data;

  if (head == NULL){
    head = linkedList;
    tail = linkedList;       
  }

  else{

    temp = head;
    while (temp->next != NULL)
      temp = temp->next;
      temp->next = linkedList;
      tail = linkedList;         // append to the tail/end
      linkedList->prev = temp;
      //printf("%d", tail);
  
  }
}
void print (struct node *head) {
    struct node *current_node = head;
    while ( current_node != NULL) {
        printf("%d ", current_node->v);
        current_node = current_node->next;
    }
}

int size() {
    int cnt = 0;
    struct node *current_node = head;
    while ( current_node != NULL) {
        cnt++;
        current_node = current_node->next;
    }
  return(cnt);
}

//remove is a reserved word
int remove1(){ 
    if (head == NULL){
      return NULL;
    } 
  
    // Move the head pointer to the next node 
    struct node* temp = head; 
    head = head->next; 
  
    free(temp); 

    return head; 
} 

void freeList(){

  if (head == NULL){
      return NULL;
    } 

  while(head!= NULL){
    struct node* temp = head; 
    head = head->next;

    free(temp);
  }


}

/*
As long as the invocations of the methods from multiple threads change different locations
of the list, the multiple invocation should run concurrently, i.e., not waiting for each other.

For example, if one thread is adding a key to a list of 100 elements, and another thread is
removing a key, then the two threads should not block each other
*/
void workload(){
  
  counter++;
  

  printf("\n Job %d has started\n", counter); 

  for(int i=0; i<1000; i++){
    pthread_mutex_lock(&lock1);
    add(i *tid);
    pthread_mutex_unlock(&lock1);
  }


  for(int i=0; i<1000; i++){
    pthread_mutex_lock(&lock2);
    add(i);
    pthread_mutex_unlock(&lock2);
    
    remove1();
    
  }


  printf("%d\n", size());
  
  printf("\n Job %d has finished\n", counter); 
  //pthread_mutex_unlock(&lock1);
  
}

int main(int argc, char *argv[]){

  int iterations = 0;
  int max_iterations = 50;
  struct timeval t1, t2;
  double elapsedTime;
  double total_elapsedTime = 0;

  int i = 0;  
    while(iterations < max_iterations){
      if (pthread_mutex_init(&lock1, NULL) != 0) { 
        printf("\n mutex init has failed on lock1\n"); 
        return 1; 
      } 
      else if(pthread_mutex_init(&lock2, NULL) != 0){
        printf("\n mutex init has failed on lock2\n"); 
        return 1;
      }

    gettimeofday(&t1, NULL);
    // Let us create 8 threads 
    for (i = 0; i < 8; i++) {
        pthread_create(&tid, NULL, workload, NULL);
        pthread_join(tid, NULL);  
    }


    gettimeofday(&t2, NULL);

    // Calculating total time taken by the program in ms
    elapsedTime = (t2.tv_sec - t1.tv_sec) * 1000.0;      
    elapsedTime += (t2.tv_usec - t1.tv_usec) / 1000.0;
    total_elapsedTime +=elapsedTime;

    freeList();
    iterations++;
    

    }
    
    pthread_mutex_destroy(&lock1); 
    pthread_mutex_destroy(&lock2);
    printf("%f\n", total_elapsedTime/max_iterations);
    pthread_exit(NULL);
    
    
    return 0; 

}
