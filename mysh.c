#include <stdio.h>
#include <stdlib.h>

#define MAXLINE 1024

int main(void) {
    char *line = malloc(MAXLINE);
    if (!line) {
        perror("malloc");
        exit(1);
    }

    while (1) {
        // 1. Print prompt
        printf("mysh> ");
        fflush(stdout);      // ensure prompt appears immediately

        // 2. Read input
        if (fgets(line, MAXLINE, stdin) == NULL) {
            // EOF (Ctrl-D) or error
            printf("\n");
            break;
        }

        // TODO: parse and execute `line`

    }

    free(line);
    return 0;
}
