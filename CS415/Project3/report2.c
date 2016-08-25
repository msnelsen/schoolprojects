#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <limits.h>
#include <string.h>
#include <signal.h>
#include <sys/sysmacros.h>

volatile sig_atomic_t stopFlag = 1;

void 
usr1handler(int sig){
	stopFlag = 0;
	signal(sig, usr1handler);
} 
int main(int argc, char *argv[], char * envp[]){
	
	
	//Input checking
	
	int kiloFlag = 0;	
	char * endptr;
	char * dayString;
	long int sleepSeconds;
	char * sleepString;
	long int days;
	if(argc < 2){
		printf("Invalid number of arguments\n");
	}
	if(argc >= 2){
		errno = 0;
		char * endptr; 
		days = strtol(argv[1], &endptr, 10);
		printf("%d\n", days);
		dayString = malloc(sizeof(argv[1]));
		strcpy(dayString, argv[1]);
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
		if(days <= 0){
			printf("First argument must be positive\n");
			exit(1);
		}	
	}
	
	if(argc == 3){
		if(strcmp(argv[2], "-k") != 0){
			printf("Incorrect arguments\n");
			exit(1);
		}
		else{
			kiloFlag = 1;
			printf("kilobytes mode\n");
		}
	}
		
	if(argc == 4){
		if(strcmp(argv[2], "-k") == 0){
			printf("Incorrect argument\n");
		}
		
		if(strcmp(argv[2], "-d") == 0){
			errno = 0;
			char * endptr;
			sleepSeconds = strtol(argv[3], &endptr, 10);
			sleepString = malloc(sizeof(argv[3]));
			strcpy(sleepString, argv[3]);
			if(errno == ERANGE){
				if(sleepSeconds == LONG_MIN){
					printf("Invalid Number: Underflow\n");
					exit(1);
				}else if(sleepSeconds == LONG_MAX){
					printf("Invalid Number: Overflow\n");
					exit(1);
				}
			}
			if (*endptr != '\0'){
				printf("Invalid Characters\n");
				exit(1);
			}
			if(sleepSeconds <= 0){
				printf("Number after -d must be positive\n");
				exit(1);
			}
		}
	}
	
	
	if(argc == 5){
		if(strcmp(argv[2], "-k") == 0){
			kiloFlag = 1;
			printf("kilobyte mode\n");
			if(strcmp(argv[3], "-d") != 0){
				printf("Incorrect arguments\n");
				exit(1);
			}else{
				errno = 0;
				char * endptr;
				sleepSeconds = strtol(argv[4], &endptr, 10);
				sleepString = malloc(sizeof(argv[4]));
				strcpy(sleepString, argv[4]);
				if(errno == ERANGE){
					if(sleepSeconds == LONG_MIN){
						printf("Invalid Number: Underflow\n");
						exit(1);
					}else if(sleepSeconds == LONG_MAX){
						printf("Invalid Number: Overflow\n");
						exit(1);
					}
				}
				if (*endptr != '\0'){
					printf("Invalid Characters\n");
					exit(1);
				}
				if(sleepSeconds <= 0){
					printf("Number after -d must be positive\n");
					exit(1);
				}
			}
		}
		
		if(strcmp(argv[2], "-d") == 0){
			errno = 0;
			char * endptr;
			sleepSeconds = strtol(argv[3], &endptr, 10);
			sleepString = malloc(sizeof(argv[3]));
			strcpy(sleepString, argv[3]);
			if(errno == ERANGE){
				if(sleepSeconds == LONG_MIN){
					printf("Invalid Number: Underflow\n");
					exit(1);
				}else if(sleepSeconds == LONG_MAX){
					printf("Invalid Number: Overflow\n");
					exit(1);
				}
			}
			if (*endptr != '\0'){
				printf("Invalid Characters\n");
				exit(1);
			}
			if(sleepSeconds <= 0){
				printf("Number after -d must be positive\n");
				exit(1);
			}
			if (strcmp(argv[4], "-k") != 0){
				printf("Incorrect arguments\n");
				exit(1);
			}else{
				kiloFlag = 1;
				printf("kilobyte mode\n");
			}
		}
	}
	
	if(argc>5){
		printf("Too many arguments\n");
		exit(1);
	}
	
	
	
	//Here begins the Greatest Battle of Our Time. 
	pid_t pID1; pid_t pID2; pid_t pID3; pid_t pID4; 
	long int pIDA = getpid();
	//printf("%lu\n", pIDA);
	char * pIDAstring = malloc(sizeof(char) * 100);
	sprintf(pIDAstring, "%d", pIDA);
	char units[105] = "UNITS=";
	char tstall[105] = "TSTALL=";
	if(sleepString != NULL){
		strcat(tstall, sleepString);
	}
	char tmom[105] = "TMOM=";
	
	strcat(tmom, pIDAstring);
	//printf("%s\n", tmom);
	int p2a1[2], a12t1[2], t12p[2];
	int p2a2[2], a22t2[2], t22p[2];
	pipe(p2a1); pipe(a12t1); pipe(t12p);
	pipe(p2a2); pipe(a22t2); pipe(t22p);
	int STDIN_COPY1 = dup(STDIN_FILENO);
	int STDIN_COPY2 = dup(STDIN_FILENO);
	int STDOUT_COPY1 = dup(STDOUT_FILENO);
	int STDOUT_COPY2 = dup(STDOUT_FILENO);

	int status;
	if(pID1 = fork() == 0){
		//printf("Forking 1\n");
		close(p2a1[1]); 
		dup2(STDIN_COPY1, STDIN_FILENO);
		dup2(p2a1[0], STDIN_COPY1);
		close(p2a1[0]);
		char * a[3] = {"accessed", dayString, NULL};
		char* e[] = {NULL};
		dup2(a12t1[1], STDOUT_FILENO);
		close(a12t1[1]); 
		execve("accessed", a, e);
		fflush(stdout);
		perror("parent");
		exit(1);
	}

	if(pID2 = fork() == 0){
		//printf("Forking 2\n"); 
		STDIN_COPY1 = dup(STDIN_FILENO);
		dup2(a12t1[0], STDIN_FILENO); 
		close(a12t1[0]);
		close(a12t1[1]);
		char * a[] = {NULL};
		char * e[2] = {tstall, NULL};
		dup2(t12p[1], STDOUT_FILENO);
		close(t12p[1]);
		execve("totalsize", a, e); 
		perror("parent");
		exit(1);
	}
	
	if(pID3 = fork() == 0){
		//printf("Forking 3\n");
		close(p2a2[1]);
		dup2(STDIN_COPY2, STDIN_FILENO);
		dup2(p2a2[0], STDIN_COPY2);
		close(p2a2[0]);
		char minus[5] = "-";
		strcat(minus, dayString);
		char * a[3] = {"accessed", minus, NULL};
		char * e[] = {NULL};
		dup2(a22t2[1], STDOUT_FILENO);
		close(a22t2[1]);
		execve("accessed", a, e);
		fflush(stdout);
		perror("parent");
		exit(1);
	}
	
	if(pID4 = fork() == 0){
		//printf("Forking 4 \n");
		STDIN_COPY2 = dup(STDIN_FILENO);
		dup2(a22t2[0], STDIN_COPY2);
		close(a22t2[0]);
		char * a[] = {NULL};
		char * e[3] = {tmom, tstall, NULL};
		dup2(t22p[1], STDOUT_FILENO);
		close(t22p[1]);
		execve("totalsize", a, e);
		perror("parent");
		exit(1);
	}
	
	
	signal(SIGUSR1, usr1handler);
	while(stopFlag){
		sleep(1);
		write(1, "*", 1);
		
	}
	close(t12p[1]); close(t22p[1]);
	//printf("here\n");
	int val1 = 0; int val2 = 0;
	//read(t12p[0], &val1, sizeof(int));
	read(t22p[0], &val2, sizeof(int));
	close(t22p[0]);
	printf("\nA total of %d bytes are in regular files not accessed for %ld days\n", val1, days);
	printf("---------\n");
	printf("A total of %d bytes are in regular files accessed within %ld days\n", val2, days);

	exit(0);
	

	
	
}