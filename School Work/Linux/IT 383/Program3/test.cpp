#include "buffer.h"
#define VALUE_MAX 1000
buffer_item buffer[BUFFER_SIZE];
int size = 0; 
pthread_t tid1;
pthread_t tid2;
pthread_attr_t attr;
pthread_mutex_t mutex;
sem_t full;
sem_t empty;

int insert_item(buffer_item item)
{


	//check if array is full
	if(size >= BUFFER_SIZE)
	{
		return -1;
	}
	//add to array
	buffer[size] = item;
	size++;
	return 0;
}

int remove_item(buffer_item *item)
{
	//remove an object from buffer, place it in item
	//return 0 if successful
	//else return -1 if error
	bool done = false;
	if(size <= 0)
	{
		return -1;
	}
	//remove from array and store in pointer
	*item = buffer[size-1];
	size--;
	return 0;
}
void *producer(void *param)
{
	buffer_item item;


	while(true)
	{
		//sleep between random interval 1-10 seconds
		sleep((rand() % 10 )+ 1);
		//generate random number
		item = rand();

		sem_wait(&empty);
		pthread_mutex_lock(&mutex);
		item = rand()%VALUE_MAX;
		if(insert_item(item))
			cout<<"report buffer is full"<<endl;
		else
		{
			cout<<"[producer thread ID: "<< pthread_self()<<" inserted an item (value: "<<item<<") to the buffer."<<endl; 
		}
		//release lock
		pthread_mutex_unlock(&mutex);
		//increment semaphore
		sem_post(&full);
	}
}

void *consumer(void *param)
{
	buffer_item item;

	while(true)
	{
		//sleep for random interval of 1-10 seconds
		sleep((rand()%10) + 1);
		//decrement semaphore
		sem_wait(&full);
		pthread_mutex_lock(&mutex);

		if(remove_item(&item))
			cout<<"report buffer is empty"<<endl;
		else
		{
			cout<<"[consumer thread ID: "<<pthread_self()<<" removed an item (value: "<<item<<") from the buffer."<<endl;
		}
		//release lock
		pthread_mutex_unlock(&mutex);
		//increment semaphore
		sem_post(&empty);
	}
}

//initialize buffer and create separate producer and consumer threads
int main(int argc, char* argv[])
{
	int sleepDuration;
	int numProd;
	int numCons;
	if(argc != 4)
	{
		cout<<"ERROR: need exactly 3 parameters. How long to sleep, num producers, num consumers"<<endl;
		return -1;
	}
	
	//use atoi to parse string
	sleepDuration = atoi(argv[1]);
	numProd = atoi(argv[2]);
	numCons = atoi(argv[3]);

	//init buffer
	pthread_attr_init(&attr);
	pthread_mutex_init(&mutex,NULL);

	//init semaphore
	sem_init(&full,0,0);
	sem_init(&empty,0,BUFFER_SIZE);
	//create prod
	for(int i = 0; i < numProd; i++)
	{
		pthread_create(&tid1, &attr, producer, NULL);
	}
	//create cons
	for(int i = 0; i < numCons; i++)
	{
		pthread_create(&tid2, &attr, consumer, NULL);
	}
	sleep(sleepDuration);

	return 0;
}

