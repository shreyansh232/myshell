// Include the standard input/output library.
// This library provides functions for input and output operations,
// such as printf (to print to the console), fgets (to read from input),
// stdin (standard input stream), stdout (standard output stream),
// and perror (to print error messages).
#include <stdio.h>

// Include the standard library.
// This library provides functions for general utility tasks, including
// memory allocation (malloc, free) and program termination (exit).
#include <stdlib.h>

#include <string.h>

// Define a constant 'MAXLINE' with the value 1024.
// This constant represents the maximum number of characters (bytes)
// that our program will read for a single line of input, including
// the newline character ('\n') and the null terminator ('\0').
// Using a defined maximum helps prevent buffer overflows.
#define MAXLINE 1024

// The main function - the entry point of every C program.
// 'int' indicates that the function returns an integer value (typically 0 for success).
// 'void' indicates that this function takes no command-line arguments.
int main(void) {
    // Declare a pointer 'line' of type char*. This pointer will hold the
    // memory address of the first character of the buffer we allocate
    // to store the user's input command line.
    char *line;

    // Allocate memory dynamically on the heap.
    // `malloc(MAXLINE)` requests `MAXLINE` (1024) bytes of memory.
    // If successful, `malloc` returns a pointer to the beginning of the
    // allocated block of memory. This address is stored in the 'line' pointer.
    // If `malloc` fails (e.g., not enough memory available), it returns NULL.
    line = malloc(MAXLINE);

    // Check if memory allocation failed.
    // If 'line' is NULL, it means malloc couldn't allocate the requested memory.
    if (!line) { // Equivalent to: if (line == NULL)
        // Print a system-level error message associated with the last failed
        // system call (in this case, `malloc`). For example, it might print
        // "malloc: Cannot allocate memory". This is more informative than
        // just printing a generic error message.
        perror("malloc");

        // Terminate the program immediately.
        // `exit(1)` signals to the operating system that the program
        // terminated abnormally or with an error. A non-zero exit status
        // conventionally indicates failure.
        exit(1); // Using 1 or EXIT_FAILURE (from stdlib.h) are common conventions
    }

    // Start an infinite loop.
    // `while (1)` creates a loop that will continue forever unless explicitly
    // stopped using 'break' or 'return', or if the program is terminated (e.g., with 'exit').
    // This loop structure is typical for a shell, which continuously prompts the user
    // for input, executes the command, and then prompts again.
    while (1) {
        // --- 1. Print the shell prompt ---
        // Display "mysh> " to the console to indicate that the shell is ready
        // to accept a command.
        printf("mysh> ");

        // Flush the standard output buffer.
        // `printf` often buffers output (especially when not writing a newline).
        // This means the prompt might not appear on the screen immediately.
        // `fflush(stdout)` forces any buffered data in the standard output stream
        // (`stdout`) to be written to the console right away, ensuring the user
        // sees the prompt before the program waits for input.
        fflush(stdout);

        // --- 2. Read user input ---
        // Read a line of text from standard input (usually the keyboard).
        // - `line`: The buffer where the input characters will be stored.
        // - `MAXLINE`: The maximum number of bytes to read into the buffer
        //   (including space for the null terminator '\0'). `fgets` reads at
        //   most `MAXLINE - 1` characters from the input.
        // - `stdin`: The standard input stream (where the keyboard input comes from).
        //
        // `fgets` reads until it encounters a newline character ('\n'), reaches the
        // end-of-file (EOF), or has read `MAXLINE - 1` characters.
        // If a newline is read, it IS stored in the buffer 'line'.
        // `fgets` automatically adds a null terminator ('\0') at the end of the
        // string in the buffer.
        //
        // Return Value:
        // - On success, `fgets` returns the pointer 'line'.
        // - If end-of-file (EOF) is reached before any characters are read (e.g., user presses Ctrl+D
        //   on an empty line), `fgets` returns NULL.
        // - If a read error occurs, `fgets` returns NULL.
        if (fgets(line, MAXLINE, stdin) == NULL) {
            // Handle EOF (Ctrl+D) or a read error.
            // If fgets returns NULL, it usually means the user signaled the end of input.
            // We print a newline character for cleaner terminal output before exiting.
            printf("\n");
            // Exit the infinite `while` loop.
            break;
        }

        // --- TODO: Parse and Execute the command ---
        // At this point, the 'line' buffer contains the command entered by the user
        // (e.g., "ls -l\n\0").
        // The next steps for a real shell would be:
        // 1. Parse 'line': Split the string into the command name and its arguments
        //    (e.g., ["ls", "-l"]). This often involves handling spaces, quotes, etc.
        // 2. Execute the command: Use system calls like `fork`, `execvp` (or similar),
        //    and `waitpid` to create a new process and run the user's command.
        // This section is currently a placeholder.

    } // End of the `while(1)` loop

    // Free the dynamically allocated memory.
    // Since we allocated memory using `malloc`, we MUST release it using `free`
    // when we are finished with it. This returns the memory block back to the
    // system, preventing memory leaks.
    // It's crucial to free memory allocated with malloc/calloc/realloc.
    free(line);

    // Return 0 from main.
    // This indicates to the operating system that the program executed successfully.
    // This is the standard convention for a successful program termination.
    return 0; // Or return EXIT_SUCCESS (from stdlib.h)
}