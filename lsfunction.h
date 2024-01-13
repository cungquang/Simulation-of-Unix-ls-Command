#ifndef _LSFUNCTION_H_
#define _LSFUNCTION_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>
#include <dirent.h>
#include <time.h>
#include <grp.h>
#include <pwd.h>
#include <limits.h>

//Pre-con: get the valid gid_t variable
//Post-con: print the group ID - string
void getAndPrintUserName(uid_t uid);

//Pre-con: get the valid uid_t variable
//Post-con: print the user ID - string
void getAndPrintGroup(gid_t grpNum);

//Pre-con: get the valid file - struct stat*
//Post-con: print Inode number
void print_Ioption(struct stat* file);

//Pre-con: get the valid file - struct stat*
//Post-con: print all information in order: permission - hardlink
//owner - group owner - size of file in bytes - time 
void print_Loption(struct stat* file);

//Pre-con: get the valid directory - struct dirent*
//Post-con: print name of the file
void print_Filename(struct dirent* directory);

//Pre-con: get the valid path - char*
//Post-con: recursively loop through all the avalaible path - print according to requirement
void print_Roption(int option, char* path);

#endif