#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "fcntl.h"
#include "sys/mman.h"
#include "sys/shm.h"
#include "sys/stat.h"

int main()
{
	const int SIZE = 4096;
	const char *name = "OS";
	const char *message_0 = "Hello";
	const char *message_1 = "World!";

	//shared mem file descriptor
	int shm_fd;
	//pointer to the shared memory obj
	void *ptr;
	
	//create teh shared mem obj
	shm_fd = shm_open(name,  O_CREAT | O_RDWR, 0666);
	//configure the size of the shared memory obj
	ftruncate(shm_fd,SIZE);
	//memory map to the shared mem obj
	ptr = mmap(0,SIZE,PROT_WRITE, MAP_SHARED, shm_fd,0);

	//write to shared memory obj
	sprintf(ptr,"%s",message_0);
	ptr += strlen(message_0);
	sprintf(ptr,"%s",message_1);
	ptr+=strlen(message_1);

	return 0;

}
