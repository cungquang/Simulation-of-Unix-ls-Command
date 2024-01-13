# Simulation of Unix `Ls` Command

## Description of the Command

This program contains 6 files zipped in the UnixLsCommand folder:

- `UnixLs.c`
- `lsadmin.c`
- `lsadmin.h`
- `lsfunction.c`
- `lsfunction.h`
- `makefile`
- `README`
- A picture showing the sample output

## Instruction for Makefile

- `make all`: Compile all the files for general use.
- `make demo`: Run the `ls` command with a default option, listing files in the current working directory.
- `make valgrind-check`: Run in valgrind mode to check for memory leaks, displaying the sample output.
- `make valgrind-show`: Run in valgrind mode to display the sample output with memory-leak checks.
- `make sample-output`: Run in normal mode to display the sample output without memory-leak checks.
- `make clean`: Clean executable files of the simulation program.

## Instruction for Command Line

### GENERAL SYNTAX: `./UnixLs-[l/i/R][valid directories]`

Sample (command line):
- `./UnixLs`: Return the default option of `ls` command for the current working directory.
- `./UnixLs .`: Return the files in the current working directory.
- `./UnixLs -i`: Return the inode number and file name of the current working directory.
- `./UnixLs -l`: Return the inode number and other information (permission, owner ID, group owner ID, size, last modified date, file name).
- `./UnixLs -R`: Recursively go through and return files of the directory tree.
- `./UnixLs -ilR`, `./UnixLs -liR`, `./UnixLs -ilR`: Combinations of `-i`, `-l`, and `-R`.

## Potential Problems of the Command

### Symbolic Link

There are a few minor problems with the printing format for symbolic links.

### Printing Option

There are a few issues with the format of the printing function, which do not perform as well as the actual `ls` command.
