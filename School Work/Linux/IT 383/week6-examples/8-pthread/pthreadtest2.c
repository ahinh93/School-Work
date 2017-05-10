/* figure 4.9 in textbook
 */

#include <pthread.h>
#include <stdio.h>

int sum; /* this data is shared by the thread(s) */

int array_values[10][20];


void *runner(void *param); /* the thread */

int main(int argc, char *argv[])
{
	pthread_t tid1,tid2; /* the thread identifier */
	pthread_attr_t attr; /* set of thread attributes */

	if (argc !=2) {
		fprintf(stderr,"usage: a.out <integer value>\n");
		return -1;
	}
	if (atoi(argv[1]) < 0) {
		fprintf(stderr,"%d must be >=0\n",atoi(argv[1]));
		return -1;
	}

	fprintf(stderr,"---Hello, I am parent thread. Now I am creating a new thread...\n");
	/* get the default attributes */
	pthread_attr_init(&attr);
	/* create the thread */
	/* NOTE: we use pthread_create rather than "fork" */
	//pthread_create(&tid, &attr, runner,argv[1]);
	pthread_create(&tid1, &attr, runner,argv[1]);
	pthread_create(&tid2, &attr, runner,argv[1]);

	/* wait for the thread to exit */
	/* NOTE: we use pthread_join rather than "wait" */
	pthread_join(tid1,NULL);
	pthread_join(tid2,NULL);
	fprintf(stderr,"---Hello, I am parent thread. I have created two threads... Now I am waiting for the completion of the two threads.....\n");
	fprintf(stderr,"---Hello, I am parent thread. Just confirmed that the new thread has finished its job......\n");
	
	printf("sum = %d\n",sum);
}

/* The thread will begin control in this function */
void *runner(void *param)
{
	int i, upper = atoi(param);
	sum = 0;

	fprintf(stderr,"---Hello, I am a newly created thread...\n");
	for (i=1; i <= upper; i++)
		sum += i;

	/* NOTE: we need to call pthread_exit() to indicate that
         * thread is being terminated
         */
	pthread_exit(0);
}


