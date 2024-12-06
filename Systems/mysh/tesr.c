#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>
#include <inttypes.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define BUFSIZE 1024
#define MAXARGV 34

int main() {
    char *buffer, *arg;
    int pipes[2], prev_read_end = -1;
    pid_t pid;
    char *argv[MAXARGV];

    while (1) {
        buffer = malloc(sizeof(char) * BUFSIZE);
        printf("$ ");

        // Read in commands

        if (!fgets(buffer, BUFSIZE, stdin)) {
            exit(EXIT_SUCCESS);
        }

        buffer[strcspn(buffer, "\n")] = '\0';

        if (strcmp(buffer, "exit") == 0) {
            exit(EXIT_SUCCESS);
        }

        if (strlen(buffer) == 0) {
            continue;
        }

        // Tokenize commands

        arg = strtok(buffer, " ");
        argv[0] = arg;

        if (argv[0] == NULL) {
            perror("empty program");
            exit(EXIT_FAILURE);
        }

        // If command is cd
        if (strcmp(arg, "cd") == 0) {
            char* dirname = strtok(NULL, " ");

            if (dirname == NULL) {
                dirname = getenv("HOME");
            }

            if (chdir(dirname) != 0) {
                perror("chdir");
            }
        } else {
            int argv_idx = 1;
            int pipe_needed = 0;

            do {
                arg = strtok(NULL, " ");
                if (arg == NULL || strcmp(arg, "|") == 0) {
                    argv[argv_idx] = NULL;

                    pipe_needed = arg != NULL && strcmp(arg, "|") == 0;

                    if (pipe_needed && pipe(pipes) == -1) {
                        perror("pipe");
                        exit(EXIT_FAILURE);
                    }

                    switch (pid = fork()) {
                        case -1: // error
                            perror("fork");
                            exit(EXIT_FAILURE);
                            break;

                        case 0: // child process
                            // Redirect stdin to the previous pipe's read end if not the first program
                            if (prev_read_end != -1) {
                                dup2(prev_read_end, STDIN_FILENO);
                                close(prev_read_end);
                            }

                               // Redirect stdout to the next pipe's write end if not the last program
                            if (pipe_needed) {
                                dup2(pipes[1], STDOUT_FILENO);
                                close(pipes[0]);
                                close(pipes[1]);
                            }

                            execvp(argv[0], argv);
                            perror("execvp");
                            _exit(EXIT_FAILURE);
                            break;

                        default: // parent process
                            // Close the write end of the pipe in the parent
                            if (pipe_needed) {
                                close(pipes[1]);
                            }

                            // Update prev_read_end to the read end of the current pipe
                            if (prev_read_end != -1) {
                                close(prev_read_end);
                            }
                            prev_read_end = pipes[0];

                            // Wait for command to finish if it's the last one and reset variables
                            if (!pipe_needed) {
                                do {
                                    while (wait(NULL) > 0);
                                } while (errno != ECHILD);
                                prev_read_end = -1;
                            }

                            break;
                    }

                    if (arg == NULL) {
                        break;
                    }

                    // Start parsing next command
                    argv[0] = strtok(NULL, " ");
                    argv_idx = 1;
                } else {
                    argv[argv_idx++] = arg;
                }
            } while (arg != NULL);
        }

        free(buffer);
    }

    return 0;
}