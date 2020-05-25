#include <stdio.h>
#include <stdlib.h>

#include <papi.h>

/* Please add your event here */
int events[3] = {PAPI_L2_DCM, PAPI_L1_DCM, PAPI_TLB_DM}; /*PAPI_L1_DCM, PAPI_L2_DCM, PAPI_TLB_DM*/
int eventnum = 3;
long long values[3];
int eventset;

static unsigned t1, t2, t3;

typedef struct s1 {
	//nodes
	int a;
	int b;
	int c;
	int d;
	int e;
	int START;
	int END;
} s1;

int count = 0;
int ii = 0;
int stride = 15;
int paths_list[6] = {0,0,0,0,0,0};
int edge_list[9] = {0,0,0,0,0,0,0,0,0};
static s1 * a;
static s1 * node;

const int arraysize = 16*(1 << 10); 

static inline void func(int a1, int a2, int a3)
{
	int i;
	node->START++;
	if(a1 || a3){
		//treat the for loops as nodes i.e we don't need to go into them to get the path
		node->a++;

		for(ii =0; ii <= stride ; ii++){
			for(i=0; i<arraysize; i+=stride){
				a[i].a += a[i].e;
			}
		}

		
		if(a2){
			//A-C
			count+=2;
			node->c++;

			for(ii =0; ii <= stride ; ii++){
				for(i=0; i<arraysize; i+=stride){
					a[i].b++;
				}
			}

		}
	} 

	else {
		node->b++;
		//A-C
		count+=4;

		for(ii =0; ii <= stride ; ii++){
			for(i=0; i<arraysize; i+=stride){
				a[i].c = a[i].d++;
			}
		}

	}
	node->d++;
	if(a2 && a3){
		//D-E
		count+=1;
		node->e++;

		for(ii =0; ii <= stride ; ii++){
			for(i=0; i<arraysize; i+=stride){
				a[i].b = a[i].d++;
			}
		}

	}
	node->END++;
	//printf("%d", paths_list[count]);
	//printf("%s%d\n","Count: ", count);
	paths_list[count] = paths_list[count] + 1;
	//printf("%d\n", paths_list[count]);
	count = 0;
}

/* Input set 1 */
void input1()
{
	t1 = 0.5 * RAND_MAX;
	t2 = 0.5 * RAND_MAX;
	t3 = 0.5 * RAND_MAX;
}
/* a-b input set 1*/

/* Input set 2 */
void input2()
{
	t1 = 0.2 * RAND_MAX;
	t2 = 0.6 * RAND_MAX;
	t3 = 0.8 * RAND_MAX;
}
/* a-b input set 2*/

int main()
{


	a = (s1 *) malloc(sizeof(s1) * arraysize);
	node = (s1 *) malloc(sizeof(s1) * arraysize);

	if(PAPI_VER_CURRENT != PAPI_library_init(PAPI_VER_CURRENT)){
		printf("Can't initiate PAPI library!\n");
		exit(-1);
	}


	eventset = PAPI_NULL;
	if(PAPI_create_eventset(&eventset) != PAPI_OK){
		printf("Can't create eventset!\n");
		exit(-3);
	}


	if(PAPI_OK != PAPI_add_events(eventset, events, eventnum)){
		printf("Can't add events!\n");
		exit(-4);
	}


	int i;
	unsigned a1, a2, a3;
	
	srandom(0);

	//input1();
	input2();
	/* input2(); */

	PAPI_start(eventset);

	for(i=0; i<10000; i++){
		a1 = (random() > t1);
		a2 = (random() > t2);
		a3 = (random() > t3);

				
		func(a1, a2, a3);
		
		
	}

	PAPI_stop(eventset, values);

	//S-A
	edge_list[0] = paths_list[3] + paths_list[2] + paths_list[1] + paths_list[0];
	//S-B
	edge_list[1] = paths_list[5] + paths_list[4];
	//A-C
	edge_list[2] = paths_list[3] + paths_list[2];
	//C-D
	edge_list[3] = paths_list[3] + paths_list[2];
	//A-D
	edge_list[4] = paths_list[1] + paths_list[0];
	//B-D
	edge_list[5] = paths_list[5] + paths_list[4];
	//D-E
	edge_list[6] = paths_list[3] + paths_list[5] + paths_list[1];
	//D-END
	edge_list[7] = paths_list[0] + paths_list[2] + paths_list[4];
	//E-END
	edge_list[8] = paths_list[3] + paths_list[5] + paths_list[1];

	/* Print out your profiling results here */
	//printf("%lld\n",values[0]);
	//PAPI_list_events(eventset);
	printf("%s\n", "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
	printf("%s\n", "NODE");
	printf("%s%d\n","START: ", node->START);
	printf("%s%d\n","a: ", node->a);
	printf("%s%d\n","b: ", node->b);
	printf("%s%d\n","c: ", node->c);
	printf("%s%d\n","d: ", node->d);
	printf("%s%d\n","e: ", node->e);
	printf("%s%d\n","END: ", node->END);

	printf("%s\n", "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");

	printf("%s\n", "EDGES");
	printf("%s%d\n", "S-A: ", edge_list[0]);
	printf("%s%d\n", "S-B: ", edge_list[1]);
	printf("%s%d\n", "A-C: ", edge_list[2]);
	printf("%s%d\n", "C-D: ", edge_list[3]);
	printf("%s%d\n", "A-D: ", edge_list[4]);
	printf("%s%d\n", "B-D: ", edge_list[5]);
	printf("%s%d\n", "D-E: ", edge_list[6]);
	printf("%s%d\n", "D-END: ", edge_list[7]);
	printf("%s%d\n", "E-END: ", edge_list[8]);

	printf("%s\n", "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");

	printf("%s\n", "PATHS");
	printf("%s%d\n", "START-A-D-END: ", paths_list[0]);
	printf("%s%d\n", "SART-A-D-E-END: ", paths_list[1]);
	printf("%s%d\n", "START-A-C-D-END: ", paths_list[2]);
	printf("%s%d\n", "START-A-C-D-E-END: ", paths_list[3]);
	printf("%s%d\n", "START-B-D-END: ", paths_list[4]);
	printf("%s%d\n", "START-B-D-E-END: ", paths_list[5]);

	printf("%s\n", "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");

	//L1_DCM
	printf("%s%lld\n","L2 CACHE MISS: ", values[0]);
	//L2_DCM
	printf("%s%lld\n","L1 CACHE MISS: ", values[1]);
	//TLB_DM
	printf("%s%lld\n","TLB CACHE MISS: ", values[2]);


}

