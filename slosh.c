/**
 * SLOsh - San Luis Obispo Shell
 * CSC 453 - Operating Systems
 * 
 * TODO: Complete the implementation according to the comments
 */

 #include <stdio.h>
 #include <stdlib.h>
 #include <string.h>
 #include <unistd.h>
 #include <sys/wait.h>
 #include <sys/types.h>
 #include <fcntl.h>
 #include <signal.h>
 #include <limits.h>
 #include <errno.h>
 
 /* Define PATH_MAX if it's not available */
 #ifndef PATH_MAX
 #define PATH_MAX 4096
 #endif
 
 #define MAX_INPUT_SIZE 1024
 #define MAX_ARGS 64
 
 /* Global variable for signal handling */
 volatile sig_atomic_t child_running = 0;
 
 /* Forward declarations */
 void display_prompt(void);
 
 /**
  * Signal handler for SIGINT (Ctrl+C)
  * 
  * TODO: Implement the signal handler to:
  * 1. Print a newline
  * 2. If no child is running, display a prompt
  * 3. Make sure the shell doesn't exit when SIGINT is received
  */
 void sigint_handler(int sig) {
     /* TODO: Your implementation here */
 }
 
 /**
  * Display the command prompt with current directory
  */
 void display_prompt(void) {
     char cwd[PATH_MAX];
     
     if (getcwd(cwd, sizeof(cwd)) != NULL) {
         printf("%s> ", cwd);
     } else {
         perror("getcwd");
         printf("SLOsh> ");
     }
     fflush(stdout);
 }
 
 /**
  * Parse the input line into command arguments
  * 
  * TODO: Parse the input string into tokens and store in args array
  * 
  * @param input The input string to parse
  * @param args Array to store parsed arguments
  * @return Number of arguments parsed
  */
 int parse_input(char *input, char **args) {
     /* TODO: Your implementation here */
     int i = 0;
     int j = 0;
     int len = strlen(input);
     if (input && input[len - 1] == '\n') {
         input[len - 1] = '\0';
     }
     char *token = strtok(input, " ");
     for (j = 0; j < MAX_ARGS; j++) {
         args[j] = NULL;
     }
     while (token != NULL && i < MAX_ARGS) {
         args[i] = token;
         i++;
         token = strtok(NULL, " ");
     }
     return 0;
 }
 
 /**
  * Execute the given command with its arguments
  * 
  * TODO: Implement command execution with support for:
  * 1. Basic command execution
  * 2. Pipes (|)
  * 3. Output redirection (> and >>)
  * 
  * @param args Array of command arguments (NULL-terminated)
  */
 void execute_command(char **args) {
     /* TODO: Your implementation here */
     
     /* Hints:
      * 1. Fork a child process
      * 2. In the child, reset signal handling and execute the command
      * 3. In the parent, wait for the child and handle its exit status
      * 4. For pipes, create two child processes connected by a pipe
      * 5. For redirection, use open() and dup2() to redirect stdout
      */
     pid_t cpid;
     int i = 0;
     char *commands[20][MAX_ARGS];
     int numComs = 0;
     int j = 0;
     int append = 0;
     char *outfile = NULL;
     memset(commands, 0, sizeof(commands));
     while (args[i] != NULL) {
         if (strcmp(args[i], "|") == 0) {
             commands[numComs][j] = NULL;
             numComs++;
             j = 0;
         } else if (strcmp(args[i], ">") == 0) {
             commands[numComs][j] = NULL;
             outfile = args[i + 1];
             i++;
         } else if (strcmp(args[i], ">>") == 0) {
             commands[numComs][j] = NULL;
             outfile = args[i + 1];
             append = 1;
             i++;
         } else if (args[i][0] != '\0') { // regular command
             commands[numComs][j] = args[i];
             j++;
         }
         i++;
     }
     if (j > 0) {
         commands[numComs][j] = NULL;
         numComs++;
     }

     int numPipes = numComs - 1;
     int pipefd[2 * numPipes];
     int k = 0;
     int m = 0;
     int x = 0;

     // create all the pipes
     for (k = 0; k < numPipes; k++) {
         if (pipe(pipefd + k * 2) == -1) {
             perror("pipe creation failed");
             exit(EXIT_FAILURE);
         }
     }

     // forking
     for (m = 0; m < numComs; m++) {
         cpid = fork();
         if (cpid == 0) { // child        
             if (m > 0) {
                 dup2(pipefd[(m - 1) * 2], STDIN_FILENO);
             }
             if (m < numPipes) {
                 dup2(pipefd[m * 2 + 1], STDOUT_FILENO);
             }
             if (outfile != NULL && m == numComs - 1 && numPipes == 0) {
                 int outFD;
                 if (append) {
                     outFD = open(outfile, O_WRONLY | O_CREAT | O_APPEND, 0644);
                 } else {
                     outFD = open(outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
                 }
                 dup2(outFD, STDOUT_FILENO);
                 close(outFD);
             }
             
             for (x = 0; x < 2 * numPipes; x++) {
                 close(pipefd[x]);
             }
             execvp(commands[m][0], commands[m]);
             printf("failed");
             exit(EXIT_FAILURE);
         }
     }
     for (k = 0; k < 2 * numPipes; k++) {
         close(pipefd[k]);
     }
     for (k = 0; k < numComs; k++) {
         wait(NULL);
     }   
 }
 
 /**
  * Check for and handle built-in commands
  * 
  * TODO: Implement support for built-in commands:
  * - exit: Exit the shell
  * - cd: Change directory
  * 
  * @param args Array of command arguments (NULL-terminated)
  * @return 0 to exit shell, 1 to continue, -1 if not a built-in command
  */
 int handle_builtin(char **args) {
     /* TODO: Your implementation here */
     return -1;  /* Not a builtin command */
 }
 
 int main(void) {
     char input[MAX_INPUT_SIZE];
     char *args[MAX_ARGS];
     int status = 1;
     int builtin_result;
     
     /* TODO: Set up signal handling for SIGINT (Ctrl+C) */
     
     while (status) {
         display_prompt();
         
         /* Read input and handle signal interruption */
         if (fgets(input, MAX_INPUT_SIZE, stdin) == NULL) {
             /* TODO: Handle EOF and signal interruption */
             break;
         }
         
         /* Parse input */
         parse_input(input, args);
         
         /* Handle empty command */
         if (args[0] == NULL) {
             continue;
         }
         
         /* Check for built-in commands */
         builtin_result = handle_builtin(args);
         if (builtin_result >= 0) {
             status = builtin_result;
             continue;
         }
         
         /* Execute external command */
         execute_command(args);
     }
     
     printf("SLOsh exiting...\n");
     return EXIT_SUCCESS;
 }
