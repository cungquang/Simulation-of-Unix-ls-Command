#ifndef _LSADMIN_H_
#define _LSADMIN_H_

#include "lsfunction.h"

//Pre-con: get the array of char[], and size - int
//Post-con: extract the user's input
char** fetch_Userinput(int size, char* list[]);

//Pre-con: none
//Post-con: manage the information flow of the program
void ls_Admin(int size, char* list[]);

#endif