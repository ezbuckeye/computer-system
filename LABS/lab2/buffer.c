/* NOTE: DO NOT REMOVE THIS COMMENT!! CSE 2431 buffer.c SP 23 08032011 */ 

/* STUDENT NAME: Jiahao(Edison) Zhang */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>

#define BUFFER_SIZE 7

typedef unsigned int buffer_item;

buffer_item buffer[BUFFER_SIZE]; /* shared data buffer */

/* Declaration of pthread mutex locks here; these are shared by threads. */
/* See the lab instructions to find out how to initialize the locks in main, */
/* and also how to acquire the lock before entering a critical section, */
/* and how to release the lock after exiting a critical section. */

pthread_mutex_t prod_mutex; /* shared lock used to ensure only one producer thread */
			    /* can access buffer at any given time. */

pthread_mutex_t cons_mutex; /* shared lock used to ensure only one consumer thread */
			    /* can access buffer at any given time. */

pthread_mutex_t output_mutex; /* shared lock used to ensure only one thread */
			     /* can write output at any given time. */

/* See the lab instructions to find out how to initialize */
/* the semaphores in main. */
sem_t empty;	/* shared data empty counting semaphore */

sem_t full;	/* shared data full counting semaphore */

/* shared data buffer indexes */

int in = 0;	/* shared data/index to be used by producers for next position in */
		/* buffer to insert produced item */

int out = 0;	/* shared data/index to be used by consumers for next position in */
		/* buffer from which to consume item */

unsigned int seed = 100; 	/* seed value for rand_r; initialized to 100 */

unsigned int *seedp = &seed; 	/* pointer to seed for rand_r(), a  */
				/* re-entrant, and therefore thread-safe, */
				/* version of rand() */

void *producer (void *param);
void *consumer (void *param);
void insert_item (buffer_item);
void remove_item (buffer_item *);

/* function shared by all producer threads; DO NOT CHANGE THIS CODE */
void *producer (void *param) {
	buffer_item rand;
	while (1) {
		/* generate a random number between 0 and 99 */
		rand = rand_r(seedp) % 100;
		/* sleep for rand * 10000 microseconds */
		usleep(rand * 10000);
		/* insert item into buffer */
		insert_item(rand);
	}
}

/* function shared by all consumer threads; DO NOT CHANGE THIS CODE */
void *consumer (void *param) {
	buffer_item rand;
	while (1) {
		/* generate a random number between 0 and 99 */
		rand = rand_r(seedp) % 100;
		/* sleep for rand * 10000 microseconds */
		usleep(rand * 10000);
		/* remove item from buffer */
		remove_item(&rand);
	}
}

/* function shared by all producer threads; COMPLETE THIS CODE */
void insert_item(buffer_item item) {
	/* fill in code to insert a single item into buffer */

	sem_wait(&empty); /* wait for consumer to consume item(s) in buffer*/
	pthread_mutex_lock(&prod_mutex);	/* wait till lock available*/

	buffer[in] = item;
	in = (in + 1) % BUFFER_SIZE;

	pthread_mutex_lock(&output_mutex);	/* output_mutex lock should be held before writing output */
	printf("producer produced %d\n", item);
	pthread_mutex_unlock(&output_mutex);	/* output_mutex lock should be released after writing output */

	pthread_mutex_unlock(&prod_mutex);
	sem_post(&full);
	

}

/* function shared by all consumer threads; COMPLETE THIS CODE */
void remove_item(buffer_item *item) {
	/* fill in code to remove a single value from buffer and place it in *item */

	sem_wait(&full); /* wait for producer to put item in buffer */
	pthread_mutex_lock(&cons_mutex);

	*item = buffer[out];
	out = (out + 1) % BUFFER_SIZE;
	
	pthread_mutex_lock(&output_mutex);	/* output_mutex lock should be held before writing output */
	printf("\tconsumer consumed %d\n", *item);
	pthread_mutex_unlock(&output_mutex);	/* output_mutex lock should be released after writing output */

	pthread_mutex_unlock(&cons_mutex);
	sem_post(&empty);
}

/* COMPLETE CODE FOR MAIN - SEE COMMENTS BELOW */
int main(int argc, char *argv[]) {
	int sleep_time = atoi(argv[1]);
	int num_prod_threads = atoi(argv[2]);
	int num_cons_threads = atoi(argv[3]);
	int i;

	/* initialize 3 mutex locks using pthread_mutex_init */
	pthread_mutex_init(&prod_mutex, NULL);
	pthread_mutex_init(&cons_mutex, NULL);
	pthread_mutex_init(&output_mutex, NULL);
	
	/* initialize full semaphore using sem_init */
	sem_init(&full, 0, 0);

	/* initialize empty semaphore using sem_init */
	sem_init(&empty, 0, BUFFER_SIZE);

		
	/* Create single thread id (tid) and attribute variable (attr) for the multiple threads */
	pthread_t tid;
	pthread_attr_t attr;
	pthread_attr_init(&attr);

	/* create num_prod_threads with for loop */
	for (i = 0; i < num_prod_threads; i++){
		pthread_create(&tid, &attr, producer, NULL);
	}

	/* create num_cons_threads with for loop */	
	for (i = 0; i < num_cons_threads; i++){
		pthread_create(&tid, &attr, consumer, NULL);
	}

	/* sleep for number of seconds equal to second param on command line */
	sleep(sleep_time);

	return 0;
}

