#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <cstdlib>
#include <iostream>
#include <signal.h>

int main() {
    int pipefd[2];
    pid_t gpid;
    pid_t cpid;
    int status;

    if (pipe2(pipefd, O_CLOEXEC) == -1) {
        std::cerr << "pipe error";
        return(1);
    }

    gpid = fork();
    if(gpid == -1) {
        std::cerr << "fork error";
        return(1);
    }

    if (gpid == 0) {
        dup2(pipefd[1], 1);
        execl("./generator", "./generator", NULL);
    }

    cpid = fork();
    if(cpid == -1) {
        std::cerr << "fork error";
        return(1);
    }

    if (cpid == 0) {
        dup2(pipefd[0], 0);
        execl("./consumer", "./consumer", NULL);
    }

    close(pipefd[0]);
    close(pipefd[1]);

    sleep(1);
    kill(gpid,SIGTERM);
    waitpid(gpid, &status, 0);

    std::cerr << "child[" << gpid << "] exited with status " << WEXITSTATUS(status) << std::endl;

    waitpid(cpid, &status, 0);

    std::cerr << "child[" << cpid << "] exited with status " << WEXITSTATUS(status) << std::endl;

    return 0;
    
}
