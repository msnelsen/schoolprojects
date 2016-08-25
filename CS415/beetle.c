/**
*The Beetle and the Boiling Oil
*CS 415
*By Meade Nelsen
*January 27, 2015
**/

#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
#include <math.h>
#include <errno.h>


int main (int argc, char *argv[]){
	long int beetleCount, count, sideSize;
	int timer = 0;
	char *endptr;
	
	float dX, dY, y, x, rando, average;
	if (argc != 3){
		printf("Incorrect number of arguements\n");
		exit(1);
	}else{
		errno = 0;
		sideSize = strtol(argv[1], &endptr, 10);
		if(errno == ERANGE){
			if(sideSize == LONG_MIN){
				printf("Invalid Number: Underflow\n");
				exit(1);
			}else if(sideSize == LONG_MAX){
				printf("Invalid Number: Overflow\n");
				exit(1);
			}
		}
		if (*endptr != '\0'){
			printf("Invalid Characters\n");
			exit(1);
		}
		errno = 0;
		beetleCount = strtol(argv[2], &endptr, 10);
		if(errno == ERANGE){
			if(beetleCount == LONG_MIN){
				printf("Invalid Number: Underflow\n");
				exit(1);
			}else if( beetleCount == LONG_MAX){
				printf("Invalid Number: Overflow\n");
				exit(1);
			}
		}
		if (*endptr != '\0'){
			printf("Invalid Characters\n");
			exit(1);
		}
		
		if(sideSize<=0 || beetleCount<= 0){
			printf("Invalid Number: Must be positive, non-zero\n");
			exit(1);
		}
	}
	
	
	while(count < beetleCount){
		x = sideSize / 2;
		y = sideSize / 2;
		while(x <= sideSize && y <= sideSize && x >= 0 && y >= 0){
			rando = random() % 360;
			dY = sinf(rando);
			dX = cosf(rando);
			x = x+dX;
			y = y+dY;
			timer = timer + 2;

		}
		count ++;
	}
	average = timer / count;
	printf("%lu by %lu square, %lu beetles, mean beetle lifetime %.1f\n", sideSize, sideSize, beetleCount, average);
	return 0;
}