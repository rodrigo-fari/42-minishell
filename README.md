# 42 Minishell

## Table of Contents
1. [Project Overview](#project-overview)
2. [Folder Organization](#folder-organization)
3. [Features](#features)
   - [Interactive Prompt](#interactive-prompt)
   - [Command Execution](#command-execution)
   - [Signal Handling](#signal-handling)
   - [Quotes and Special Characters](#quotes-and-special-characters)
   - [Redirections and Pipes](#redirections-and-pipes)
   - [Environment Variables](#environment-variables)
   - [Built-in Commands](#built-in-commands)
4. [Authorized Functions](#authorized-functions)
5. [Bash Reference](#bash-reference)

---

## Project Overview

Minishell is a simplified shell implementation developed as part of the 42 curriculum. Its purpose is to provide hands-on experience in working with system-level programming, process management, and implementing core shell functionalities.

---

## Folder Organization

```
📁42_MINISHELL/
│
├──📁inc/
│   └──minishell.h
├──📁obj/(*.o)
│
├──📁src/(*.c)
│   ├────📁ms_built-in/ (built-in related) (bi prefix stands for built-in)
│   │     ├────────📄bi_cd.c (cd command)
│   │     ├────────📄bi_commands.c (commands execution)
│   │     ├────────📄bi_echo.c (echo command)
│   │     ├────────📄bi_error.c (error handler for built-in commands)
│   │     ├────────📄bi_exit.c (exit command)
│   │     ├────────📄bi_export.c (export command)
│   │     ├────────📄bi_pwd.c (pwd command)
│   │     └────────📄bi_unset.c (unset command)
│   │
│   ├────📁ms_env/ (environment variables related) (ev prefix stands for environment)
│   │     ├────────📄ev_env_to_struct.c (puts all environment variables in a linked list)
│   │     └────────📄ev_utils.c (support functions)
│   │
│   ├────📁ms_libft/ (own library of functions)
│   │     └────────📄*libft files.c*
│   │
│   ├────📁ms_main/ (main function and related) (ms prefix stands for minishell)
│   │     ├────────📄main.c (main function)
│   │     ├────────📄ms_exec.c (execution of the code)
│   │     └────────📄ms_utils.c (support functions)
│   │
│   └────📁ms_parsing/ (user input parsing) (ps prefix stands for parsing)
│         ├────────📄ps_error.c (error handler for the parsing)
│         ├────────📄ps_parsing.c (functions to parse the input)
│         └────────📄ps_syntax.c (functions that check if the input is valid or not)
└──Makefile
```

---

## Features

### Interactive Prompt
- Displays the prompt while waiting for a command.

### Command Execution
- Finds and executes the correct command using the PATH or an absolute/relative path.

### Signal Handling
- `ctrl+c`: Displays a new prompt.
- `ctrl+d`: Exits the shell.
- `ctrl+\`: Does nothing.

### Quotes and Special Characters
- `'`: Ignores special characters inside single quotes.
- `"`: Interprets `$` for variables but ignores other special characters.

### Redirections and Pipes
- `<`: Input redirection.
- `>`: Output redirection.
- `>>`: Output redirection in append mode.
- `<<`: Reads until reaching a delimiter.
- `|`: Connects commands with a pipe.

### Environment Variables
- `$`: Supports variables using `$`.
- `?`: Expands to the exit status of the last command.

### Built-in Commands
- `echo`: Supports the `-n` option.
- `cd`: Handles both relative and absolute paths.
- `pwd`: (No options).
- `export`: (No options).
- `unset`: (No options).
- `env`: (No arguments).
- `exit`: (No options).

---

## Authorized Functions

### Input/Output and Memory Functions
- `readline`: Reads a line of input from the user, allowing interactive editing.
- `rl_clear_history`: Clears the command history stored by readline.
- `rl_on_new_line`: Informs readline that a new line is being processed.
- `rl_replace_line`: Replaces the current line in the readline buffer.
- `rl_redisplay`: Refreshes the current line on the terminal.
- `add_history`: Adds a line to the readline command history.
- `printf`: Prints formatted text to standard output.
- `write`: Writes data to a file or output, such as stdout.
- `malloc`: Allocates dynamic memory.
- `free`: Frees memory previously allocated with malloc.

### File and Directory Functions
- `access`: Checks file access permissions.
- `open`: Opens a file and returns a file descriptor.
- `read`: Reads data from a file or input.
- `close`: Closes a file descriptor.
- `unlink`: Removes a file from the filesystem.
- `stat`: Retrieves information about a file (by path).
- `lstat`: Similar to `stat`, but handles symbolic links.
- `fstat`: Retrieves information about a file using a file descriptor.
- `opendir`: Opens a directory for reading its entries.
- `readdir`: Reads the next entry in an open directory.
- `closedir`: Closes a directory previously opened with `opendir`.

### Process and Signal Functions
- `fork`: Creates a new process by duplicating the current one.
- `wait`: Waits for a child process to terminate.
- `waitpid`: Waits for a specific child process to terminate.
- `wait3` and `wait4`: Similar to `wait`, but provide additional child process information.
- `signal`: Sets a handler for a specific signal.
- `sigaction`: Configures signal handling with more control than `signal`.
- `sigemptyset`: Initializes an empty signal set.
- `sigaddset`: Adds a signal to a signal set.
- `kill`: Sends a signal to a process or group of processes.
- `exit`: Terminates a process.

### Terminal Manipulation Functions
- `isatty`: Checks if a file descriptor refers to a terminal.
- `ttyname`: Returns the name of the terminal associated with a file descriptor.
- `ttyslot`: Returns the terminal session number.
- `ioctl`: Controls I/O devices, including terminals.
- `tcsetattr`: Configures terminal attributes.
- `tcgetattr`: Retrieves terminal attributes.

### Environment Variable Functions
- `getenv`: Retrieves the value of an environment variable.

### Path and Directory Manipulation Functions
- `getcwd`: Retrieves the current working directory.
- `chdir`: Changes the current working directory.

### Program Execution Functions
- `execve`: Replaces the current process with a new program.

### Pipe and File Descriptor Functions
- `dup`: Duplicates a file descriptor.
- `dup2`: Duplicates a file descriptor to a specific target descriptor.
- `pipe`: Creates a unidirectional communication channel between processes.

### Error Handling Functions
- `strerror`: Returns a descriptive error message for a given error number.
- `perror`: Prints an error message based on the global `errno` variable.

### Termcap (Advanced Terminal Handling) Functions
- `tgetent`: Initializes the terminal capabilities database.
- `tgetflag`: Returns the value of a terminal capability flag.
- `tgetnum`: Returns the numeric value of a terminal capability.
- `tgetstr`: Returns the string value of a terminal capability.
- `tgoto`: Calculates a cursor position string for the terminal.
- `tputs`: Sends a formatted string to the terminal.

---

## Bash Reference
For detailed Bash specifications, refer to the [GNU Bash Manual](https://www.gnu.org/software/bash/manual/bash.html).

---

Feel free to contribute or suggest changes to improve the Minishell project! This README is open to further enhancements to provide clarity and better user experience.
