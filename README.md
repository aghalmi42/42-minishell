# 42-minishell

> Created as part of the 42 curriculum by **aghalmi** / **amoderan**

## Description

The minishell project is a complete implementation of a Unix shell coded in C, offering advanced features for syntax analysis, execution and shell management, with implementations of several built-in features, signals, expansion, redirection (addition, heredoc, etc.), pipes, logical operators, subshells and wildcards. This project demonstrates a thorough understanding of system programming, process management, and the inner workings of shells.

## Instructions

### Compile the project
```bash
make
```

### Run minishell
```bash
./minishell
```

## Features

### Parsing Engine
- **Lexical Scanning:** Transforms raw input into structured token sequences
- **Tree Construction:** Generates Abstract Syntax Tree to represent command hierarchy
- **Fault Tolerance:** Detects and reports malformed expressions without crashing

### Execution Engine
- **Process Orchestration:** Spawns child processes via fork/exec for program execution
- **Event Propagation:** Correct signal routing and termination handling
- **I/O Multiplexing:** Pipe chaining and stream redirection implementation

### Memory Management
- **Automatic Reclamation:** Systematic deallocation through a custom garbage collector
- **Leak Prevention:** Rigorous error checking and controlled resource lifecycle

## Resources

- [Learn Git Branching](https://learngitbranching.js.org/?locale=fr_FR)
- [GNU Bash Manual](https://www.gnu.org/software/bash/manual/bash.html)
- [Minishell - Building a Mini Bash](https://m4nnb3ll.medium.com/minishell-building-a-mini-bash-a-42-project-b55a10598218)
- [Exit Codes](http://pierrellensa.free.fr/dev/bash/www.bsdbooks.net/shells/scripting/fr/exitcodes.html)
- [Signals en C](https://www.codequoi.com/envoyer-et-intercepter-un-signal-en-c/)
- [Volatile](http://shtroumbiniouf.free.fr/CoursInfo/Systeme2/TP/CoursSignaux/Volatile.html)
- [GNU Bash Savannah](https://www.gnu.org/savannah-checkouts/gnu/bash/manual/bash.html)
- [Bash - Stéphane Robert](https://blog.stephane-robert.info/docs/admin-serveurs/linux/shells-linux/bash/)
- [Pipes Ubuntu](https://doc.ubuntu-fr.org/pipe)
- [Redirections Bash](https://www.pierre-giraud.com/shell-bash/redirection-gestion-flux/)
- [GNU Signals](https://www.gnu.org/software/bash/manual/html_node/Signals.html)
- [Programmation Bash](https://fr.wikibooks.org/wiki/Programmation_Bash/Commandes_shell)