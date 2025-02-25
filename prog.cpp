/**
 * Assignment 2: Simple UNIX Shell
 * @file pcbtable.h
 * @author Jose Medina
 * @brief This is a simple UNIX Shell supporting history, redirection, background execution, and piping.
 * @version 0.3
 */
#include <stdio.h>
#include <unistd.h>
#include <iostream>
#include <fcntl.h>
#include <cstring>
#include <sys/wait.h>
#include <vector>

using namespace std;

#define MAX_LINE 80  // Maximum command length
vector<string> history;  // Stores command history

/**
 * @brief Removes the newline character at the end of a string.
 * @param str The string to process.
 */
void trim_newline(char *str) {
    size_t len = strlen(str);
    if (len > 0 && str[len - 1] == '\n')
        str[len - 1] = '\0';
}

/**
 * @brief Parses a command string into arguments.
 * @param command The input command string.
 * @param args Array to store parsed arguments.
 * @return Number of arguments parsed.
 */
int parse_command(char command[], char *args[]) {
    int i = 0;
    char *token = strtok(command, " ");  // Tokenize the input string by spaces
    while (token != NULL) {
        args[i++] = token;
        token = strtok(NULL, " ");
    }
    args[i] = NULL;  // Null-terminate the argument list
    return i;
}

/**
 * @brief Executes a given command by forking a child process.
 * @param args Command arguments array.
 * @param background Flag to indicate background execution.
 */
void execute_command(char *args[], bool background) {
    pid_t pid = fork();  // Create a new process
    if (pid < 0) {
        perror("Fork failed");  // Print error if fork fails
        return;
    } else if (pid == 0) {  // Child process
        if (execvp(args[0], args) == -1) {  // Replace child process with new command
            perror("Command not found");
            exit(EXIT_FAILURE);  // Exit on failure
        }
    } else {  // Parent process
        if (!background) {  // Wait for child process if not running in background
            wait(NULL);
        }
    }
}

/**
 * @brief Manages command history, including executing the last command with '!!'.
 * @param command The input command string.
 * @return True if a command was retrieved from history, false otherwise.
 */
bool handle_history(char command[]) {
    trim_newline(command);  // Remove trailing newline

    if (strcmp(command, "!!") == 0) {  // Check for history recall command
        if (history.empty()) {
            printf("No commands in history.\n");
            return false;
        }
        strcpy(command, history.back().c_str());  // Retrieve last command
        printf("%s\n", command);  // Print the last command before executing
    }

    history.push_back(command);  // Store command in history
    return true;
}

/**
 * @brief Runs the shell's main loop, handling user input and executing commands.
 */
void run_shell() {
    char command[MAX_LINE];  // Buffer to store input command
    char *args[MAX_LINE / 2 + 1];  // Argument array
    bool should_run = true;  // Controls the shell loop

    while (should_run) {
        printf("osh> ");  // Print shell prompt
        fflush(stdout);

        if (!fgets(command, MAX_LINE, stdin)) {  // Read user input
            continue;
        }

        trim_newline(command);  // Remove newline from input

        if (strcmp(command, "exit") == 0) {  // Exit condition
            break;
        }

        if (!handle_history(command)) {  // Handle command history
            continue;
        }

        int num_args = parse_command(command, args);  // Parse command into arguments
        if (num_args == 0) {  // Skip empty commands
            continue;
        }

        // Check for background execution
        bool background = false;
        if (strcmp(args[num_args - 1], "&") == 0) {
            background = true;
            args[num_args - 1] = NULL;  // Remove '&' from the command
        }

        execute_command(args, background);  // Execute the parsed command
    }
}

/**
 * @brief Entry point for the shell program.
 * Runs the shell loop until the user exits.
 */
int main() {
    run_shell();
    return 0;
}
