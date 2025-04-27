// mysh.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define MAXLINE 1024
#define MAXARGS 128

int main(void) {
    char *line = malloc(MAXLINE);
    char *argv[MAXARGS];
    if (!line) { perror("malloc"); exit(1); }

    while (1) {
        printf("mysh> "); fflush(stdout);
        if (fgets(line, MAXLINE, stdin) == NULL) {
            printf("\n");
            break;
        }
        // tokenize
        int argc = 0;
        char *token = strtok(line, " \t\r\n");
        while (token && argc < MAXARGS-1) {
            argv[argc++] = token;
            token = strtok(NULL, " \t\r\n");
        }
        argv[argc] = NULL;

        if (argc == 0) continue;           // no command

        // built-ins
        if (strcmp(argv[0], "exit") == 0) break;
        if (strcmp(argv[0], "cd") == 0) {
            const char *dir = (argc>1 ? argv[1] : getenv("HOME"));
            if (chdir(dir) != 0) perror("chdir");
            continue;
        }

        // external commands
        pid_t pid = fork();
        if (pid < 0) {
            perror("fork");
        } else if (pid == 0) {
            execvp(argv[0], argv);
            perror("execvp");  // only returns on error
            exit(1);
        } else {
            int status;
            waitpid(pid, &status, 0);
        }
    }

    free(line);
    return 0;
}
