#include <stdio.h>
#include <iostream>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>

using namespace std;

int main (int argc, char **argv) {
    pid_t pid_radgen;
    int pipe_radgen[2];  // Initializing the reading file discriptor and the writing file descriptor 
    pipe(pipe_radgen);
    
    pid_radgen = fork();

    if(pid_radgen == (pid_t) -1 )
    {
        exit(EXIT_FAILURE);

    }
    if(pid_radgen == (pid_t) 0 ) // first child process 
    {
        close(pipe_radgen[0]);
        dup2(pipe_radgen[1] , STDOUT_FILENO);
        close(pipe_radgen[1]);
        execv("./rgen", argv);
    }
close(pipe_radgen[1]);
pid_t pid_ass1;
int pipe_ass1[2];
pipe(pipe_ass1);
pid_ass1 =  fork();
    if(pid_ass1 == (pid_t) -1)
    {
        exit(EXIT_FAILURE);
    }
    if(pid_ass1 == (pid_t) 0)
    {
        dup2(pipe_radgen[0] , STDIN_FILENO);
        close(pipe_radgen[0]);
        close(pipe_ass1[0]);
        dup2(pipe_ass1[1] , STDOUT_FILENO);
        close(pipe_ass1[1]);
        execl("/bin/sh", "sh" ,"-c", "python3 ./a1ece650.py",(char*) NULL);
    }
close (pipe_radgen[0]);
close (pipe_ass1[1]);
FILE* a2_write = popen("./a2ece650" , "w");
pid_t pid_ass1_r;
pid_ass1_r =fork();
    if (pid_ass1_r  == (pid_t) -1)
    {
        exit(EXIT_FAILURE);
    }
    if(pid_ass1_r == (pid_t) 0)
    {
        FILE* a1_F = fdopen(pipe_ass1[0] , "r");
        char* stream = NULL;
        size_t bytes= 0 ;
        while(getline(&stream , &bytes , a1_F) != -1)
        {
            fputs(stream , a2_write);
            fflush(a2_write);
        }
        fclose(a1_F);
        fclose(a2_write);
        exit(EXIT_SUCCESS);
    }    
close(pipe_ass1[0]);
char* stream_from_Driver = NULL;
size_t bytes = 0 ;
    while (getline(&stream_from_Driver , &bytes , stdin) != -1)
    {
        fputs(stream_from_Driver , a2_write);
        fflush(a2_write);
    }
    kill(pid_radgen ,  SIGTERM);
    pclose(a2_write);

        return EXIT_SUCCESS;
}
