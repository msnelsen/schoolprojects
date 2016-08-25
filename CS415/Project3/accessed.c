#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <limits.h>
#include <ctype.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/sysmacros.h>
#include <signal.h>
#include <errno.h>
#include <time.h>

int main (int argc, char *argv[], char *envp[]){
	struct stat info;
	long int days;
	int modeFlag = 0;
	// Input Checking Section
	if(argc != 2){
		printf("Invalid number of arguments for accessed program\n");
		exit(-1);
		}
	else{
		errno = 0;
		char * endptr;
		days = strtol(argv[1], &endptr, 10);
		if(errno == ERANGE){
			if(days == LONG_MIN){
				printf("Invalid Number: Underflow\n");
				exit(1);
			}else if(days == LONG_MAX){
				printf("Invalid Number: Overflow\n");
				exit(1);
			}
		}
		if (*endptr != '\0'){
			printf("Invalid Characters Here\n");
			exit(1);
		}
	}
	long int seconds = days * 86400;
	if(days > 0){
		modeFlag = 1;
	}else if(days < 0){
		modeFlag = 0;
		seconds = seconds * -1;
	}else{
		printf("Invalid Number :  0 \n");
		exit(-1);
	}
	char* fileName = malloc(sizeof(char) * LINE_MAX);
	long int * arraySTINO = malloc(sizeof(long int));
	long int * arraySTDEV = malloc(sizeof(long int));
	int arrayLength = 0;
	while(scanf("%s", fileName) != EOF){
		stat(fileName, &info);
		if (S_ISREG(info.st_mode) == 0){
			//printf("%s: Not a regular file\n", fileName);
		}else{
			int k = 0;
			int countedFlag = 0;
			while(k < arrayLength){
				if(info.st_dev == arraySTDEV[k] && info.st_ino == arraySTINO[k]){
					countedFlag = 1;
				}
				k++;
			}
			if(countedFlag != 1){
				arraySTINO[arrayLength] = info.st_ino;
				arraySTDEV[arrayLength] = info.st_dev;
				arrayLength ++;
				arraySTINO = (long int *) realloc(arraySTINO, (arrayLength + 1)* sizeof(long int));
				arraySTDEV = (long int *) realloc(arraySTDEV, (arrayLength + 1)* sizeof(long int));
				time_t accessedTime = info.st_atime;
				time_t currentTime = time(NULL);
				time_t timeSince = currentTime - accessedTime;
				if(modeFlag == 1){
					if(timeSince > seconds){
						printf("%s\n", fileName);
					}
				}else if(modeFlag == 0){
					if(timeSince < seconds){
						printf("%s\n", fileName);
					}
				}
			}
		}
	}
	exit(0);
	
	
}