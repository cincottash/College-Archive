#include <time.h>
#include <sys/time.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h> 
#include <unistd.h> 

void flush(int * g, int size){
	int i;

	for(i = 0; i<size; i++){
		g[i]++;
	}
}
/*
void parallelizationImplementation(){
	int *a;
	int *garbage;
	int i,j,iter;
	int stride2 = 2;
	const int arraysize = 9*(1 << 20);
	garbage = (int *) malloc(sizeof(int) * arraysize);
	for (i = 0; i < arraysize; i++) {
		garbage[i] = rand();
	}
	
	a = (int *) malloc(sizeof(int) * arraysize);
	for (i = 0; i < arraysize; i++) {
		a[i] = rand();
	}
	
	int pid = fork();

	for(iter = 0; iter < 10; iter++){
		//fork returns negative if error
		if(pid < 0){
			printf("Error");
			exit(1);
		}
		//fork returns 0 for child
		else if(pid == 0){
			for (j = 0; j < 4; j += stride2){
	            for(i = 2; i < (1 << 20); i += stride2){
					a[8*i+j] = a[8*(i-1)+j] * 2;
				}
			}
		}
		//parent process
		else{
			for (j = 0; j < 4; j += stride2){
	            for(i = 1; i < (1 << 20); i += stride2){
					a[8*i+j] = a[8*(i-1)+j] * 2;
				}
			}
		}
	}
}
*/

int main(){
	int * a;
	int * garbage;

	const int arraysize = 9*(1 << 20);
	int i, j, ii, stride;
	int iter, numOfIter;
	struct timeval start, end;
	int r;

	printf("array size = %d\n", arraysize);
	
	srand(time(NULL));

	garbage = (int *) malloc(sizeof(int) * arraysize);
	for (i = 0; i < arraysize; i++) {
		garbage[i] = rand();
	}
	
	a = (int *) malloc(sizeof(int) * arraysize);
	for (i = 0; i < arraysize; i++) {
		a[i] = rand();
	}
	
	numOfIter = 10;

	/* ver. 1: sequential access */

	flush(garbage, arraysize);

	gettimeofday(&start, NULL);

	for(iter = 0; iter < numOfIter; iter++){
        for (i = 1; i < (1 << 20); i++) {
            for(j = 0; j < 4; j++){
				a[8*i+j] = a[8*(i-1)+j] * 2;
			}
		}
	}

	gettimeofday(&end, NULL);

	printf("v1: %lf us\n", (((end.tv_sec * 1000000 + end.tv_usec)
				- (start.tv_sec * 1000000 + start.tv_usec)))*1.0/numOfIter);


	/* end */

	/* ver. 2: sequential access */

	stride = 4;

	flush(garbage, arraysize);

	gettimeofday(&start, NULL);

	for(iter = 0; iter < numOfIter; iter++){
		for (ii =1; ii <= stride ; ii++){
			for (i = ii; i < (1 << 20); i+=stride) {
				for(j = 3; j >= 0; j--){
					a[8*i+j] = a[8*(i-1)+j] * 2;
				}
			}
		}
	}

	gettimeofday(&end, NULL);

	printf("v2: %lf us\n", (((end.tv_sec * 1000000 + end.tv_usec)
				- (start.tv_sec * 1000000 + start.tv_usec)))*1.0/numOfIter);



	/* ver. 3: for loop reversal */

	flush(garbage, arraysize);

	gettimeofday(&start, NULL);

	for(iter = 0; iter < numOfIter; iter++){
        for (j = 0; j < 4; j++) {
            for(i = 1; i < (1 << 20); i++){
				a[8*i+j] = a[8*(i-1)+j] * 2;
			}
		}
	}

	gettimeofday(&end, NULL);

	printf("v3: %lf us\n", (((end.tv_sec * 1000000 + end.tv_usec)
				- (start.tv_sec * 1000000 + start.tv_usec)))*1.0/numOfIter);
	
	/* end */



	/* ver. 4: parallelization */

	

	flush(garbage, arraysize);

	gettimeofday(&start, NULL);

	int pid = fork();
	int stride2 = 2;

	for(iter = 0; iter < 10; iter++){
		//fork returns negative if error
		if(pid < 0){
			printf("Error");
			exit(1);
		}
		//fork returns 0 for child
		else if(pid == 0){
			for (j = 0; j < 4; j += stride2){
	            for(i = 2; i < (1 << 20); i += stride2){
					a[8*i+j] = a[8*(i-1)+j] * 2;
				}
			}
		}
		//parent process
		else{
			for (j = 0; j < 4; j += stride2){
	            for(i = 1; i < (1 << 20); i += stride2){
					a[8*i+j] = a[8*(i-1)+j] * 2;
				}
			}
		}
	}

	gettimeofday(&end, NULL);

	printf("v4: %lf us\n", (((end.tv_sec * 1000000 + end.tv_usec)
				- (start.tv_sec * 1000000 + start.tv_usec)))*1.0/numOfIter);


	r = rand() % arraysize;
	printf("a[%d] = %d\n", r, a[r]);

	free(a);
	free(garbage);

}

