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

int main (int argc, char *argv[], char *envp[]){
	int totalSize = 0;
	char * kilobytes = getenv("UNITS");
	char * tstall = getenv("TSTALL");
	char * tmom = getenv("TMOM");
	// printf("%s", tmom);
	// printf("made it to the top!\n");
	
	
	if(tstall != NULL){
		long int sleeper = strtol(tstall, NULL, 10);
		if(sleeper>0){
			sleep(sleeper);
		}
	}
	int kiloFlag = 0;
	struct stat info;
	if(kilobytes != NULL){
	if(strcmp(kilobytes, "k") == 0 || strcmp(kilobytes, "K") == 0){
		//printf("%s\n", "Kilobytes");
		kiloFlag = 1;
	}
    }


	char* fileName = malloc(sizeof(char) * LINE_MAX);
	long int * arraySTINO = malloc(sizeof(long int)*2 );
	long int * arraySTDEV = malloc(sizeof(long int)*2);
	int arrayLength = 0;


	while(scanf("%s", fileName) != EOF){
		//printf("%s", fileName);

		stat(fileName, &info);
		
		if (S_ISREG(info.st_mode) == 0){
			//printf("File isn't regulation\n");
		}else{
		//	printf("(device,i_number)=(%d/%d,%ld)\n", major(info.st_dev), minor(info.st_dev), (long) info.st_ino);
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
				arrayLength++;
				totalSize = totalSize + info.st_size;
				arraySTINO = realloc(arraySTINO, (arrayLength + 1)* sizeof(long int));
				arraySTDEV = realloc(arraySTDEV, (arrayLength + 1)* sizeof(long int));
			//	printf("%d\n", totalSize); 
			}
		}
	}
	if(kiloFlag == 1){
		totalSize = totalSize * .001;
		printf("%dkB\n", totalSize);
	}else{
	printf("%d\n", totalSize);
	}
	
//Termination protocol
	
	if(tmom != NULL){
		long int pid = strtol(tmom, NULL, 10);
		if(pid > 0){
			kill(pid,SIGUSR1);//look at this later
			//printf("SIGUSR1 sent to %ld\n", pid);
		}
	} 
	
	// printf("Made it too the end of this file\n");
	exit(1);
	
}



