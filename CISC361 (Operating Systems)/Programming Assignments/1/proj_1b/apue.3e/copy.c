#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>

void
main(int argc, char *argv[])
{
  struct stat   buf;

   umask(0);   // UMASK

  printf("copy: %s %s ", argv[1], argv[2]);
  if (stat(argv[1], &buf) < 0) {
    perror("stat error");
  }
  printf("source mode [%o]\n", buf.st_mode);
  open(argv[2], O_WRONLY | O_CREAT | O_TRUNC, buf.st_mode);
}
