#include <stdio.h>
#include <stdlib.h>
#include <string.h>
 
typedef struct node
{
  char *name;    
  char *artist;
  char *title;
  int date;
  int data;
  int run_time;
  struct node *prev;
  struct node *next;
} node_t; 
