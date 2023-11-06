#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(void)
{
    char *cmd;
    size_t bufsize = 0;

    while (1) {
        printf("#cisfun$ ");
        if (getline(&cmd, &bufsize, stdin) == -1) {
            printf("\n");  // Handle Ctrl+D
            break;
        }
        if (cmd[0] != '\n') {
            // Remove the trailing newline character
            cmd[strlen(cmd) - 1] = '\0';

            // Fork a child process
            pid_t pid = fork();
            if (pid == -1) {
                perror("Fork failed");
            } else if (pid == 0) {
                // Child process
                if (execve(cmd, NULL, NULL) == -1) {
                    perror("Command execution error");
                }
            } else {
                // Parent process
                wait(NULL);
            }
        }
    }

    free(cmd);
    return 0;
}
