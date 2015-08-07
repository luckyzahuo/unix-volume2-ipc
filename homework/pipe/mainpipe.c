#include "unpipc.h"

void client(int, int), server(int, int);

int main(int argc, char **argv)
{
    int pipe1[2], pipe2[2];
    pid_t childpid;

    pipe(pipe1);
    pipe(pipe2);

    if( (childpid = fork()) == 0)
    {
        close(pipe1[1]);
        close(pipe2[0]);

        server(pipe1[0], pipe2[1]);
        exit(0);
    }

    close(pipe1[0]);
    close(pipe2[1]);

    client(pipe2[0], pipe1[1]);
    waitpid(childpid, NULL, 0);
    exit(0);
}
