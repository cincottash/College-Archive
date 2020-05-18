#include "mp3.h"

extern node_t *head;
extern node_t *tail;

void print()
{
  node_t *temp;
  int  i = 0;

  temp = head;

  while (temp != NULL) {
    printf("(%d)--%s--%d--%s--%d--%d--%s\n", ++i, temp->name, temp->data, temp->title, temp->run_time, temp->date, temp->artist);
    temp = temp->next;
  }
}

void print2()
{
  node_t *temp;
  int  i = 0;

  temp = tail;

  while (temp != NULL) {
    printf("(%d)--%s--%d--%s--%d--%d--%s\n", ++i, temp->name, temp->data, temp->title, temp->run_time, temp->date, temp->artist);
    temp = temp->prev;
  }
}
//
