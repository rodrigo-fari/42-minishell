# Minishell - Project Summary and Organization

## Key parts of the project (*Mandatory*)
1. **Interactive prompt**:
   - Must display a prompt while waiting for a command.

2. **Command execution**:
   - Must find and execute the correct command using the `PATH` or an absolute/relative path.

3. **Signal handling**:
   - `Ctrl+C`: Displays a new prompt.
   - `Ctrl+D`: Exits the shell.
   - `Ctrl+\`: Does nothing.

4. **Quotes and special characters**:
   - `'` (single quotes): Ignore special characters within the quotes.
   - `"` (double quotes): Interpret `$` for variables but ignore other special characters.

5. **Redirections and pipes**:
   - `<`: Redirect input.
   - `>`: Redirect output.
   - `>>`: Redirect output in append mode.
   - `<<`: Read until a delimiter is reached.
   - `|`: Connect commands through a pipe.

6. **Environment variables**:
   - Support variables using `$`.
   - `?`: Expands to the exit status of the last command.

7. **Built-in commands**:
   - `echo` (with `-n`).
   - `cd` (with relative or absolute paths).
   - `pwd` (no options).
   - `export` (no options).
   - `unset` (no options).
   - `env` (no arguments).
   - `exit` (no options).

---

## Important rules
1. **42 Norm**:
   - Follow the *Norminette* rules.

2. **No memory leaks**:
   - All dynamically allocated memory must be properly freed.

3. **Allowed external functions**:
   - *Readline library*: `readline`, `add_history`, etc.
   - System calls such as: `fork`, `execve`, `pipe`, `dup2`, etc.
   - File manipulation: `open`, `close`, `read`, `write`.

4. **Limited use of global variables**:
   - Only one global variable is allowed for signal handling.

5. **Readline can leak memory**:
   - You are not required to fix leaks in `readline`, but your code must not have leaks.

6. **No undefined behavior**:
   - Avoid issues such as segmentation faults or double frees.

---

## Core libraries and associated functions
### Libraries
1. **<stdio.h>**
   - Functions: `printf`, `perror`.

2. **<stdlib.h>**
   - Functions: `malloc`, `free`, `exit`, `getenv`.

3. **<unistd.h>**
   - Functions: `write`, `access`, `read`, `close`, `fork`, `chdir`, `dup`, `dup2`, `isatty`, `ttyname`, `ttyslot`.

4. **<signal.h>**
   - Functions: `signal`, `sigaction`, `sigemptyset`, `sigaddset`, `kill`.

5. **<fcntl.h>**
   - Functions: `open`, `fcntl`.

6. **<sys/types.h>**, **<sys/stat.h>**
   - Functions: `stat`, `lstat`, `fstat`.

7. **<dirent.h>**
   - Functions: `opendir`, `readdir`, `closedir`.

8. **<string.h>**
   - Functions: `strerror`.

9. **<sys/ioctl.h>**
   - Functions: `ioctl`.

10. **<termios.h>**
    - Functions: `tcsetattr`, `tcgetattr`.

11. **<readline/readline.h>**
    - Functions: `readline`, `add_history`, `rl_clear_history`, `rl_on_new_line`, `rl_replace_line`, `rl_redisplay`.

12. **<curses.h>** or **<term.h>**
    - Functions: `tgetent`, `tgetflag`, `tgetnum`, `tgetstr`, `tgoto`, `tputs`.

---

## Notes on libraries
1. **External libraries**:
   - The `readline` library must be installed on the system. Ensure it is correctly linked in the *Makefile* with appropriate flags (e.g., `-lreadline`).

2. **Libft**:
   - You can use your own `libft` for utility functions such as string manipulation (`ft_split`, `ft_strjoin`, etc.).

3. **Forbidden functions**:
   - Any function not explicitly listed (e.g., `system`, `strtok`) is not allowed.

---

## How to divide the project as a team
1. **Parsing and command interpretation**:
   - One teammate can focus on parsing user input (string handling, environment variables, quotes, etc.).

2. **Command execution and redirections**:
   - The other can handle command execution, including redirections and pipes.

3. **Process and signal management**:
   - Implement process control (`fork`, `execve`, etc.) and signal handling.

4. **Built-in commands**:
   - Split the implementation of built-ins (e.g., `cd`, `echo`) between teammates.

5. **Integration and testing**:
   - Both teammates should participate in integrating components and testing.

---

## What to study
- **Processes and syscalls**:
  - `fork()`, `execve()`, `waitpid()`, `pipe()`, `dup2()`.

- **Input/output redirection**:
  - File descriptor manipulation (`open`, `close`, `dup2`).

- **Signals**:
  - Usage of `signal` and `sigaction`.

- **Environment variables**:
  - `getenv`, `setenv`.

---

## Initial plan
1. Set up the **Makefile** with basic rules (`NAME`, `all`, `clean`, etc.).
2. Divide work into main functionalities.
3. Start with a basic interactive prompt that displays user input.
4. Expand to include parsing, command execution, and other required features.

