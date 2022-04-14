#include <sys/mman.h>   /* mmap()  */
#include <stdlib.h>     /* exit() */
#include <unistd.h>     /* fork() and getpid() */
#include <stdio.h>      /* printf() */
#include <sys/wait.h>   /*wait*/
#include <errno.h>    
#include<time.h> 
#include <pthread.h> 

pthread_mutex_t lock;

 int main(int argc, char const *argv[])
{
	int prod, cons, max;
	scanf("%d %d", &prod, &cons);

	if (prod > cons){
		max = prod;
	}else{
		max = cons;
	}

	 //init mutex
    if (pthread_mutex_init(&lock, NULL) != 0)
    {
        printf("\n mutex init gagal\n");
        return 1;
    }


	  int pid;

    printf("mulai \n");

    int size = 3 * sizeof(int);

     //buat memory map
    void *addr = mmap(0, size, PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
    printf("Mapped at %p\n", addr);
    int *shared = addr;

    int inbuf; //buffer
    // int pid;
    int fd[2]; //pipe
    int add = 0;
    int msg1, msg2;
    int num[max], num2;

	pthread_mutex_lock(&lock);
  	for(int i=0;i<max;i++) // loop will run n times (n=5)
	{
		srand((rand() * time(NULL) * getpid())); //biar angka rand() random setiap program dieksekusi

	    if(fork() == 0){
	    	if(i <= prod){
				shared[i] = (rand() % 20);//simbol \0 adalah end of string
                printf("%d. nilai %d\n", i+1, shared[i]);
	    	}

	    	if(i <= cons){
				printf("[%d] proses child menulis pesan: %d \n", getpid(), shared[i]);	    		
	    	}
	        exit(0); //wajib ada biar jumlah proses tepat
	    }
	}
	pthread_mutex_unlock(&lock);

	// pthread_mutex_lock(&lock);
	for (int i = 0; i < max; ++i)
	{
		add = shared[i] + add;
		/* code */
	}
    printf(">>> Total %d\n", add);
	// pthread_mutex_unlock(&lock);

	pthread_mutex_destroy(&lock);

	wait(0);
}