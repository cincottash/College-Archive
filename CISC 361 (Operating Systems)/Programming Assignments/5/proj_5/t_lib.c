//Created by Shane Cincotta and Madison Adams

#include "t_lib.h"
#include <signal.h>
#include <unistd.h>
#include <memory.h>
//#include "ud_thread.h"


tcb *running;
readyQueue *ready;

void push(readyQueue *queueHead, tcb *node){
	node->next = NULL;
	tcb *currentNode = queueHead->first;

	if(currentNode == NULL){
		queueHead->first = node;
	}
	else{
	  if(node->thread_priority < queueHead->first->thread_priority){
	  	node->next = queueHead->first;
		queueHead->first = node;
	  }//if
	  else{
		while(NULL != currentNode->next && currentNode->next->thread_priority < node->thread_priority){
			currentNode = currentNode->next;
		}//while
		currentNode->next = node;

	  }//else

	}


}


tcb *pop(readyQueue *queueHead) {
    tcb *temp = NULL;
    if (queueHead != NULL) {
        temp = queueHead->first;
        queueHead->first = queueHead->first->next;
        temp->next = NULL;
    }
    if (temp != NULL) {
        temp->next = NULL;
    }
    return temp;
}

void t_yield() {
    tcb *next = pop(ready);
    tcb *current = running;
    next->next = NULL;
    current->next = NULL;

    push(ready, current); //calling thread is placed at the end of the ready queue
    running = next;

    swapcontext(current->thread_context, next->thread_context);  //first thread in the ready queue resumes execution
}

void sig_func(int sig_no) {
    t_yield();
}

void t_init()
{
  printf("t_init running\n");
  tcb *temp_block;  //creating tcb of main thread
  temp_block = malloc(sizeof(tcb));
  temp_block->thread_id = 0;
  temp_block->thread_priority = 1;
  temp_block->thread_context = (ucontext_t *) malloc(sizeof(ucontext_t));
  temp_block->next = NULL;

  getcontext(temp_block->thread_context);

  running = temp_block;  //adding main thread to running queue

  ready = (readyQueue *) calloc(1, sizeof(readyQueue));  //initializing ready queue 
  ready->first = NULL;  
  //printf("%s\n", ready->first);
}

void init_alarm() {
    //signal(SIGALRM, sig_func);
    ualarm(10000, 0); // alarm in 1 microsecond
}


//shutting down the thread library while also freeing all dynamically allocated memory
void t_shutdown(){
	printf("Shutting down\n");
	tcb *current = ready->first;
	while(NULL != current->next){
		tcb *temp_block = current;
		current = current->next;
		free(temp_block->thread_context);
		free(temp_block);
	}

	free(current->thread_context);
	free(ready);
	free(running);
}

void t_create(void (*fct)(int), int id, int pri) {
    size_t sz = 0x10000;

    //mallocing space for our new thread control block(newThreadCB)
    tcb *newThreadCB = malloc(sizeof(tcb));
    newThreadCB->thread_context = (ucontext_t *) malloc(sizeof(ucontext_t));

    getcontext(newThreadCB->thread_context);
/***
  uc->uc_stack.ss_sp = mmap(0, sz,
       PROT_READ | PROT_WRITE | PROT_EXEC,
       MAP_PRIVATE | MAP_ANON, -1, 0);
***/
    newThreadCB->thread_context->uc_stack.ss_sp = malloc(sz);
    newThreadCB->thread_context->uc_stack.ss_size = sz;
    newThreadCB->thread_context->uc_stack.ss_flags = 0;
    makecontext(newThreadCB->thread_context, (void (*)(void)) fct, 1, id);

    newThreadCB->thread_id = id;
    newThreadCB->thread_priority = pri; //create with priority "pri"
    newThreadCB->thread_context = newThreadCB->thread_context;
    newThreadCB->next = NULL;
    push(ready, newThreadCB);  //tcb of created thread is added to the end of the ready queue
}


void t_terminate() {
    tcb *temp = running;

    //free it's dynamically allocated memory
    free(temp->thread_context->uc_stack.ss_sp);
    free(temp->thread_context);
    free(temp);

    running = pop(ready); //remove from ready queue

    if (NULL != running) {
        setcontext(running->thread_context);  //resume execution of the head thread on the ready queue
    }
}


int sem_init(sem_t **sp, int sem_count){

  sem_t *tmp = (sem_t *) malloc(sizeof(sem_t));
  tmp->count = sem_count;
  tmp->q = NULL;
  sp = &tmp;
  return 1;
}

void sem_wait(sem_t *s)
{
	sighold();
	tcb *tmp = running;
	s->count--;
	
	if(s->count < 0){
		push(s->q, tmp);


	tcb *temp = pop(ready);
	free(temp);

	swapcontext(temp->thread_context, running->thread_context);
	sigrelse();
	return;
	}

	else if(s->count >=0){
		sigrelse();
		return;
	}

}

void sem_signal(sem_t *s){
  sighold();
  s->count++;

  if(s->count <= 0){
    tcb *Thread = pop(s->q);
    push(ready, Thread);
    free(Thread);
    sigrelse();
    return;
  }

}

void sem_destroy(sem_t **sp) {

  sem_t *tmp = *sp;
  tcb *next;

  while(tmp->q != NULL) {
    next = tmp->q->next;
    //free(tmp->q->thread_context.uc_stack.ss_sp);
    free(tmp->q->thread_context);
    free(tmp);
    tmp = next;
  }
  free(tmp);

}

int mbox_create(mbox **mb) {
    mbox *mailbox = malloc(sizeof(mb));
    mailbox->msg = malloc(sizeof(messageNode));
    mailbox->mbox_sem = malloc(sizeof(sem_t));

    *mb = mailbox;
    return 0;
}

void mbox_destroy(mbox **mb) {
    free((*mb)->msg);
    free((*mb)->mbox_sem);
    free(mb);
}


void mbox_deposit(mbox *mb, char *msg, int len) {
    printf("Sending message\n");
    // Make the message
    messageNode *messageNodeHead = malloc(sizeof(messageNode));
    messageNodeHead->len = len;
    messageNodeHead->message = msg;

    // Append to mailbox
    messageNode *headNode = mb->msg;
    if (NULL == headNode) {
        //printf("Head null\n");
        mb->msg = messageNodeHead;
        headNode = messageNodeHead;
    } else {
        //printf("Looping");
        while (NULL != headNode->next) {
            headNode = headNode->next;
        }
        headNode->next = messageNodeHead;
    }
    printf("Deposited");
    t_yield();
}


void mbox_withdraw(mbox *mb, char *msg, int *len) {
    printf("Withdrawing message\n");
    messageNode *messageNodeHead = mb->msg;

    char *message = "";
    *len = 0;

    if (NULL != messageNodeHead) {
        // printf("Head not null\n");
        *len = messageNodeHead->len;
        message = messageNodeHead->message;
        mb->msg = mb->msg->next;
    }

    strcpy(msg, message);
    t_yield();
}


void mbox_withdraw_2(mbox *mb, int *tid, char *msg, int *len) {
    printf("Withdrawing message\n");
    messageNode *messageNodeHead = mb->msg;

    char *message = "";
    *len = 0;

    if (NULL != messageNodeHead) {
        while (NULL != messageNodeHead->next) {
            if (messageNodeHead->sender == *tid) {
                *len = messageNodeHead->len;
                message = messageNodeHead->message;
            }
            mb->msg = mb->msg->next;
        }
    }

    strcpy(msg, message);
    t_yield();
}


void receive(int *tid, char *msg, int *len) {
    mbox *recipient = running->mailbox;
    if (tid == 0) {
        mbox_withdraw(recipient, msg, len);
    } else {
        mbox_withdraw_2(recipient, tid, msg, len);
    }
}

mbox *fetchMailbox(int tid) {
    if (running->thread_id == tid) {
        return running->mailbox;
    } else {
        tcb *currentNode;
        if (NULL != ready) {
            currentNode = ready->first;

            while (NULL != currentNode) {
                if (currentNode->thread_id == tid) {
                    return currentNode->mailbox;
                }
                currentNode = currentNode->next;
            }

        }
    }
    return NULL;
}

void send(int tid, char *msg, int len) {
    mbox *destination = fetchMailbox(tid);
    mbox_deposit(destination, msg, len);
}

