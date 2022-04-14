#include <stdlib.h>     /* exit() */
#include <unistd.h>     /* fork() and getpid() */
#include <stdio.h>      /* printf() */
#include <string.h>
#include <sys/wait.h>  
#include<time.h> 

// Driver program
int main(void)
{
        // This program will create different sequence of
        // random numbers on every program run
    int inbuf; //buffer
    int pid;
    int fd[2]; //pipe
    int add = 0;
    int msg1, msg2;
        if (pipe(fd) < 0) {
            exit(1); //error
        }

        // Use current time as seed for random generator
        srand(time(0));

        for(int i = 0; i<4; i++){
            //      if(fork() == 0)
            // {
                // if(i < prod){
        // srand(stime);
                                // srand(getpid());
                                msg1  =  (rand() % (20 - 0 + 1)); // simbol \0 adalah end of string
                // msg2  =  (rand() % (20 - 0 + 1)); 
                
                /* tutup bagian input dari pipe */
                close(fd[0]);
                
                // tulis ke pipe
                write(fd[1], &msg1, sizeof(msg1));
           
                // }

                // if(i < cons){
                        close(fd[1]);
                                read(fd[0], &inbuf, sizeof(inbuf)); //buffer terisi
                                add += inbuf;

                                printf("[%d] proses child menulis pesan ke-1: %d \n", getpid(), inbuf);                 
                // }

                

            // }
        }

printf("\n");
        return 0;
}
