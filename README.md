#  🖥️ Mini(s)hell

###  📌 Overview
In this project, [Leo](https://github.com/lglauch) and I created our very own shell while learning how to work as a team for the first time. The goal was to replicate many of the features of a standard shell and add useful functionality for both interactive and non-interactive modes.

##  🚀 Features
####  🔹 Prompt
A prompt just like Bash, awaiting user commands.

####  🔧 Builtin Commands
-  echo (with -n option)
-  cd (supports relative & absolute paths, - and ~)
-  pwd
-  export (with and without arguments, supports += to add variables)
-  unset
-  env
-  exit
####  🖥️ External Commands
Execution of external commands using $PATH, as well as relative or absolute paths.

####  🔀 Redirections
<, >, <<, and >> for input/output redirection.
####  🔗 Pipes
|: The output of each command in the pipeline is connected to the input of the next command via a pipe.
####  🧩 Expansion
Handle environment variables starting with $.

Handle $? to display the exit status of the last command executed.
####  🔄 Modes
Support for interactive and non-interactive modes.
####  ⚡ Signal Handling
Handles Ctrl+C, Ctrl+D, and *Ctrl+* signals gracefully.
###  🛠️ Compilation
To compile the shell:
```bash
make
```
To clean up:
```bash
make clean
```
To remove compiled objects:
```bash
make fclean
```
###  📖 Usage
To run the shell:
```bash
./minishell
```
