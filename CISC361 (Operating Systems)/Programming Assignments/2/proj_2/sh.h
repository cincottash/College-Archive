
//#include "get_path.h"

int pid;
int sh( int argc, char **argv, char **envp);
char *which(char *command, struct pathelement *pathlist);
char *where(char *command, struct pathelement *pathlist);
void list ( char *dir );
void printenv(char **envp);
void sigint_handler(int sig_num);
void signal_stp_handler(int sig_num);
#define PROMPTMAX 32
#define MAXARGS 10

