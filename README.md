# Simple Shell

A simple UNIX command interpreter written in C as part of the Holberton School low-level programming curriculum.  
This project replicates the core behavior of the traditional UNIX shell while providing a lightweight and educational implementation.

---


## 🧠 Project Overview

The goal of this project is to build a functional command-line interpreter that:

- Displays a prompt
- Waits for the user to enter a command
- Parses the command and its arguments
- Executes commands found in the system PATH
- Handles errors gracefully
- Supports both interactive and non-interactive modes

This project focuses on understanding:
- Process creation (`fork`)
- Program execution (`execve`)
- Environment variables (`environ`)
- Memory management (`malloc`, `free`)
- System calls and error handling

---


## 🖥️ Features

### ✅ Core Functions
- Execute commands from user input
- Locate executables using the PATH environment variable
- Fork child processes to run commands
- Handle built-in commands (`exit`, `env`)
- Read input using a custom getline implementation
- Support command arguments


### ❌ Not Supported
This shell intentionally avoids advanced features:
- No pipes (`|`)
- No redirection (`>`, `<`)
- No logical operators (`&&`, `||`)
- No environment variables manipulation
- No command substitution
- No aliases
- No scripting

---


## 📥 Installation

Clone the repository:

```bash
git clone https://github.com/agalotaibi/holbertonschool-simple_shell.git
cd holbertonschool-simple_shell
```

### Compile using:
```bash
gcc -Wall -Werror -Wextra -pedantic *.c -o hsh
```

## 🚀 Usage

### Interactive Mode
```bash
./hsh
$
```

### Non-interactive Mode
```bash
echo "ls -l" | ./hsh
```

## 🧩 Built-in Commands
exit [status]

Exit the shell.
	•	Without a status → exit using the status of the last command
	•	With a status → exit using that value

env

Print the current environment variables.

### 🧪 Example Session
```bash
$ ./hsh
$ ls
main.c  shell.h  hsh  README.md
$ pwd
/home/vagrant/simple_shell
$ env
PATH=/usr/local/sbin:/usr/local/bin:...
$ exit
```

## 📄 Manual Page
A full formatted man page is included:
```bash
man ./man_1_simple_shell
```

## 👩🏻‍💻 Authors
Amaal AlOtaibi — @agalotaibi￼

Lamyaa Alghaihab — @Lamyaa439￼
