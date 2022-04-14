#include <stdlib.h>     /* exit() */
#include <unistd.h>     /* fork() and getpid() */
#include <stdio.h>      /* printf() */
#include <string.h>
#include<time.h> 
#include <sys/wait.h>   /* wait */
#include <errno.h>      /* errno */
#include <unistd.h>     /* sleep() */
#include <pthread.h> 

pthread_mutex_t lock;

int main(int argc, char **argv) {
        int inbuf; //buffer
        int pid;
        int fd[2]; //pipe
        int add = 0;
        int msg1, msg2;

        //create pipe
        if (pipe(fd) < 0) {
            exit(1); //error
        }
        printf("mulai \n");

        int prod, cons, max;
        scanf("%d %d", &prod, &cons);
        if (prod > cons){
                max = prod;
        }else{
                max = cons;
        }


        int senarai[max];
        // int senarai[max];
        // srand(time(0));

        switch (pid = fork()) {
        
        //producer
        case 0:         /* fork returns 0 ke proses anak */
                for (int i = 0; i < prod; i++)
                {
                        /* code */
                        if(fork()==0){

                                pthread_mutex_lock(&lock);

                                srand(getpid() * rand());

                                for (int j = 0; j < prod; j++)
                                {
                                        senarai[j]  =  (rand() % (20 - 0 + 1)); // simbol \0 adalah end of string
                                        sleep(1);
                                        /* code */
                                }
                                // msg2  =  (rand() % (20 - 0 + 1)); 
                                        printf("producer %d\n", senarai[0]);
                        
                                /* tutup bagian input dari pipe */
                                close(fd[0]);
                                
                                // tulis ke pipe
                                write(fd[1], &senarai, sizeof(senarai));
                                exit(0);
                                pthread_mutex_unlock(&lock);
                        }

                }

                // tulis data ke pipe, random angka 0 - 30
                // write(fd[1], &msg2, sizeof(msg2));
                break;
        
        //consumer
        default:        /* fork returns pid ke proses ortu */
                for (int i = 0; i < cons; i++)
                {
                        if (fork() == 0)
                        {
                                pthread_mutex_lock(&lock);
                                /*tutup bagian output dari pipe*/
                                close(fd[1]);

                                // baca yang ditulis child dari pipe
                                read(fd[0], &senarai, sizeof(senarai)); //buffer terisi
                                for (int j = 0; j < prod; j++){
                                        add += senarai[i];
                                }
                                printf("consumer: %d \n", add);
                                
                                // read(fd[0], &inbuf, sizeof(inbuf)); //buffer terisi
                                // printf("proses child menulis pesan ke-2: %d \n", inbuf);
                                /* code */

                                exit(0);
                                pthread_mutex_unlock(&lock);
                        }
                        // read(fd[0], &senarai, sizeof(senarai)); //buffer terisi
                        //         add += senarai;
                }
                break;
        case -1:        /* error */
                perror("fork");
                exit(1);
        }
        // printf("Hasil akhir add: %d\n", add);
        exit(0);
}
