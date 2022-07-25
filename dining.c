#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>

#include "dbg.h"

pthread_mutex_t fork1 = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t fork2 = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t fork3 = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t fork4 = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t fork5 = PTHREAD_MUTEX_INITIALIZER;

struct Args_Struct
{
	int num;

} *args, *args2, *args3, *args4, *args5;

void think(int num)
{
	printf("Philosopher %d thinking...\n", num);
	sleep(10);
}

void take_forks12(int num)
{		
	pthread_mutex_lock(&fork1);		

	printf("Philosopher %d taking up fork 1\n", num);

	sleep(2);


	pthread_mutex_lock(&fork2);

	printf("Philosopher %d taking up fork 2\n", num);

	sleep(2);
}

void putdown_forks12(int num)
{
	pthread_mutex_unlock(&fork1);

	printf("Philsopher %d putting down fork 1\n", num);

	sleep(2);


	pthread_mutex_unlock(&fork2);
		
	printf("Philsopher %d putting down fork 2\n", num);

	sleep(2);
}

void take_forks34(int num)
{		
	pthread_mutex_lock(&fork3);		

	printf("Philosopher %d taking up fork 3\n", num);

	sleep(2);


	pthread_mutex_lock(&fork4);

	printf("Philosopher %d taking up fork 4\n", num);

	sleep(2);
}

void putdown_forks34(int num)
{
	pthread_mutex_unlock(&fork3);

	printf("Philosopher %d putting down fork 3\n", num);

	sleep(2);


	pthread_mutex_unlock(&fork4);

	printf("Philosopher %d putting down fork 4\n", num);

	sleep(2);
}

void take_forks15(int num)
{		
	pthread_mutex_lock(&fork1);		

	printf("Philosopher %d taking up fork 1\n", num);

	sleep(2);


	pthread_mutex_lock(&fork4);

	printf("Philosopher %d taking up fork 5\n", num);

	sleep(2);
}

void putdown_forks15(int num)
{
	pthread_mutex_unlock(&fork1);

	printf("Philosopher %d putting down fork 1\n", num);

	sleep(2);


	pthread_mutex_unlock(&fork5);

	printf("Philosopher %d putting down fork 5\n", num);

	sleep(2);
}

void eat(int num)
{
	printf("Philosopher %d eating...\n", num);
	sleep(5);
}

void *philosopher_actions12(void *num)
{
struct Args_Struct *_num = num;

	think(_num->num);	
	take_forks12(_num->num);
	eat(_num->num);
	putdown_forks12(_num->num);	

	return NULL;
}

void *philosopher_actions34(void *num)
{
struct Args_Struct *_num = num;

	think(_num->num);	
	take_forks34(_num->num);
	eat(_num->num);
	putdown_forks34(_num->num);	

	return NULL;
}

void *philosopher_actions15(void *num)
{
struct Args_Struct *_num = num;

	think(_num->num);
	take_forks15(_num->num);
	eat(_num->num);
	putdown_forks15(_num->num);

	return NULL;
}

int main()
{
	args = malloc(sizeof(struct Args_Struct));
	CHECK_MEM(args);	

	args->num = 1;

	pthread_t phi1;

	pthread_create(&phi1, NULL, philosopher_actions12, args);

	//philosopher_actions12(1);

	args2 = malloc(sizeof(struct Args_Struct));
	CHECK_MEM(args2);

	args2->num = 2;

	pthread_t phi2;	

	pthread_create(&phi2, NULL, philosopher_actions34, args2);

	//philosopher_actions34(args2);

	args3 = malloc(sizeof(struct Args_Struct));
	CHECK_MEM(args3);

	args3->num = 3;

	pthread_t phi3;

	pthread_create(&phi3, NULL, philosopher_actions15, args3);

	//philosopher_actions15(args3);

	args4 = malloc(sizeof(struct Args_Struct));	
	CHECK_MEM(args4);

	args4->num = 4;

	pthread_t phi4;

	pthread_create(&phi4, NULL, philosopher_actions34, args4);

	args5 = malloc(sizeof(struct Args_Struct));
	CHECK_MEM(args5);

	args5->num = 5;

	philosopher_actions12(args5);
	

	pthread_join(phi1, NULL);
	pthread_join(phi2, NULL);
	pthread_join(phi3, NULL);
	pthread_join(phi4, NULL);

	if(args) free(args); 
	if(args2) free(args2);
	if(args3) free(args3);
	if(args4) free(args4);
	if(args5) free(args5);

	return 0;

error:

	pthread_join(phi1, NULL);
	pthread_join(phi2, NULL);
	pthread_join(phi3, NULL);
	pthread_join(phi4, NULL);

	
	if(args) free(args); 
	if(args2) free(args2);
	if(args3) free(args3);
	if(args4) free(args4);
	if(args5) free(args5);

	return -1;
}
