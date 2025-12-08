#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"


int main(int argc,char **argv){
    int pipe_parent_to_child[2];
    int pipe_child_to_parent[2];
    pipe(pipe_child_to_parent);
    pipe(pipe_parent_to_child);
    int pid;
    pid=fork();
    if (pid<0){
        printf("fork error\n");
        exit(1);
    }
    else if(pid==0){
        char buf;
        read(pipe_parent_to_child[0],&buf,1);
        close(pipe_parent_to_child[0]);
        printf("%d: received ping\n",getpid());

        write(pipe_child_to_parent[1],&buf,1);
        close(pipe_child_to_parent[1]);
        exit(0);

    }
    else{
        char buf;
        write(pipe_parent_to_child[1],"a",1);
        close(pipe_parent_to_child[1]);

        read(pipe_child_to_parent[0],&buf,1);
        close(pipe_child_to_parent[0]);
        printf("%d: received pong\n",getpid());

        wait(0);
        exit(0);
    }
}