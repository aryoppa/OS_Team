#include <stdlib.h>     /* exit() */
#include <unistd.h>     /* fork() and getpid() */
#include <stdio.h>      /* printf() */
#include <string.h>
#include <sys/wait.h>  
#include<time.h> 
#include <stdlib.h>
// #include <pthread.h>

int prod, cons, max;
int inbuf; //buffer
int pid;
int fd[2]; //pipe
int add = 0;
int msg1, msg2;
int num[100], num2, i;

// pthread_mutex_t lock;

void procedur(int i){
	// pthread_mutex_lock(&lock);

	num[i] =  (rand() % 20);//simbol \0 adalah end of string
	printf("%d. nilai %d\n", i+1, num[i]);
	/* tutup bagian input dari pipe */

	close(fd[0]);
	write(fd[1],&num, sizeof(num));

	// pthread_mutex_unlock(&lock);
}
void consumer(int i){
	// pthread_mutex_lock(&lock);
	
	close(fd[1]);
	read(fd[0],&num, sizeof(num));//uffer terisi

	printf("[%d] proses child menulis pesan: %d \n", getpid(), num[i]);

	// pthread_mutex_unlock(&lock);
}

 int main(int argc, char const *argv[])
{
	// if (pthread_mutex_init(&lock, NULL) != 0)
	// {
	// 	printf("\n mutex init gagal\n");
	// 	return 1;
	// }
	scanf("%d %d", &prod, &cons);

	if (prod > cons){
		max = prod;
	}else{
		max = cons;
	}

	//create pipe
	if (pipe(fd) < 0) {
	    exit(1); //error
	}


  	for(int i=0;i<max;i++) // loop will run n times (n=5)
	{
		srand((rand() * time(NULL) * getpid())); //biar angka rand() random setiap program dieksekusi

	    if(fork() == 0){
	    	if(i < prod){
           		procedur(i);
	    	}

	    	if(i < cons){
	    		consumer(i);
	    	}
	        exit(0); //wajib ada biar jumlah proses tepat
	    }
		read(fd[0],&num, sizeof(num));//buffer terisi
		add = num[i] + add;
	}

    printf("Total %d\n", add);

	return 0;
}
