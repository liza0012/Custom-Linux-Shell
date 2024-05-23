# Custom-Linux-Shell
This project implements a custom Unix/Linux shell in C, offering basic command execution functionality. Designed to mimic core shell behaviors, it parses user input, executes commands like `cd`, `ls`, and `echo`, and provides error handling. 

# Shell Description
This comprehensive overview provides details on external and internal commands implemented in the shell, along with error-handling mechanisms. Additionally, test cases and assumptions are outlined to guide users in utilizing the shell effectively.

# External Commands
### 1. ls
```- ls -a```
- ls -m
### 2. cat
- cat -n
- cat -E
### 3. date
- date -u
- date -I
### 4. rm
- rm -v
- rm -i
### 5. mkdir
- mkdir -p
- mkdir -v
## Internal Commands
### 1. cd
- cd ~
- cd ..
### 2. echo
- echo *
- echo --help
### 3. pwd
- pwd -L
- pwd -P
# Error Handling
Command Not Found: If the user enters any command other than the specified ones.
No Such File or Directory: In cat and rm commands for non-existing files, and in cd for non-existing directories.
Invalid Option: If the user enters an option not handled by the shell.
Missing Operands: In cat if the user enters it without any argument.
Cannot Create Directory: In mkdir if the user tries to create a duplicate directory.
Fork Error (Child Process Not Created): Error handling for creating a child process using the Fork System Call.
# Implementation Details
The shell can be implemented using both forks and threads. If someone wishes to use threads, they can add &t at the end of the command. For example:

ls -a &t
cat -n cat.c &t
date -I &t
## Test Cases
## 1. ls
ls -a & ls -a &t
ls -m & ls -m &t
## 2. cat
cat -n cat.c & cat -n cat.c &t
cat -E cat.c & cat -E cat.c &t
## 3. date
date -u & date -u &t
date -I & date -I &t
## 4. rm hello.c
rm -v hello.c & rm -v hello.c &t
rm -i hello.c & rm -i hello.c &t
## 5. mkdir newDir
mkdir -p newDir/newDir2 & mkdir -p newDir/newDir2 &t
mkdir -v newDir & mkdir -v newDir &t
# Assumptions
No unnecessary arguments will be passed in between or after the command.
cat and rm commands will not be passed a directory as an argument.
mkdir and rm commands will not be entered without any arguments.
