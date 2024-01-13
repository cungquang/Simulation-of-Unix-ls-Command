//#########################################################################################
//###							Prorgarm Administration									###	
//###					       fectch_Userinput - ls_Admin								###
//###																					###
//#########################################################################################

#include "lsadmin.h"

static char** buffer = NULL;		//buffer to get input directory
static int test_char[3];			//array of options: 0 - i option; 1 - l option; 2 - R option
static int option = 0; 				//check user's option request
static char sym_Link[PATH_MAX];		//array store the actual path of symbolic link
static int new_Size = 0;			//size of sym_link array
static int* index_File = NULL;		//array of index of folder from user-input

//Pre-con: get the array of char[], and size - int
//Post-con: extract the user's input
char** fetch_Userinput(int size, char* list[]){

	//memset(buffer, 0, sizeof(char)* PATH_MAX);
	memset(test_char, 0, sizeof(int)*3);
	int index_Path = 0;

	for(int i = 1; i < size; i++){
		if(list[i][0] != '-')
			new_Size++;
	}

	buffer = malloc(sizeof(char*)* new_Size);
	index_File = malloc(sizeof(int)*new_Size);
	memset(index_File, 0, sizeof(int)*new_Size);

	//loop through all the user arguments
	for(int i = 1; i < size; i++){

		//user provide option
		if(list[i][0] == '-'){
			for(int j = 0; j < strlen(list[i]); j++){
				
				//if user ask for i option - index 0
				if(list[i][j] == 'i'){
					test_char[0] = 1;
				}
				//if user ask for l option - index 1
				if(list[i][j] == 'l'){
					test_char[1] = 1;
				}
				//if user ask for R option - index 2
				if(list[i][j] == 'R'){
					test_char[2] = 1;
				}
			}
		}

		//user provide the alternative link
		else{

			//create the new array of char
			buffer[index_Path] = malloc(sizeof(char)*PATH_MAX);
			memset(buffer[index_Path], 0, sizeof(char)*PATH_MAX);
			index_File[index_Path] = i; 

			char* check = realpath(list[i], buffer[index_Path]);
			if(!check){
				char err_Message[100]; 
				strcat(err_Message, "UnixLs: cannot access '");
				strcat(err_Message, list[i]);
				strcat(err_Message, "'");
				perror(err_Message);

				memset(err_Message, 0, sizeof(char)*PATH_MAX);
				exit(EXIT_FAILURE);
			}
		
			index_Path++;
		}
	}

	//if user doesn't provide link
	if(new_Size == 0){
		buffer = malloc(sizeof(char*));
		buffer[0] = malloc(sizeof(char)*1);
		strcat(buffer[0],".");
		new_Size++;
	}

	/*
	Finding user's request of printing option:
	Non-recursive options:
	2 - print i option -> inode number
	3 - print l option -> permission, group owner, owner, size in bytes, last modeifed date
	5 - print i & l options 
	
	recursive options:
	4 - print R option -> recursively loop and print all branches of valid directories
	6 - print i & R options
	7 - print l & R options
	9 - print i & l & R option
	*/
	option = test_char[0]*2 + test_char[1]*3 + test_char[2]*4;
	return buffer;
}

//Pre-con: none
//Post-con: manage the information flow of the program
void ls_Admin(int size, char* list[]){
	DIR *dirp;
	struct dirent* dp;
	struct stat temp;
	char** input;
	char new_Path[PATH_MAX];

	//default ls command - print current working directory:
	if(size <= 1){
		dirp = opendir(".");

		while(dirp){
			if((dp = readdir(dirp)) != NULL){
				if( strcmp(dp->d_name,".") != 0 && strcmp(dp->d_name,"..")){
					print_Filename(dp);
					printf("\t");
				}
			}
			else{
				printf("\n");
				closedir(dirp);
				return;
			}
		}
		closedir(dirp);
	} 

	//non-default ls command - print with option and the input directory
	else{
		
		//extract user input
		input = fetch_Userinput(size, list);

		//List all the current file in the current working directory
		if(new_Size >= 2){
			for(int i = 0; i < new_Size; i++){

				//read the file information directly
				memset(&temp, 0, sizeof(struct stat));
				lstat(input[i],&temp);

				if(option == 2 || option == 5 || option == 6 || option == 9)
					print_Ioption(&temp);

				if(option == 3 || option == 5 || option == 7 || option == 9)
					print_Loption(&temp);

				printf("%s",list[index_File[i]]);

				if(S_ISLNK(temp.st_mode)){

					//print l-option
					if(option == 3 || option == 5 || option == 7 || option == 9){
						ssize_t nbytes = readlink(input[i],sym_Link, PATH_MAX);
						if(nbytes != -1)
							printf(" -> %s",sym_Link);
						printf("/");
					}

					//print i-option
					else if(option == 2 || option == 4 || option == 6){
						printf("@  ");
					}

					//otherwise
					else{
						printf("  ");
					}

				}else{
					printf("  ");
				}

				if(option == 3 || option == 5 || option == 7|| option == 9){
					printf("\n");
				}
				else{
					printf("   ");
				}
			}
			printf("\n");
		}
		

		//loop & read information of all valid directory
		for(int i = 0; i < new_Size; i++){

			memset(&temp, 0, sizeof(struct stat));

			//open the directory
			dirp = opendir(input[i]);

			//check - invalid directory
			if(!dirp){
				continue;
			}

			//print the origin path (from user's request)
			printf("%s:\n", input[i]);

			//non-recursive options
			if(option != 4 && option != 6 && option != 7 && option != 9){
				while( (dp = readdir(dirp)) != NULL){

					memset(new_Path, 0, sizeof(char)*PATH_MAX);
					strcat(new_Path, input[i]);
					strcat(new_Path,"/");
					strcat(new_Path, dp->d_name);

					if( strcmp(dp->d_name,".") != 0 && strcmp(dp->d_name,"..")){

						lstat(new_Path, &temp);

						//print-Ioption
						if(option == 2 || option == 5)
							print_Ioption(&temp);

						//print-Loption
						if(option == 3 || option == 5)
							print_Loption(&temp);
					
						print_Filename(dp);

						//print symbolic link
						if(S_ISLNK(temp.st_mode)){
							//print l-option
							if(option == 3 || option == 5){
								ssize_t nbytes = readlink(new_Path,sym_Link, PATH_MAX);
								if(nbytes != -1)
									printf(" -> %s",sym_Link);
								printf("/");
							}
							//print i-option
							else if(option == 2){
								printf("@  ");
							}
							//otherwise
							else{
								printf("  ");
							}
						}else{
							printf("  ");
						}

						if(option == 3 || option == 5 || option == 7 || option ==9)
							printf("\n");
					}			
				}

				//add more option here
				if(option != 4 && option != 6)
					printf("\n");
			}

			//recursive option
			else{
				print_Roption(option, input[i]);
			}

			//end of the loop - check if the directory is not closed
			if(dirp) closedir(dirp);
		}

	}

	//free the entire list of input:
	if(buffer != NULL){
		for(int i = 0; i < new_Size; i++){
			memset(buffer[i], 0, sizeof(char)*PATH_MAX);
			free(buffer[i]);
			buffer[i] = NULL;
		
		}

		free(buffer);
		buffer = NULL;		
	}

	if(index_File != NULL){
		free(index_File);
		index_File = NULL;
	}
	
	memset(new_Path, 0, sizeof(char)*PATH_MAX);

	return;
}