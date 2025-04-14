<<<<<<< HEAD
# Program 1: SLOsh
## by Tommy Pho & Anson Wu

This assignment may be completed individually or in pairs.

## Overview

In this programming assignment, you will implement a simple Unix-like shell called **SLOsh**. This shell will support:

- Basic command execution  
- Built-in commands  
- Signal handling  
- I/O redirection  
- Piping  

This is a refresher assignment meant to remind you of core concepts from CSC 357.

## Requirements

Your shell (`slosh`) must implement the following features:

### Basic Command Execution

- Execute external commands  
- Support command-line arguments  
- Handle both relative and absolute paths  
- Report command execution errors appropriately

### Built-in Commands

- `cd [directory]`: Change the current working directory  
- `exit`: Exit the shell

### Command Prompt

- Display the current working directory as a prompt  
- Format: `current_directory>`

### Signal Handling

- `SIGINT` (Ctrl-C) kills a child process  
- The shell itself should **not** be killed

### I/O Redirection

- `command > file`: Redirect output to a file (create or overwrite)  
- `command >> file`: Append output to a file

### Pipes

- `command1 | command2`: Pipe output from `command1` to input of `command2`  
- Handle multi-stage pipes (e.g., `cmd1 | cmd2 | cmd3`)  
- Properly manage file descriptors to avoid leaks

### Status Reporting

- Report **non-zero exit statuses**  
- Report signals that terminated child processes

## Implementation Guidelines / Hints

### Main Loop

- Continuously prompt, parse, and execute user commands

### Parsing

- Tokenize input into commands and arguments  
- Detect special operators: `|`, `>`, `>>`  
- Handle empty commands

### Signal Handling

- Use `sigaction()` to handle `SIGINT`  
- If compiling with C99, include `-D_XOPEN_SOURCE=700` in your flags  
- Child processes should reset signal handling to default

### Process Management

- Use `fork()` to create child processes  
- Use the appropriate `exec()` variant to execute commands  
- Use `waitpid()` to wait for child processes

### Redirection and Pipes

- Use `open()`, `dup2()`, and `close()` for file redirection  
- Use `pipe()` to create pipes

## Testing / Grading Rubric

| Feature | Description |
|--------|-------------|
| Basic execution | Run simple commands (e.g., `ls`) |
| `cd` command | Change directories |
| `exit` command | Shell exits cleanly |
| SIGINT handling | Child killed, shell survives |
| Empty input | Shell handles empty lines |
| Bad command | Reports "command not found" |
| Pipes | Executes pipe chains |
| Complex pipes | Handles multi-stage piping |
| Prompt | Displays current directory |
| Status reporting | Shows non-zero exit codes |
| Absolute paths | Executes commands via full path |
| `>` Redirection | Overwrites file output |
| `>>` Redirection | Appends file output |
| Overwrite behavior | Confirms file replacement |
| Code Quality | Clean, maintainable code |

Each feature is worth 1 point unless otherwise noted.

## Deliverables

Submit a `.tgz` archive containing:

- All source code (no compiled binaries)  
- A `Makefile` to build an executable named `slosh`  
- A plaintext `README` file with:
  - Your name (and partner’s name, if any)  
  - Any special instructions  
  - Additional notes you'd like the grader to know  
  - Filename must be `README` (all caps, no extension)

> Make sure it compiles and runs on the CSL UNIX machines (e.g., `unix1.csc.calpoly.edu`).
=======
# program-1
Anson Wu and Tommy Pho
>>>>>>> anson
