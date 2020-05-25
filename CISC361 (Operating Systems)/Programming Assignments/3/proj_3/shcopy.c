#include <stdio.h>
#include <string.h>
#include <strings.h>
#include <limits.h>
#include <unistd.h>
#include <stdlib.h>
#include <pwd.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
#include "sh.h"
#include <glob.h>
#include <sys/time.h>
#include <pthread.h> //thread library
#include "dll.h"
#include <utmpx.h>
#include <fcntl.h>
#include <termios.h>

extern struct Node* head;
extern struct Node* tail;

pid_t cpid;
//void *firstRun(void *vargp);
int watch_user_called = 0;

/* function that starts the shell
 * argc: argument count
 * argv: the array of arguments given
 * envp: the array of ponters to environment variables
 */
pthread_mutex_t lock; 
void *firstRun(void *vargp){
	while(1){ 
		sleep(10); 
		pthread_mutex_lock(&lock); 
		struct Node *temp = head;
		while(temp != NULL){
			int isTempIn = 0;
			printf("\nThis is temp's name: %s \n",temp->userName);
			struct utmpx *up;
			setutxent();			/* start at beginning */
			while (up = getutxent()) {	/* get an entry */
				if ( up->ut_type == USER_PROCESS ) {	//only want the users
					if(strcmp(temp->userName,up->ut_user) == 0 && strcmp(temp->tty,up->ut_line) == 0){ //is the user still logged in?
						isTempIn = 1;
						printf("user: %s is logged on %s from %s.\n",temp->userName, temp->tty, up ->ut_host );
					}
					if(strcmp(temp->userName,up->ut_user) == 0 && strcmp(temp->tty,up->ut_line) != 0){ // are they logged in from another ?
						int redundant = findTty(up->ut_line);
						if (redundant < 0) {
							printf("%s has logged on %s from %s.\n",temp->userName,temp->tty,up->ut_host );
							push(temp->userName,up->ut_line);  // adds new user to linked list
						}
					}
				}
			}
			
			if(isTempIn == 0){ // lets user know there are no other connections
				printf("%s has logged off %s \n",temp->userName,temp->tty);
				delet2(temp->userName,temp->tty);
				printf("Watched users are:  \n");
				displayForward();
			}
			temp = temp->next;
		}
		pthread_mutex_unlock(&lock); 
	}
}


int sh( int argc, char **argv, char **envp)
{ /*NEW VARBS*/
    int pipe1Flag, pipe2Flag, bgFlag = 0; // |, |&, &
    int r = 0;	//tells us if it was successful or not
    int redirect1, redirect2, redirect3, redirect4, redirect5, fd = 0;//redirect to redirect5
    int noclober = 0;
    pid_t shellPG = getpgid(0);
  //Setting up variables needed for the shell to function
  char * prompt = calloc(PROMPTMAX, sizeof(char));
  char * prefix = "";
  char *commandline = calloc(MAX_CANON, sizeof(char));
  char *command, *arg, *commandpath, *p, *pwd, *owd;
  char **args = calloc(MAXARGS, sizeof(char*));
  int uid, i, status, argsct, go = 1;
  struct passwd *password_entry;
  char *homedir;
  struct pathelement *pathlist;
  int count;
  char *token;
  struct prev_cmd* head = NULL;
  struct alias* alist = NULL;
  int space;
  int valid;
  uid = getuid();
  password_entry = getpwuid(uid);               /* get passwd info */
  homedir = password_entry->pw_dir;		/* Home directory to start
						  out with*/

  // store the current working directory
  if ( (pwd = getcwd(NULL, PATH_MAX+1)) == NULL )
  {
    perror("getcwd");
    exit(2);
  }
  owd = calloc(strlen(pwd) + 1, sizeof(char));
  memcpy(owd, pwd, strlen(pwd));

  // Set up the initial prompt
  prompt[0] = ' '; prompt[1] = '['; prompt[2] = '\0';

  strcat(prompt, pwd);
  prompt[strlen(prompt)+3] = '\0';
  prompt[strlen(prompt)] = ']';
  prompt[strlen(prompt)] = '>';
  prompt[strlen(prompt)] = ' ';

  /* Put PATH into a linked list */
  pathlist = get_path();

  while ( go )
  {
    /* print your prompt */
    valid = 1;
    printf("%s%s", prefix, prompt);

    // Read in command line
	if(fgets(commandline, MAX_CANON, stdin) == NULL){
		commandline[0] = '\n';
		commandline[1] = '\0';
		valid = 0;
		printf("\n");
	}

	int space = 1;
	// Remove newline character from end of input
	if (strlen(commandline) > 1){
		commandline[strlen(commandline) - 1] = '\0';
	}
	else {
		valid = 0;
	}

	// Check command for special cases
	for(i = 0; i < strlen(commandline); i++){
		if(commandline[i] != ' '){
			space = 0;
		}

	}//for


	if (space){
		commandline[strlen(commandline)-1] = '\n';
		valid = 0;
	}
	// Parse the command line to separate the arguments
	count = 1;
	args[0] = strtok(commandline, " ");
	while((arg=strtok(NULL, " ")) != NULL){
		args[count] = arg;
		count++;
	}
   	args[count] = NULL;
	argsct = count;


	if (strcmp(args[argsct-1], "&") == 0){ //check last postion for the & character
		bgFlag = 1; //set our flag
		args[argsct-1] = '\0'; //overwrite the last position with null terminating character
		argsct--; //decrement count of args
	}

        for(i = 0; i < argsct; i++ ){ //itterate through tokens until we find |
			if(strcmp(args[i], "|") == 0){ 
				pipe1Flag = 1; //update our flag
				args[i] = args[i+1]; //shift the rest of our args
				args[i+1] = '\0'; //make last arg null character
				argsct--; //decremet args
		}

	}

		//same as above but for |&
	for(i = 0; i < argsct; i++){
		if(strcmp(args[i], "|&") == 0){
			pipe2Flag = 1;
			args[i] = args[i+1];
			args[i+1] = '\0';
			argsct--;
		}


	}

	// Check if command is an alias
	struct alias* curr = alist;
	int found = 0;
	int done = 0;
	if(argsct == 1){
		while(curr != NULL && !done){
			found = 0;
			if(strcmp(curr->name, args[0]) == 0){
				strcpy(commandline, curr->cmd);
				found = 1;
				count = 1;
				args[0] = strtok(commandline, " ");
				while((arg=strtok(NULL, " ")) != NULL){
					args[count] = arg;
					count++;
				}
   				args[count] = NULL;
				argsct = count;
				if(curr->used == 1){
					args[0] = "\n\0";
					printf("Alias Loop\n");
					done = 1;
				}
				curr->used = 1;
			}
			curr = curr->next;
			if(found) {
				curr = alist;
			}


		}

	}

	// Reset (used) aspect of each alias struct
	curr = alist;
	while(curr!=NULL){
		curr->used = 0;
		curr=curr->next;
	}

	

        // Check for each built in command
	command = args[0];
	int count = 0;
	if(argsct >= 3){
		while(count < argsct){
		  if(args[count] != NULL){
			if(strcmp(args[count], ">") == 0){	//redirect one to 5
				redirect1 = 1;
				strcpy(args[count], args[count+1]);
				args[count + 1] = NULL;
				argsct--;
				
				
				if((noclober == 0) || (access(args[count], W_OK))){		//if noclober is zero or no file to overwrite
					fd = open(args[count], O_CREAT|O_WRONLY|O_TRUNC, S_IRWXU);	
					close(1);	//stdout
					dup(fd);
					close(fd);
					args[count] = NULL;	//make it so there is just command
					argsct--;
					r = 1;
					break;
				}
				else{
					printf("can't overwrite \n");
					break;
				}
			
			}
			else if(strcmp(args[count], ">&") == 0){
				redirect2 = 1;
				strcpy(args[count], args[count+1]);
				args[count + 1] = NULL;
				argsct--;
				
				
				if((noclober == 0) || (access(args[count], W_OK) !=0)){		//if noclober is zero or no file to overwrite
					fd = open(args[count], O_CREAT|O_WRONLY|O_TRUNC, S_IRWXU);
					close(1); //stdout
					dup(fd);
					close(2); //stderr
					dup(fd);	//stderr
					close(fd);
					args[count] = NULL;
					argsct--;
					
					r = 1;
					break;
				}
				else{
					printf("can't overwrite \n");
					break;
				}
				
			}
			else if(strcmp(args[count], ">>") == 0){
				redirect3 = 1;
				strcpy(args[count], args[count+1]);
				args[count+1] = NULL;
				argsct--;
				
				
				if((noclober == 0) || (access(args[count], W_OK) ==0)){		//if noclober is zero or file already exists
					fd = open(args[count], O_WRONLY|O_APPEND|O_CREAT, S_IRWXU);	
					close(1);
					dup(fd);
					close(fd);
					args[count] = NULL;	//make it so there is just command
					argsct--;
					
					r = 1;
					break;
				}
				else{
					printf("can't create \n");
					break;
				}
			}
			else if(strcmp(args[count], ">>&") == 0){
				redirect4 = 1;
				strcpy(args[count], args[count +1]);
				args[count +1] = NULL;
				argsct--;
				
				
				if((noclober == 0) || (access(args[count], W_OK) ==0)){		//if noclober is zero or file already exists
					fd = open(args[count], O_WRONLY|O_APPEND|O_CREAT, S_IRWXU);
					close(1); //stdour
					dup(fd);
					close(2); //stderr
					dup(fd);	//stderr
					close(fd);
					args[count] = NULL;
					argsct--;
					count--;
					r = 1;
					break;
				}
				else{
					printf("can't create \n");
					break;
				}
			}
			else if(strcmp(args[count], "<") == 0){
				redirect5 = 1;
				strcpy(args[count], args[count+1]);
				args[count+1] = NULL;
				argsct--;
				
				
				fd = open(args[count], O_RDONLY, S_IRWXU);
				close(0);	//stdin
				dup(fd);
				close(fd);
				args[count] = NULL;
				argsct--;
				
				r = 1;
				break;
			}
		   }
		     count++;
		   
		}
	}
	
	
	waitpid(-1, &status, WNOHANG); //pick up anny zombies and reap them
	
	//direct
	arg = args[1];
	if(strcmp(args[0], "noclober") ==0){
		//found = 1;
		if(noclober == 0){
			noclober = 1;
		}
		else{
			noclober = 0;
		}
		printf("noclober set to: %d \n", noclober);
	}
	else if(strcmp(command, "exit") == 0){
		// Exit the shell
		printf("Executing built-in exit\n");
		exit(0);
	}
	else if(strcmp(command, "which") == 0){
		// Finds first alias or file in path directory that 
		// matches the command
		printf("Executing built-in which\n");
		if(argsct == 1){
			fprintf(stderr, "which: Too few arguments.\n");
		}
		else{

			// Checks for wildcard arguments
			glob_t globber;
			int i;
			for(i = 1; i < argsct; i++){
				int globreturn = glob(args[i], 0, NULL, &globber);
				if(globreturn == GLOB_NOSPACE){
					printf("glob: Runnning out of memory.\n");
				}
				else if(globreturn == GLOB_ABORTED){
					printf("glob: Read error.\n");
				}
				else{

					if(globber.gl_pathv != NULL){
						which(globber.gl_pathv[0], pathlist, alist);
					}
					else {
						which(args[i], pathlist, alist);
					}
				}
			}
		}
	} else if(strcmp(command, "watchuser") == 0){
			
			pthread_mutex_lock(&lock); 
			
			
			
			if(argsct == 2){
				
				addUser(args[1]);
				
			}else if (argsct == 3){
				
			}
			
			printf("Current logged in users: \n");
			struct utmpx *up;
			setutxent();			/* start at beginning */
			while (up = getutxent()) {	/* get an entry */
				if ( up->ut_type == USER_PROCESS ) {	/* only care about users */
					printf("-- %s is logged on %s from %s\n", up->ut_user, up->ut_line, up ->ut_host);
				}
			}
			
			pthread_mutex_unlock(&lock); 
			if(watch_user_called == 0){

				pthread_t thread_id; 
				
				pthread_create(&thread_id, NULL, firstRun, NULL);
				
				watch_user_called = 1;

			} else {

			}
			
			
			
		} else{


		}


	  /*EXTERNAL COMMANDS*/

        // If the command is not an alias or built in function, find it
        // in the path
	found = 0;
	int status;
	char* toexec = malloc(MAX_CANON*sizeof(char));
	if(access(args[0], X_OK) == 0){
		found = 1;
		strcpy(toexec, args[0]);
	}
	else{
		struct pathelement* curr = pathlist;
		char *tmp = malloc(MAX_CANON*sizeof(char));

		while(curr!=NULL & !found){
			snprintf(tmp,MAX_CANON,"%s/%s", curr->element, args[0]);
			if(access(tmp, X_OK)==0){
				toexec = tmp;
				found = 1;
			}
			curr=curr->next;
		}
	}


	if((redirect1==1 || redirect2==1 || redirect3==1 || redirect4==1 || redirect5==1) && r == 0){
			found = 0;
		}

	// If the command if found in the path, execute it as a child process
	if(found){
		if(r == 0){
		  
		  printf("Executing %s\n", toexec);
	
		}

		// Create a child process
		cpid = fork();
		struct itimerval timer;
		if(cpid == 0){
			if(bgFlag){
			  printf("Running command in background\n");
			  setpgid(cpid, 0);
			  //sleep(20); testing if it works


			}
			// Child process executes command
			execve(toexec, args, envp);
		}
		else if(cpid == -1){
			perror(NULL);
		}
		else {
			// Parent process (shell) times child process 
			if(argc > 1){
				timer.it_value.tv_sec = atoi(argv[1]);
				timer.it_interval.tv_sec = 0;
				if(setitimer(ITIMER_REAL, &timer, NULL)==-1){
					perror(NULL);
				}
			}


			if(r == 1 && (redirect1 == 1 || redirect2 == 1 || redirect3 == 1 || redirect4 == 1)){	//reopen stdout
					fd = open("/dev/tty", O_WRONLY);
					close(1);
					dup(fd);
					close(fd);
				}

				if(r == 1 && (redirect2 == 1 || redirect4 == 1)){	//reopen stderr
					fd = open("/dev/tty", O_WRONLY);
					close(2);
					dup(fd);
					close(fd);
				}
				if(r == 1 && (redirect5 == 1)){	//reopen stdin
					fd = open("/dev/tty", O_RDONLY);
					close(0);
					dup(fd);
					close(fd);
				}
				if(bgFlag ==0){
				waitpid(cpid, NULL, 0);

				}
				else{
					tcsetpgrp(0, shellPG); //setgroup
					tcsetpgrp(1, shellPG); //setgroup
					waitpid(cpid, &status, WNOHANG);
				}
			/*NEW CODE HERE*/





			if(pipe1Flag){
				int pfds[2]; //this is correct
				pid_t pid1 = fork(); //
				pipe(pfds);
				if(pid1 == 0){
				  close(1); //closing stdout for command on the left
				  dup(pfds[1]);
				  execve(toexec, args[0], NULL);

				}

				else{
				  //parent does nothing
				}

			  close(pfds[0]); //Have to close our pipe or we get stuck in inf loop
			  close(pfds[1]);

			}//if pipe1Flag


			else if(pipe2Flag){
				printf("Need to implement this\n");
				int pfds[2];
				pid_t pid2 = fork();
				pipe(pfds);
				if(pid2 == 0){
					close(2); //stderr
					dup(pfds[2]);
					close(1); //stdout
					dup(pfds[1]);
					close(pfds[1]);


				}

			}

			// Disable timer after child process terminates
			if(argc > 1){
				timer.it_value.tv_sec = 0;
				if(setitimer(ITIMER_REAL, &timer, NULL)==-1){
					perror(NULL);
				}
			}

			// Return non-normal exit status from child
			if(WIFEXITED(status)){
				if(WEXITSTATUS(status) != 0){
					printf("child exited with status: %d\n", WEXITSTATUS(status));
				}
			}
		}
	}

	// Give error if command not found
        else if (valid){
          fprintf(stderr, "%s: Command not found.\n", args[0]);
        }//else if


	bgFlag = 0;
	r = 0;
	redirect1 = 0;
	redirect2 = 0;
	redirect3 = 0;
	redirect4 = 0;
	redirect5 = 0;
	fd = 0;

      }
  
  return 0;
} /* sh() */

/* function call for 'which' command
 * command: the command that you're checking
 * pathlist: the path list data structure
 * alist: the alias data structure
 */
char *which(char *command, struct pathelement *pathlist, struct alias *alist )
{
	// Set up path linked list variables
	struct pathelement *curr = pathlist;
	char *path = malloc(MAX_CANON*(sizeof(char)));
	int found = 0;


	// Search aliases for command
	struct alias* curra = alist;
	while(curra != NULL){
		if(strcmp(curra->name, command)==0){
			printf("%s:\t aliased to %s\n", curra->name, curra->cmd);
			found = 1;
		}
		curra=curra->next;
	}

	// Search path for command
	while(curr != NULL && !found){
		strcpy(path, curr->element);
		path[strlen(path)+1] = '\0';
		path[strlen(path)] = '/';
		strcat(path, command);
		if(access(path, F_OK) == 0){
			printf("%s\n", path);
			found = 1;
		}
		curr = curr->next;
	}

	// Print error if command not found
	if (!found){
		fprintf(stderr, "%s: command not found\n", command);
		return NULL;
	}

} /* which() */





