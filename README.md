# TinySH

TinySH is a small Unix shell written in C++ for my Operating Systems course. The goal of this project was to learn how a shell reads and executes commands using processes.

## Features

- Runs Unix commands using `fork()` and `execvp()`
- Supports commands with arguments
- Supports multiple commands separated by semicolons
- Runs multiple commands on the same line concurrently
- Supports interactive mode and batch mode
- Includes a built-in `quit` command
- Handles invalid commands without crashing the shell

## How to Compile

Compile TinySH using:

```bash
g++ -std=c++17 -Wall -Wextra -Werror -o tinysh tinysh.cpp
```

## How to Run

To run TinySH in interactive mode:

```bash
./tinysh
```

Example:

```text
tinysh> ls
tinysh> pwd
tinysh> echo hello world
tinysh> quit
```

To run TinySH in batch mode:

```bash
./tinysh batch.in
```

The batch file should contain commands that TinySH will read and execute.

## Design Overview

TinySH works by reading one line of input at a time. In interactive mode, the input comes from the user through the terminal. In batch mode, the input comes from a file.

Each line is split into separate commands using the semicolon (`;`) as a delimiter. Each command is then split into words so the program can separate the command name from its arguments.

For each command, TinySH uses `fork()` to create a child process. The child process uses `execvp()` to execute the command. The parent keeps track of how many child processes were created and uses `wait()` to wait for all of them to finish before reading the next line.

Commands on the same line are started before the parent begins waiting for them, which allows them to run concurrently.

The `quit` command is handled directly by TinySH instead of being passed to `execvp()`. When `quit` is found, TinySH waits for any other commands from that line to finish and then exits.

## Known Bugs or Problems

No major known bugs were found during testing. TinySH is a simplified shell and does not include the advanced features of a standard Unix shell.




## Author

Natalie Vidarte
