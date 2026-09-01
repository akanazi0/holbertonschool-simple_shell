# Simple Shell (`hsh`)

[![Language](https://img.shields.io/badge/Language-C89%20%2F%20GNU89-blue.svg)](https://en.wikipedia.org/wiki/C_(programming_language))
[![Standard](https://img.shields.io/badge/Standard-Betty%20Compliant-brightgreen.svg)](https://github.com/holbertonschool/Betty)
[![Curriculum](https://img.shields.io/badge/Project-Holberton%20School-red.svg)](https://www.holbertonschool.com/)
[![License](https://img.shields.io/badge/License-MIT-yellow.svg)](LICENSE)

A lightweight, POSIX-compliant UNIX command line interpreter implemented in C. Developed as part of the **Holberton School** curriculum, this project demonstrates foundational systems programming concepts including process creation, system call execution, dynamic path lookup, environment variable handling, and robust memory management.

---

## Table of Contents

- [Overview](#overview)
- [Key Features](#key-features)
- [Architecture & Flow](#architecture--flow)
- [File Structure](#file-structure)
- [Allowed Functions & System Calls](#allowed-functions--system-calls)
- [Compilation & Installation](#compilation--installation)
- [Usage Examples](#usage-examples)
  - [Interactive Mode](#interactive-mode)
  - [Non-Interactive Mode](#non-interactive-mode)
- [Supported Built-ins](#supported-built-ins)
- [Error Handling & Return Codes](#error-handling--return-codes)
- [Coding Standard](#coding-standard)
- [Authors](#authors)

---

## Overview

`hsh` functions as a minimal UNIX shell. It presents a command prompt (`$ `), reads standard input from terminal or piped streams, parses inputs into argument arrays, resolves the command location across directory paths, and safely executes target binaries in dedicated child processes.

---

## Key Features

- **Dual Mode Operation:** Supports interactive terminal sessions with a custom `$ ` prompt and non-interactive piped batch executions.
- **Process Management:** Leverages `fork()`, `execve()`, and `waitpid()` for isolated process execution and accurate exit code propagation.
- **Dynamic PATH Search:** Traverses colon-separated directories in `PATH`. Bypasses `fork()` entirely when a binary is not found to optimize system resources.
- **Built-in Commands:** Native support for `exit` (with custom status code parsing) and `env` (environment listing).
- **Whitespace & Comment Parsing:** Sanitizes inputs with leading/trailing spaces or tabs and trims inline shell comments (`#`).
- **Memory Safety & Betty Compliance:** Strict compliance with the Betty style standard with zero memory leaks across core execution paths.

---

## Architecture & Flow

```text
[ User Input ] ---> [ read_input() / getline ]
                             |
                             v
                   [ tokenize_input() ]  ---> Handles whitespace & '#'
                             |
                             v
                  [ Built-in Check ] ---------> (exit / env handled in parent)
                             |
                      (If external command)
                             v
                   [ find_path() ]   ---------> Searches PATH directories
                             |
                     (Command Found?)
                       /           \
                    [Yes]          [No]
                     /               \
            [ fork() ]        [ Print stderr & Exit 127 ]
                |
          [ execve() ]
                |
          [ waitpid() ]
```

---

## File Structure

| File | Description |
| :--- | :--- |
| `main.h` | Core header file containing definitions, standard library includes, and function prototypes. |
| `main.c` | Shell entry point controlling the primary REPL execution loop. |
| `read_input.c` | Handles input retrieval via `getline()`, prompt display, and low-level string writes. |
| `parser.c` | Tokenizes command lines, handles delimiters, and filters out comment characters. |
| `executor.c` | Manages child process creation, program replacement via `execve()`, and exit status capture. |
| `path.c` | Custom environment retrieval (`_getenv`) and directory search logic (`find_path`). |
| `builtins.c` | Logic for internal commands including `exit` (with custom numeric status codes) and `env`. |
| `utils.c` | Custom string helper functions (`_strlen`, `_strcmp`, `_strdup`, `_strcpy`). |
| `utils_helpers.c` | Additional utilities (`_strcat`, `_atoi`) maintaining Betty's 5-function file limit. |
| `AUTHORS` | Contributor listing for the repository. |
| `man_1_simple_shell` | System manual page documenting invocation, grammar, and built-ins. |

---

## Allowed Functions & System Calls

The implementation strictly relies only on standard C library functions and UNIX system calls permitted by the project specification:

`access`, `chdir`, `close`, `closedir`, `execve`, `exit`, `_exit`, `fflush`, `fork`, `free`, `getcwd`, `getline`, `getpid`, `isatty`, `kill`, `malloc`, `open`, `opendir`, `perror`, `read`, `readdir`, `signal`, `stat` (`__xstat`), `lstat` (`__lxstat`), `fstat` (`__fxstat`), `strtok`, `wait`, `waitpid`, `wait3`, `wait4`, `write`.

---

## Compilation & Installation

Clone the repository and compile all source files using the Betty-compliant GNU89 compiler flags:

```bash
# Clone the repository
git clone https://github.com/your-username/holbertonschool-simple_shell.git
cd holbertonschool-simple_shell

# Compile with GCC GNU89 standard
gcc -Wall -Werror -Wextra -pedantic -std=gnu89 *.c -o hsh
```

---

## Usage Examples

### Interactive Mode

Run the shell directly in your terminal:

```bash
$ ./hsh
$ /bin/ls
AUTHORS  README.md  builtins.c  executor.c  hsh  main.c  main.h  man_1_simple_shell  parser.c  path.c  read_input.c  utils.c  utils_helpers.c
$ ls -la
total 68
drwxr-xr-x 15 student student  4096 Sep  1 12:00 .
drwxr-xr-x  3 student student  4096 Sep  1 11:30 ..
-rw-r--r--  1 student student   120 Sep  1 12:00 AUTHORS
-rw-r--r--  1 student student  3950 Sep  1 12:00 README.md
-rwxr-xr-x  1 student student 33480 Sep  1 12:00 hsh
$ exit 0
$
```

### Non-Interactive Mode

Run commands non-interactively via standard input piping or file redirection:

```bash
$ echo "/bin/pwd" | ./hsh
/home/student/holbertonschool-simple_shell

$ echo "ls -l /tmp" | ./hsh
total 0

$ echo "exit 98" | ./hsh
$ echo $?
98
```

---

## Supported Built-ins

| Built-in | Syntax | Description | Example |
| :--- | :--- | :--- | :--- |
| **`exit`** | `exit [status]` | Terminates the shell process. Accepts an optional integer code to exit with a custom status. | `$ exit 2` |
| **`env`** | `env` | Prints the active environment variables formatted as `KEY=VALUE` pairs. | `$ env` |

---

## Error Handling & Return Codes

When a command cannot be located or executed, `hsh` prints diagnostic messages directly to `stderr` matching standard UNIX shell format:

```text
./hsh: <line_number>: <command>: not found
```

### Common Exit Codes

| Exit Status | Condition |
| :---: | :--- |
| **`0`** | Successful execution or clean exit. |
| **`2`** | Illegal argument passed to the `exit` built-in (e.g. non-numeric value or negative number). |
| **`126`** | Permission denied on target executable file. |
| **`127`** | Command not found in `PATH` or invalid executable file path. |

---

## Coding Standard

All C source and header files are formatted and validated against the [Holberton Betty Style Guide](https://github.com/holbertonschool/Betty):

- **Function limits:** Maximum of 5 functions per `.c` file.
- **Function size:** Maximum of 40 lines per function body.
- **Line length:** Strictly capped at 80 characters.
- **Documentation:** Full Betty-compliant doc comments for all functions, structs, and header definitions.
- **Memory Safety:** Checked via `valgrind --leak-check=full --show-leak-kinds=all ./hsh`.

---

## Authors

- **Abdulelah Khalaf Alanazi** — [abdulelah.khma@gmail.com](mailto:abdulelah.khma@gmail.com)
- **Asma Alsayyari** — [asmaalsayari@gmail.com](mailto:asmaalsayari@gmail.com)
