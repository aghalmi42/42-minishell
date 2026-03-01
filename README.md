# Minishell - 42 Project

## 📚 Description

**Minishell** is a project from School 42 that recreates a simplified version of Bash. The goal is to gain deep understanding of processes, file descriptors, command parsing, and shell behavior while implementing a functional command-line interpreter.

This project teaches the fundamentals of how shells work, from parsing user input to executing commands with proper redirections and pipes, all while handling signals and managing processes.

> *"As beautiful as a shell"*

## 🛠️ Features

### Mandatory Part
- **Interactive prompt** displaying when waiting for commands
- **Command history** (using readline library)
- **Executable search** based on PATH variable or absolute/relative paths
- **Quote handling**:
  - Single quotes `'` prevent interpretation of all metacharacters
  - Double quotes `"` prevent interpretation except for `$`
- **Redirections**:
  - `<` input redirection
  - `>` output redirection
  - `<<` heredoc (reads until delimiter)
  - `>>` append mode output redirection
- **Pipes** (`|`) connecting command outputs to inputs
- **Environment variables** expansion (`$VAR`)
- **Exit status** expansion (`$?`)
- **Signal handling**:
  - `ctrl-C` displays new prompt on new line
  - `ctrl-D` exits the shell
  - `ctrl-\` does nothing
- **Built-in commands**:
  - `echo` with `-n` option
  - `cd` with relative or absolute path
  - `pwd` (no options)
  - `export` (no options)
  - `unset` (no options)
  - `env` (no options)
  - `exit` (no options)

### Bonus Part
- ✅ **Logical operators** `&&` and `||` with proper precedence
- ✅ **Parentheses** `()` for command grouping and priority
- ✅ **Wildcards** `*` for pattern matching in current directory

## 🚀 Installation & Usage

### 1. Compilation

```bash
# Compile the project
make

# Clean object files
make clean

# Full cleanup
make fclean

# Recompile everything
make re
```

### 2. Execution

```bash
# Launch minishell
./minishell
```

### 3. Usage Examples

#### Basic Commands
```bash
minishell$ echo "Hello, World!"
Hello, World!

minishell$ pwd
/home/user/minishell

minishell$ cd ..
minishell$ pwd
/home/user
```

#### Environment Variables
```bash
minishell$ echo $USER
username

minishell$ echo $PATH
/usr/local/bin:/usr/bin:/bin

minishell$ export MY_VAR=42
minishell$ echo $MY_VAR
42

minishell$ unset MY_VAR
```

#### Redirections
```bash
# Output redirection
minishell$ echo "Hello" > output.txt
minishell$ cat output.txt
Hello

# Input redirection
minishell$ cat < input.txt

# Append mode
minishell$ echo "World" >> output.txt

# Heredoc
minishell$ cat << EOF
> Line 1
> Line 2
> EOF
Line 1
Line 2
```

#### Pipes
```bash
# Single pipe
minishell$ ls -l | grep minishell

# Multiple pipes
minishell$ cat file.txt | grep "pattern" | wc -l

# Complex piping with redirections
minishell$ < input.txt grep "search" | sort | uniq > output.txt
```

#### Exit Status
```bash
minishell$ ls /existing_directory
minishell$ echo $?
0

minishell$ ls /non_existing_directory
ls: cannot access '/non_existing_directory': No such file or directory
minishell$ echo $?
2
```

#### Quotes
```bash
# Single quotes (literal)
minishell$ echo 'The $USER is $USER'
The $USER is $USER

# Double quotes (expansion)
minishell$ echo "The user is $USER"
The user is username

# Mixed quotes
minishell$ echo "It's a 'mixed' example"
It's a 'mixed' example
```

#### Bonus Features
```bash
# Logical AND (&&) - executes second command only if first succeeds
minishell$ mkdir test && cd test
minishell$ pwd
/home/user/test

# Logical OR (||) - executes second command only if first fails
minishell$ cd non_existing || echo "Directory not found"
Directory not found

# Parentheses for grouping
minishell$ (echo "First" && echo "Second") || echo "Failed"
First
Second

# Wildcards
minishell$ echo *.c
main.c parser.c executor.c

minishell$ ls *.txt
file1.txt file2.txt notes.txt
```

## ⚙️ How It Works

### 1. Reading Input
- Display prompt using `readline()`
- Store command in history with `add_history()`

### 2. Lexical Analysis (Tokenization)
- Break input into tokens (words, operators, quotes)
- Identify token types: WORD, PIPE, REDIRECT, etc.

### 3. Parsing
- Build Abstract Syntax Tree (AST) or command table
- Handle quotes and special characters
- Validate syntax

### 4. Expansion
- Expand environment variables (`$VAR`)
- Expand exit status (`$?`)
- Expand wildcards (`*`) - Bonus

### 5. Execution
- Set up redirections
- Create pipes if needed
- Fork processes
- Execute commands (built-ins or external)
- Wait for child processes

### 6. Cleanup
- Close file descriptors
- Free allocated memory
- Update exit status

## 🎯 Key Concepts

### Process Management
```c
pid_t pid = fork();

if (pid == 0) {
    // Child process
    execve(path, args, envp);
    exit(1);
} else {
    // Parent process
    waitpid(pid, &status, 0);
}
```

### Pipe Implementation
```c
int fd[2];
pipe(fd);

if (fork() == 0) {
    // First command - write end
    close(fd[0]);
    dup2(fd[1], STDOUT_FILENO);
    close(fd[1]);
    execve(cmd1, args1, envp);
}

if (fork() == 0) {
    // Second command - read end
    close(fd[1]);
    dup2(fd[0], STDIN_FILENO);
    close(fd[0]);
    execve(cmd2, args2, envp);
}

close(fd[0]);
close(fd[1]);
```

### Redirection Handling
```c
// Input redirection: <
int fd = open(file, O_RDONLY);
dup2(fd, STDIN_FILENO);
close(fd);

// Output redirection: >
int fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
dup2(fd, STDOUT_FILENO);
close(fd);

// Append mode: >>
int fd = open(file, O_WRONLY | O_CREAT | O_APPEND, 0644);
dup2(fd, STDOUT_FILENO);
close(fd);
```

### Signal Handling
```c
void handle_sigint(int sig) {
    // Handle Ctrl-C
    write(1, "\n", 1);
    rl_on_new_line();
    rl_replace_line("", 0);
    rl_redisplay();
}

signal(SIGINT, handle_sigint);   // Ctrl-C
signal(SIGQUIT, SIG_IGN);        // Ctrl-\ (ignore)
```

## 🐛 Common Challenges & Solutions

### Challenge 1: Quote Parsing
**Problem**: Properly handling nested quotes and escaped characters  
**Solution**: State machine tracking quote state (NONE, SINGLE, DOUBLE)

### Challenge 2: Pipe with Redirections
**Problem**: Combining pipes and redirections in correct order  
**Solution**: Set up redirections before executing, ensuring proper fd management

### Challenge 3: Heredoc Implementation
**Problem**: Reading until delimiter without updating history  
**Solution**: Use temporary file or pipe, read line by line without `add_history()`

### Challenge 4: Memory Leaks
**Problem**: readline() leaks, complex data structures  
**Solution**: Track all allocations, use valgrind, free in reverse order of allocation

### Challenge 5: Signal Handling in Child Processes
**Problem**: Signals affecting child processes incorrectly  
**Solution**: Reset signal handlers in child after fork()

### Challenge 6: Environment Variable Expansion
**Problem**: Expanding variables inside quotes correctly  
**Solution**: Different expansion rules for single vs double quotes

### Challenge 7: Wildcard Expansion (Bonus)
**Problem**: Matching patterns with `*` reliably  
**Solution**: Use `opendir()`/`readdir()` to list files, implement pattern matching

## 🧪 Testing

### Basic Functionality Tests
```bash
# Test built-ins
echo "Test echo"
pwd
cd /tmp && pwd
export TEST=value && echo $TEST
env | grep TEST
unset TEST

# Test redirections
echo "test" > file.txt
cat < file.txt
echo "append" >> file.txt
cat << EOF
heredoc test
EOF

# Test pipes
ls | grep minishell
cat file.txt | wc -l

# Test quotes
echo "Double $USER"
echo 'Single $USER'

# Test exit status
ls /existing && echo $?
ls /nonexist || echo $?
```

### Edge Cases
```bash
# Empty command
minishell$

# Multiple spaces
minishell$    ls     -la      |    grep    test

# Unclosed quotes (should error)
minishell$ echo "unclosed

# Invalid redirections
minishell$ < nonexistent.txt cat
minishell$ > /root/forbidden.txt echo "test"

# Signal handling
minishell$ sleep 100
^C
minishell$ cat
^D
```

### Bonus Tests
```bash
# Logical operators
mkdir dir && cd dir && pwd
cd nonexist || echo "Failed"

# Complex combinations
(echo "A" && echo "B") || echo "C"
echo "1" && (echo "2" || echo "3") && echo "4"

# Wildcards
echo *.c
ls test_*.txt
```

### Memory & Error Checking
```bash
# Check for memory leaks (excluding readline)
valgrind --leak-check=full --show-leak-kinds=all \
         --suppressions=ignore.supp ./minishell

# Stress test with many pipes
seq 1 100 | grep 5 | wc -l

# Test with very long commands
<very long command line>
```

## 📝 Built-in Commands Specifications

### echo
```bash
echo [-n] [string ...]
# -n : do not output trailing newline
```

### cd
```bash
cd [directory]
# Changes current directory to specified path
# Relative or absolute paths only
```

### pwd
```bash
pwd
# Prints current working directory
```

### export
```bash
export [name[=value] ...]
# Sets environment variables
# Without arguments, displays all variables
```

### unset
```bash
unset [name ...]
# Removes environment variables
```

### env
```bash
env
# Displays all environment variables
```

### exit
```bash
exit [n]
# Exits shell with status n (default: last command status)
```

## 🔍 Allowed Functions

### Standard Library
- `malloc`, `free`, `write`
- `access`, `open`, `read`, `close`
- `fork`, `wait`, `waitpid`, `wait3`, `wait4`
- `signal`, `sigaction`, `sigemptyset`, `sigaddset`, `kill`
- `exit`, `getcwd`, `chdir`
- `stat`, `lstat`, `fstat`, `unlink`
- `execve`, `dup`, `dup2`, `pipe`
- `opendir`, `readdir`, `closedir`
- `strerror`, `perror`
- `isatty`, `ttyname`, `ttyslot`
- `ioctl`, `getenv`
- `tcsetattr`, `tcgetattr`
- `tgetent`, `tgetflag`, `tgetnum`, `tgetstr`, `tgoto`, `tputs`
- `printf`

### Readline Library
- `readline`
- `rl_clear_history`
- `rl_on_new_line`
- `rl_replace_line`
- `rl_redisplay`
- `add_history`

## 💡 Implementation Tips

### 1. Start Small
Begin with basic command execution before adding pipes and redirections

### 2. Parse Carefully
Invest time in a solid parser - it makes everything else easier

### 3. Test Against Bash
When in doubt, test the behavior in bash - it's your reference

### 4. Handle Errors
Every system call can fail - check return values and handle errors gracefully

### 5. Manage File Descriptors
Always close fds you don't need, especially in child processes

### 6. Use Valgrind Early
Don't wait until the end to check for memory leaks

### 7. Break Down Complex Commands
Test pipes, redirections, and quotes separately before combining them

### 8. Global Variable Usage
Use only ONE global variable for signal number (as per subject requirements)

## 🎓 Learning Outcomes

- **Process Management**: Deep understanding of fork(), exec(), wait()
- **File Descriptors**: Mastery of dup2(), pipe(), redirection
- **Parsing**: Building lexers and parsers for command interpretation
- **Signal Handling**: Proper signal management in interactive programs
- **Memory Management**: Complex data structure allocation and cleanup
- **Shell Behavior**: Understanding how shells parse and execute commands
- **System Calls**: Extensive practice with UNIX system calls
- **Debugging**: Advanced debugging of multi-process programs

## ⚠️ Important Notes

### Memory Leaks
- readline() may leak memory - this is acceptable
- YOUR code must NOT leak memory
- Use valgrind with readline suppressions

### Global Variables
- Maximum ONE global variable allowed
- Should only store signal number
- Cannot be a structure or provide data access

### Reference Behavior
- When uncertain, check bash behavior
- Implement only what's required by subject
- Don't over-engineer unnecessary features

### Norm Compliance
- All code must follow 42's coding norm
- Norm errors result in 0 grade

## 📚 Resources

- [Bash Reference Manual](https://www.gnu.org/software/bash/manual/)
- [GNU Readline Library](https://tiswww.case.edu/php/chet/readline/rltop.html)
- [Linux System Programming](https://www.oreilly.com/library/view/linux-system-programming/9781449341527/)

## 🏆 Evaluation Criteria

- [ ] Program compiles without errors
- [ ] No memory leaks (except readline)
- [ ] Proper error handling (no crashes)
- [ ] All built-ins work correctly
- [ ] Pipes work with multiple commands
- [ ] All redirections work (`<`, `>`, `<<`, `>>`)
- [ ] Quote handling (single and double)
- [ ] Environment variables expansion (`$VAR`, `$?`)
- [ ] Signal handling (Ctrl-C, Ctrl-D, Ctrl-\)
- [ ] PATH resolution for executables
- [ ] Command history works
- [ ] **Bonus**: Logical operators (`&&`, `||`)
- [ ] **Bonus**: Parentheses for priority
- [ ] **Bonus**: Wildcards (`*`)

## 🌟 Bonus Implementation Details

### Logical Operators

**AND Operator (`&&`)**
```bash
command1 && command2
# command2 executes ONLY if command1 succeeds (exit status 0)
```

**OR Operator (`||`)**
```bash
command1 || command2
# command2 executes ONLY if command1 fails (exit status != 0)
```

**Priority with Parentheses**
```bash
(command1 && command2) || command3
# Parentheses create subshells and control execution order
```

### Wildcard Expansion

```bash
# Match all .c files
echo *.c

# Match patterns
ls test_*.txt

# Current directory only (not recursive)
cat *.md
```

Implementation approach:
1. Detect `*` in token
2. Use `opendir()` and `readdir()` to list directory
3. Match pattern against each entry
4. Replace token with matched filenames
5. Sort results alphabetically

---

**Project completed by aghalmi and amoderan as part of the 42 School curriculum** 🚀

*Good luck with your implementation!*
