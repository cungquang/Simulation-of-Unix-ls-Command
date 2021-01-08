# UnixlsCommand
******************************************************************************************************************
******              	  										                                                                ******
******                  	                README FOR UNIXLS LINUX COMMAND					                          ******
******													                                                                            ******		
******------------------------------------------------------------------------------------------------------******
******------------------------------------------------------------------------------------------------------******
******              	  										                                                                ******
******					                           CREATOR NAME: HONG QUANG CUNG					                          ******
******              	  										                                                                ******
******************************************************************************************************************

---------------------------------------- Descripton of simulation ---------------------------------------------


This program contain 6 files - zip in folder Process Scheduling Simulation:
- UnixLs.c
- lsadmin.c
- lsadmin.h
- lsfunction.c
- lsfunction.h
- makefile
- README
- A picture show the sample output


---------------------------------------- Instruction for makefile --------------------------------------------


make all - compile all the file for general use
make demo - this will run the ls command with a default option - set of file of current working directory
make valgrind-check - run in valgrind mode - the sample output with memory-leak check
make valgrind-show - run in valgrind mode - the sample output with memory-leak check
make sample-output - run in normal mode - the sample output without memory-leak check
make clean - clean executable file of simulation program


-------------------------------------- Instruction for Command Line ------------------------------------------


GENERAL SYNTAX: ./UnixLs<space>-[l/i/R]<space>[valid directories]

Sample (command line):
./UnixLs -> return the default option of ls command - current working directory
./UnixLs . -> return the files in current working directory
./UnixLs -i -> return the inode number and file name of current working directory
./UnixLs -l -> return the inode number and other information (permission, owner ID, group owner ID, size, last
modified date, file name)
./UnixLs -R -> recursively go through and return of file of the directory tree
./UnixLs -ilR/liR/ilR -> the combination of -i, -l and -R


-------------------------------------- Major Problems of simulation ------------------------------------------

Symbolic link:
- There are a few minor problem with printing format for the symbolic link 

Printing option:
- There are a few problems with the format of printing function, which do not perform as well as actual "ls" 
command


##############################################################################################################
##############################################################################################################

