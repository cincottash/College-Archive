#include "ud_thread.h"
#include <stdio.h>

sem_t *s;

void assign(int pri)
{
  int i;

  for (i = 0; i < 3; i++)
    printf("in assign(1): %d\n", i);

  t_yield();

  for (i = 10; i < 13; i++)
    printf("in assign(2): %d\n", i);

  t_yield();

  for (i = 20; i < 23; i++)
    printf("in assign(3): %d\n", i);
}

int main(int argc, char **argv)
{
  //printf("Main\n");
  t_init();
  sem_init(&s, 5);

  sem_wait(s);
  sem_signal(s);

  t_create(assign, 1, 1);

  printf("in main(): 0\n");

  t_yield();

  printf("in main(): 1\n");
  t_yield();

  printf("in main(): 2\n");
  t_yield();

  printf("done...\n");

  sem_destroy(&s);

  return (0);
}

/* --- output -----
in main(): 0
in assign(1): 0
in assign(1): 1
in assign(1): 2
in main(): 1
in assign(2): 10
in assign(2): 11
in assign(2): 12
in main(): 2
in assign(3): 20
in assign(3): 21
in assign(3): 22
done...
*/
