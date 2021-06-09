#include <sys/wait.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>


int main(int argc, char *argv[])
{
    // Initialize vars for storing ids and exit status
    pid_t cpid, wpid_out;
    int exit_status;

    // Create a child process and assign its id to cpid
    cpid = fork();
    // Check if the child process was successfully created
    if (cpid == -1) { perror("fork"); exit(EXIT_FAILURE); }

    // If the child exits successfully, output its id
    if (cpid == 0) {            /* Code executed by child */
        printf("Child PID is %d\n", getpid());      
    // If the child is still running, make parent wait for it to finish
    } else {                    /* Code executed by parent */
        do {
            printf("Waitpid(): Waiting for child process\n");
            // When the parent finishes waiting for the child, fetch the waitpid() output
            wpid_out = waitpid(cpid, &exit_status, WUNTRACED | WCONTINUED);
            // If the return from waitpid() == -1, return a failure message
            if (wpid_out == -1) { perror("waitpid"); exit(EXIT_FAILURE); }
            // Else Print the exit status
            if (WIFEXITED(exit_status)) {
                printf("exited, status=%d\n", WEXITSTATUS(exit_status));
            } else if (WIFSIGNALED(exit_status)) {
                printf("killed by signal %d\n", WTERMSIG(exit_status));
            } else if (WIFSTOPPED(exit_status)) {
                printf("stopped by signal %d\n", WSTOPSIG(exit_status));
            } else if (WIFCONTINUED(exit_status)) {
                printf("continued\n");
            }
        } while (!WIFEXITED(exit_status) && !WIFSIGNALED(exit_status));
        exit(EXIT_SUCCESS);
    }

    // The wait() method
    printf("The wait() method test.\n");
    // Create two chil processes
    cpid = fork();
    fork();
    cpid = wait(NULL); /* reaping parent */
    printf("Parent pid = %d\n", getpid());
    printf("Child pid = %d\n", cpid);
    return 0;
}
