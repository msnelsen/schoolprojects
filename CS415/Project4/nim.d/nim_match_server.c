#include  <stdlib.h>
#include  <unistd.h>
#include	<signal.h>
#include	<errno.h>
#include	<string.h>
#include	<stdio.h>
#include	<sys/types.h>
#include	<sys/socket.h>
#include	<netinet/in.h>
#include	<netdb.h>
#include  <limits.h>


int connection1;
int connection2;
char killer[] = "c\n";

void siginthandler(sig){
	int num;
	num = write(connection2, killer, sizeof(killer));
	num = write(connection1, killer, sizeof(killer));
	exit(0);
}


int main(int argc, char **argv){
	
	int num, n;
	int endFlag = 0;
	char * connection1Str = argv[1];
	char * connection2Str = argv[2];
	char * handle1 = argv[3];
	char * handle2 = argv[4];
	char buffer1[256];
	char buffer2[256];
	char aim[] = "a8888\n";

	
//	printf("handle1: %s, handle2: %s", handle1, handle2);
	
	connection1 = strtol(connection1Str, NULL, 10);
	connection2 = strtol(connection2Str, NULL, 10);
	
	// printf("connection1: %d connection2: %d \n", connection1, connection2);
	// 
	int handler1size = sizeof(handle1); int handler2size = sizeof(handle2);
//	printf("%s %s", handle1, handle2);
	num = write(connection1, handle2, 21);
	num = write(connection2, handle1, 21);

	num = write(connection1, aim, sizeof(aim));
	
	while(1){
	//	printf("Here\n");
		signal(SIGINT, siginthandler);
		n = recv(connection1, buffer1, 255, 0);

		if(n < 0){
			printf("Something went wrong with connection1 recv\n");
			num = write(connection2, killer, sizeof(killer));
			exit(1);
		}
		num = write(connection2, buffer1, 255);

	  if(num < 0){
			printf("error with write to connection2\n");
			num = write(connection1, killer, sizeof(killer));
			exit(1);
	  }

	//	printf("connection1 message: %s\n", buffer1);
		if(buffer1[0] == 'b' || buffer1[0] == 'c'){
			endFlag = 1;
		}
		bzero(buffer1, 256);
		n = recv(connection2, buffer2, 255, 0);

		if(n < 0){
			printf("Something went wrong with connection2 recv\n");
			num = write(connection1, killer, sizeof(killer));
			exit(1);
		}
		num = write(connection1, buffer2, 255);
		if(num < 0){
			printf("error with write to connection1\n");
			num = write(connection2, killer, sizeof(killer));
			exit(1);
	  }

	//	printf("connection2 message: %s\n", buffer2); 
		if(buffer2[0] == 'b' || buffer2[0] == 'c'){
			endFlag = 1;
		}
    bzero(buffer2, 256);
    if(endFlag == 1){
			printf("Game over\n");	
			exit(0);
    }
		//printf("here\n");	
		signal(SIGINT, siginthandler);
	}
	printf("here!\n");
	 
	
}