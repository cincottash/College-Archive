#include <stdio.h>
#include <time.h>
#include <stdlib.h>

#include "papi.h"

typedef union
{
	unsigned long long u64;
	struct
	{
		unsigned long u32lo;
		unsigned long u32hi;
	};
	double d;
} Big;


#define RDTSC(a) __asm__ __volatile__ ("rdtsc" : "=a" (a.u32lo), "=d" (a.u32hi))

void flush(int * g, int size){
	int i;

	for(i = 0; i<size; i++){
		g[i]++;
	}
}

int main(){
	int * a1, *a2;
	int * garbage;

	int arraysize = 16*(1 << 20);
	int i, j, stride;
	int iter, numOfIter;
	struct timeval start, end;
	int r;

	Big bstart, bend;

	int nEvents, ret;
	int events[2] = {PAPI_STL_ICY, PAPI_TOT_CYC};
	long_long values[2];
	char eventLabel[PAPI_MAX_STR_LEN];

	unsigned alignment = 16;
	unsigned long long bytealignment = alignment * sizeof(int);
	
	printf("array size = %d\n", arraysize);

	if (PAPI_num_counters() < 2) {
		fprintf(stderr, "No hardware counters here, or PAPI not supported.\n");
		exit(1);
	}
	nEvents = sizeof(values)/sizeof(values[0]);

	srand(time(NULL));

	garbage = (int *) malloc(sizeof(int) * arraysize);
	for (i = 0; i < arraysize; i++) {
		garbage[i] = rand();
	}


	arraysize += alignment;

	a1 = (int *) malloc(sizeof(int) * 2 * arraysize);
	a2 = (int *) malloc(sizeof(int) * 2 * arraysize);
	a2 = (int *) ((((long long) a2 + bytealignment-1) & ~(bytealignment-1)) - 2);
	for (i = 0; i < arraysize; i++) {
		a1[i] = rand();
		a2[i] = rand();
	}

	numOfIter = 4;


	/* ver. 1: aligned*/
	
	stride = alignment;

	flush(garbage, arraysize);
	

	if ((ret = PAPI_start_counters(events, nEvents)) != PAPI_OK) {
		fprintf(stderr, "PAPI failed to start counters: %s\n", PAPI_strerror(ret));
		exit(1);
	}

/*	RDTSC(bstart);*/

	for(iter = 0; iter < numOfIter; iter++){
		for (i = 0; i < arraysize/2; i++) {
			a1[i] = a1[i] * 2;
			a1[i+stride] = a1[i+stride] * 2;
			a1[i+2*stride] = a1[i+2*stride] * 2;
			a1[i+3*stride] = a1[i+3*stride] * 2;
			a1[i+4*stride] = a1[i+4*stride] * 2;
			a1[i+5*stride] = a1[i+5*stride] * 2;
			a1[i+6*stride] = a1[i+6*stride] * 2;
			a1[i+7*stride] = a1[i+7*stride] * 2;
			a1[i+8*stride] = a1[i+8*stride] * 2;
			a1[i+9*stride] = a1[i+9*stride] * 2;
		}
	}

/*	RDTSC(bend);*/
/*	printf("stride=%d: %lld cycles\n", stride, (bend.u64-bstart.u64)/numOfIter);*/

	printf("stride=%d\n", stride);
		
	if ((ret = PAPI_stop_counters(values, nEvents)) != PAPI_OK) {
		fprintf(stderr, "PAPI failed to read counters: %s\n", PAPI_strerror(ret));
		exit(1);
	}

	for(i = 0; i < nEvents; i++){
		PAPI_event_code_to_name(events[i], eventLabel);
		printf("%s:\t%lld\n", eventLabel, values[i]);
	}


	/* ver. 2: mis-aligned*/

	flush(garbage, arraysize);

/*	RDTSC(bstart);*/

	if ((ret = PAPI_start_counters(events, nEvents)) != PAPI_OK) {
		fprintf(stderr, "PAPI failed to start counters: %s\n", PAPI_strerror(ret));
		exit(1);
	}

	for(iter = 0; iter < numOfIter; iter++){
		for (i = 0; i < arraysize/2; i++) {
			a2[i] = a2[i] * 2;
			a2[i+stride] = a2[i+stride] * 2;
			a2[i+2*stride] = a2[i+2*stride] * 2;
			a2[i+3*stride] = a2[i+3*stride] * 2;
			a2[i+4*stride] = a2[i+4*stride] * 2;
			a2[i+5*stride] = a2[i+5*stride] * 2;
			a2[i+6*stride] = a2[i+6*stride] * 2;
			a2[i+7*stride] = a2[i+7*stride] * 2;
			a2[i+8*stride] = a2[i+8*stride] * 2;
			a2[i+9*stride] = a2[i+9*stride] * 2;
		}
	}

/*	RDTSC(bend);*/
/*	printf("stride=%d: %lld cycles\n", stride, (bend.u64-bstart.u64)/numOfIter);*/

	if ((ret = PAPI_stop_counters(values, nEvents)) != PAPI_OK) {
		fprintf(stderr, "PAPI failed to read counters: %s\n", PAPI_strerror(ret));
		exit(1);
	}
	
	printf("stride=%d\n", stride);

	for(i = 0; i < nEvents; i++){
		PAPI_event_code_to_name(events[i], eventLabel);
		printf("%s:\t%lld\n", eventLabel, values[i]);
	}


	free(a1);
	free(a2);
	free(garbage);
}
