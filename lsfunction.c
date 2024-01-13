//#########################################################################################
//###							Other related functions									###	
//###			getAndPrintGroup - getAndPrintUserName - print_Ioption					###
//###				print_Loption - print_Filename - print_Roption						###
//###																					###
//#########################################################################################

#include "lsfunction.h"

//Source: instructor - start

//Pre-con: get the valid gid_t variable
//Post-con: print the group ID - string
void getAndPrintGroup(gid_t grpNum) {
	
	struct group *grp;
	
	grp = getgrgid(grpNum);  

	if (grp) {
		printf("%s\t",grp->gr_name);
	}
}

//Pre-con: get the valid uid_t variable
//Post-con: print the user ID - string
void getAndPrintUserName(uid_t uid) {
	
	struct passwd *pw = NULL;
	pw = getpwuid(uid);

	if (pw) {
		printf("%s\t",pw->pw_name);
	}
}

//Source: instructor - end

//Pre-con: get the valid file - struct stat*
//Post-con: print Inode number
void print_Ioption(struct stat* file){

	if(file != NULL){
		//print inode	
		printf("%ld  ", (long)file->st_ino);
		//file name will be printed outside
	}
	return;
}

//Pre-con: get the valid file - struct stat*
//Post-con: print all information in order: permission - hardlink
//owner - group owner - size of file in bytes - time 
void print_Loption(struct stat* file){

	//collect the last modified time
	char buffer[26];
	memset(buffer, '\0', 26*sizeof(char));
	struct tm* date_time = malloc(sizeof(struct tm));

	//format the time for printing - MMM DD YYYY HH:mm
	localtime_r(&file->st_mtime, date_time);	
	strftime(buffer, 26, "%b %d %Y %H:%M", date_time);

	if(file != NULL){

		//print permission:

		//Source: Stack Overflow - start
		printf( (S_ISDIR(file->st_mode)) ? "d" : "-");
		printf( (file->st_mode & S_IRUSR) ? "r" : "-");
		printf( (file->st_mode & S_IWUSR) ? "w" : "-");
		printf( (file->st_mode & S_IXUSR) ? "x" : "-");
		printf( (file->st_mode & S_IRGRP) ? "r" : "-");
		printf( (file->st_mode & S_IWGRP) ? "w" : "-");
		printf( (file->st_mode & S_IXGRP) ? "x" : "-");
		printf( (file->st_mode & S_IROTH) ? "r" : "-");
		printf( (file->st_mode & S_IWOTH) ? "w" : "-");
		printf( (file->st_mode & S_IXOTH) ? "x" : "-");
		printf("  ");
		//Source: Stack Overflow - end

		//print number of hard-link point to the file
		printf("%ld  ", (long)file->st_nlink);

		//print file owner & group owner
		getAndPrintUserName(file->st_uid);
		getAndPrintUserName(file->st_gid);

		//print size of file in bytes
		printf("%ld\t", file->st_size);

		//print last time - file was modified
		printf("%s   ", buffer);

		//file name will be printed outside
	}
	
	if(date_time != NULL){
		free(date_time);
		date_time = NULL;
	}
	return;
}


//Pre-con: get the valid directory - struct dirent*
//Post-con: print name of the file
void print_Filename(struct dirent* directory){
	
	if(directory != NULL){
		printf("%s", directory->d_name);	
	}
	return;
}


//Pre-con: get the valid path - char*
//Post-con: recursively loop through all the avalaible path - print according to requirement
void print_Roption(int option, char* path){
	DIR* dirp ;
	struct dirent* dp;
	struct stat temp;
	char* new_Path = malloc(sizeof(char)*PATH_MAX);
	char symbolic[PATH_MAX];
	char symlink[PATH_MAX];

	memset(&temp, 0, sizeof(stat));
	dirp = opendir(path);

	//Base case - the path is not a ft4ile
	if(dirp == NULL){
		return;
	} 

	//1st loop to print all the directory:
	while( (dp = readdir(dirp)) != NULL ){
		//get the path for each file
		memset(symbolic, 0, sizeof(char)*PATH_MAX);
		memset(new_Path, 0, sizeof(char)*PATH_MAX);
		strcpy(new_Path,path);
		strcat(new_Path,"/");
		strcat(new_Path, dp->d_name);

		if( strcmp(dp->d_name,".") != 0 && strcmp(dp->d_name,"..")){
			lstat(new_Path,&temp);

			if(option == 6 || option == 9)
				print_Ioption(&temp);			//function print -l command

			if(option == 7 || option == 9)
				print_Loption(&temp);

			print_Filename(dp);					//function print filename

			//check if it is a symbolic
			if(S_ISLNK(temp.st_mode)){
				if(option == 7 || option == 9){
					ssize_t nbytes = readlink(new_Path, symbolic, PATH_MAX);
					if(nbytes != -1)
						printf(" -> %s",symbolic);
					printf("/");
				}
				//print i-option
				else if(option == 6){
					printf("@  ");
				}
				//otherwise
				else{
					printf("  ");
				}
			}else{
				printf("  ");
			}

			//add more option here
			if(option != 4 && option != 6)
				printf("\n");

			if(option == 4 || option == 6)
				printf("\t");
		}
	}
	printf("\n");
	printf("\n");
	memset(&temp, 0, sizeof(stat));			//reset the temp
	

	rewinddir(dirp);						//reset the pointer dirp to the head
	while((dp = readdir(dirp)) != NULL){
		
		//get the path for each file
		memset(symlink, 0, sizeof(char)*PATH_MAX);
		memset(symbolic, 0, sizeof(char)*PATH_MAX);
		memset(new_Path, 0, sizeof(char)*PATH_MAX);
		strcpy(new_Path,path);
		strcat(new_Path,"/");
		strcat(new_Path, dp->d_name);
		
		//read the file with the new path
		lstat(new_Path, &temp);		
		
		//if the path is symbolic link
		if(S_ISLNK(temp.st_mode)){
			continue;
		}

		//check if current "." or parent - ".."
		if( strcmp(dp->d_name,".") != 0 && strcmp(dp->d_name,"..")){

			//if the file is directory - yes then execute
			if(S_ISDIR(temp.st_mode)){	

				printf("%s:\n", new_Path);
								
				//recursive through all the path
				print_Roption(option, new_Path);
			
			}
			
		}

		
	}
	closedir(dirp);
	if(new_Path != NULL){
		free(new_Path);
		new_Path = NULL;
	}
	return;
}
