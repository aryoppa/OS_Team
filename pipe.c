#include <stdlib.h>     /* exit() */
#include <unistd.h>     /* fork() and getpid() */
#include <stdio.h>      /* printf() */
#include <string.h>

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

        switch (pid = fork()) {
        
        //producer
        case 0:         /* fork returns 0 ke proses anak */
                // tulis data ke pipe, random angka 0 - 30
                msg1  =  (rand() % (20 - 0 + 1)); // simbol \0 adalah end of string
                msg2  =  (rand() % (20 - 0 + 1)); 
                
                /* tutup bagian input dari pipe */
                close(fd[0]);
                
                // tulis ke pipe
                write(fd[1], &msg1, sizeof(msg1));
                write(fd[1], &msg2, sizeof(msg2));
                break;
        
        //consumer
        default:        /* fork returns pid ke proses ortu */
                /*tutup bagian output dari pipe*/
                close(fd[1]);

                // baca yang ditulis child dari pipe
                read(fd[0], &inbuf, sizeof(inbuf)); //buffer terisi
                add += inbuf;
                printf("proses child menulis pesan ke-1: %d \n", inbuf);
                
                read(fd[0], &inbuf, sizeof(inbuf)); //buffer terisi
                add += inbuf;
                printf("proses child menulis pesan ke-2: %d \n", inbuf);
                break;
        case -1:        /* error */
                perror("fork");
                exit(1);
        }
        printf("Hasil akhir add: %d\n", add);
        exit(0);
}
