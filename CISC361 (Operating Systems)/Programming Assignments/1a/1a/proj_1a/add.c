#include "mp3.h"

extern node_t *head;
extern node_t *tail;

void insert(char *name, int num, char *title, int run_time, int date, char *artist)
{
  node_t *temp, *mp3;

  mp3 = (node_t *) malloc(sizeof(node_t));        // malloc space for MP3
  mp3->name = (char *) malloc(strlen(name) + 1);  // malloc space for name
  mp3->title = (char *)malloc(strlen(title)+ 1);  // malloc space for title 
  mp3->artist = (char *)malloc(strlen(artist)+1); //malloc space for artist
  strcpy(mp3->artist, artist);			  // "assign" artist via copy
  strcpy(mp3->name, name);                        // "assign" name via copy
  strcpy(mp3->title, title);			  // "assign" title via copy
  mp3-> date = date;
  mp3->run_time = run_time; 
  mp3->data = num;                                // assign data value
  mp3->next = NULL;
  if (head == NULL)
  {
    head = mp3;
    tail = mp3;               // add the first MP3
  }
  else
  {
    temp = head;
    while (temp->next != NULL)
      temp = temp->next;
    temp->next = mp3;
    tail = mp3;         // append to the tail/end
    mp3->prev = temp;
  }
}



