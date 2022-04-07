#include <stdlib.h>     /* exit() */
#include <unistd.h>     /* fork() and getpid() */
#include <stdio.h>      /* printf() */
#include <string.h>

int main(int argc, char **argv) {
        int inbuf; //buffer
        int pid;
        int fd[2]; //pipe
        int add = 0;

        //create pipe
        if (pipe(fd) < 0) {
            exit(1); //error
        }
        printf("mulai \n");
        switch (pid = fork()) {
        //anggap prod
        case 0:         /* fork returns 0 ke proses anak */
                // tulis data ke pipe, random angka 0 - 30
                int msg1  = rand() % 30; 
                int msg2  = rand() % 30; 
                /* tutup bagian input dari pipe */
                close(fd[0]);
                // tulis ke pipe
                write(fd[1], &msg1, sizeof(msg1));
                write(fd[1], &msg2, sizeof(msg2));
                break;
        //anggap cons
        default:        /* fork returns pid ke proses ortu */
                
                /* tutup bagian output dari pipe */
                close(fd[1]);
                // baca yang ditulis child dari pipe
                read(fd[0], &inbuf, sizeof(inbuf)); //buffer terisi
                add += inbuf;
                
                read(fd[0], &inbuf, sizeof(inbuf)); //buffer terisi
                add += inbuf;
                break;
        case -1:        /* error */
                perror("fork");
                exit(1);
        }
        printf("Hasil akhir add: %d\n", add);
        exit(0);
}
