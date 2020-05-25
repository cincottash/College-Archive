#include <stdio.h>
#include <stdlib.h>
#include <ucontext.h>
#include <sys/mman.h>

//Our thread control block
struct tcb {
  int         thread_id;
  int         thread_priority;
  ucontext_t  *thread_context;
  struct tcb *next;
  struct mbox *mailbox;
};

typedef struct tcb tcb;


struct readyQueue {
	tcb *first;
};

typedef struct readyQueue readyQueue;

struct sem_t {
    int count;
    tcb *q;
};
typedef struct sem_t sem_t;


struct messageNode {
    char *message;     // copy of the message
    int len;          // length of the message
    int sender;       // TID of sender thread
    int receiver;     // TID of receiver thread
    struct messageNode *next; // pointer to next node
};
typedef struct messageNode messageNode;

struct mbox {
    struct messageNode *msg;       // message queue
    sem_t *mbox_sem;
};
typedef struct mbox mbox;