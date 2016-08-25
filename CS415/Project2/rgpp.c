//Project 2 - rgpp- A grep Post-Processor
//Meade Nelsen
//February 8th - due February 15th, midnight
#define _GNU_SOURCE
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <errno.h>
#define ANSI_COLOR_RED  "\x1b[31m" 
#define ANSI_COLOR_RESET   "\x1b[0m"    //Color usage how to taken from here:
                                      //http://stackoverflow.com/questions/3219393/stdlib-and-colored-output-in-c

//Linked List Structs
typedef struct node{
	char * fileName;
	int lineNumber;
	struct node * next;
    }NODE;

typedef struct linkedlist{
	struct node * head;
	struct node * tail;
	}LINKEDLIST;
	
//Mode Flags
int lineFlag = 0;
int wordFlag = 0;
int bannerFlag = 0;
int numberFlag = 0;

//Globals
char * theWord;
LINKEDLIST * grepList;
int wordBannerCount;

//Function Declarations

LINKEDLIST *llalloc();
LINKEDLIST *push(LINKEDLIST *l, char * fileName, int lineNumber);
NODE *nalloc();
void printList(LINKEDLIST *l);
NODE *pop(LINKEDLIST *l);
int loList(LINKEDLIST *l);

int main (int argc, char *argv[]){
	
	wordBannerCount = 0;
	
	//input handling
	if(argc == 0){
		printf("Needs more Arguments\n");
		exit(1);
	}
	
	if(strcmp(argv[1],"-l") == 0){
		lineFlag = 1;
	}
	else if((strcmp(argv[1], "-w") == 0)){
		wordFlag = 1;
	}else{
		printf("First Argument must be either an 'l' or a 'w'\n");
		exit(1);
	}
	
	if(wordFlag == 1){
		if (argc <= 2){
			printf("Too few arguements \n");
			exit(1);
		}
		theWord = malloc(sizeof(char)*sizeof(argv[2]) + 1); //potential for error based on the size of arg[2] 
		strcpy(theWord, argv[2] );
		//printf("The Word is: %s\n", theWord);
		if(argc > 5){
			printf("Too many arguments!\n");
			exit(1);
		}
		if(argc == 4 || argc == 5){
			if(strcmp(argv[3], "-n") == 0 ){
				numberFlag = 1;
			}
			else if(strcmp(argv[3], "-b") == 0 ){
				bannerFlag = 1;
			}
			if( strcmp(argv[3], "-b")  != 0 && strcmp(argv[3], "-n") != 0 ){
				printf("Incorrect Argument: Needs either a 'b' or an 'n' \n");
				exit(1);
			}	
		}
		if(argc == 5){
			if(strcmp(argv[4], "-n") == 0 && argc == 5){
				numberFlag = 1;
			}
			else if(strcmp(argv[4], "-b") == 0 && argc == 5){
				bannerFlag = 1;
			}
		
			if(argc == 5 && strcmp(argv[4], "-b") != 0 && strcmp(argv[4],"-n") != 0){
				printf("Incorrect Argument: Needs either a 'b' or an 'n'  \n");
				exit(1);
			}  
		}
	}
	
	if(lineFlag == 1){
		if(argc > 4){
			printf("Too many arguments!\n");
		}
		if(argc == 3 || argc == 4){
			if(strcmp(argv[2], "-n") == 0 ){
				numberFlag = 1;
			}
			else if(strcmp(argv[2], "-b") == 0 ){
				bannerFlag = 1; 
			}
			if( strcmp(argv[2], "-b")  != 0 && strcmp(argv[2], "-n") != 0 ){
				printf("Incorrect Argument: Needs either a 'b' or an 'n' \n");
				exit(1);
			}	
		}
		if(argc == 4){
			if(strcmp(argv[3], "-n") == 0 ){
				numberFlag = 1;
			}
			else if(strcmp(argv[3], "-b") == 0 ){
				bannerFlag = 1;
			}
			if( strcmp(argv[3], "-b")  != 0 && strcmp(argv[3], "-n") != 0 ){
				printf("Incorrect Argument: Needs either a 'b' or an 'n' \n");
				exit(1);
			}	
		}
	}
	
//THIS IS ALL GREP READING
	grepList = llalloc();
	char * grepOutput;
	grepOutput = malloc(sizeof(char) * LINE_MAX);
	while(fgets(grepOutput, LINE_MAX, stdin)){
		int colonIndex1 = 0;
		int colonIndex2 = 0;
		int colonCounter = 0; 
		int i = 0;
		// printf("%s\n", grepOutput);
		while(colonCounter < 2){
			if(grepOutput[i] == ':'){
				if(colonCounter == 0){
					colonIndex1 = i;
					// printf("colonIndex1: %d \n", colonIndex1);
				}
				if(colonCounter == 1){
					colonIndex2 = i;
					// printf("colonIndex2: %d \n", colonIndex2);
				}
				colonCounter ++;
			}
			if(grepOutput[i] == '\0'){
				printf("Invalid grep input\n");
				exit(1);
			}
			i++; 
		}
		int j = 0;
		char * fileName = malloc (sizeof(char) * colonIndex1 + 1);
		char * lineNumber = malloc(sizeof(char) * (colonIndex2 - colonIndex1 ) + 1);
		while(j < colonIndex1){
			fileName[j] = grepOutput[j];
			j++;
		}
		int k = j + 1;
		int m = 0;
		while(k < colonIndex2){
			lineNumber[m] = grepOutput[k];
			k++;
			m++;
		}
		
		char *endptr;  //based of man strtol methods
		int lineNumberInt = strtol(lineNumber, &endptr, 10);
		
		grepList = push(grepList, fileName, lineNumberInt);
		free(grepOutput); 

		grepOutput = malloc(sizeof(char) * LINE_MAX);
		free(lineNumber);
	}

//HERE IS THE WORDMODE COUNTER	

	if(wordFlag == 1){
		FILE *fp1;
		NODE *temp = grepList->head;
		temp = temp->next;
		errno = 0;
		fp1 = fopen(temp->fileName, "r");
		if(errno != 0){
			printf("File read error\n");
			exit(-1);
		}
		char * fileInput;
		fileInput = malloc(sizeof(char) * LINE_MAX);
		int lineCounter1 = 1;
		int counter = 2;
		while(counter <= loList(grepList)){
			while(fgets(fileInput, LINE_MAX, fp1)){
				char * string = strcasestr(fileInput, theWord);
				if(string == NULL && temp-> lineNumber == lineCounter1){
					printf("%s WARNING: grep string does not match rgpp string; May cause Garbage Output %s\n", ANSI_COLOR_RED, ANSI_COLOR_RESET);
				}														//Usage for strcasestr and troubleshooting taken from:
				if(string!= NULL){
					wordBannerCount ++;	                                             //http://stackoverflow.com/questions/9935642/how-do-i-use-strcasestr
			        while(string != NULL){
					    string += strlen(theWord);
				    	string = strcasestr(string, theWord);
				        if(string != NULL){

							wordBannerCount ++;
						}	
					}
				}
				if(temp->lineNumber == lineCounter1){
					if(temp->next != NULL){
				    temp = temp->next; 
				}
					counter ++;	
				    
				}
				lineCounter1 ++ ;
			}
			fclose(fp1);
			if(temp->lineNumber > lineCounter1){
				printf("Grep output is wrong; Check file numbers\n");
				exit(-1);
			}
			errno = 0;
			fp1 = fopen(temp->fileName, "r");
			if(errno != 0){
				printf("File read error\n");
				exit(-1);
			}
			lineCounter1 = 1;
			free(fileInput);
			fileInput = malloc(sizeof(char) * LINE_MAX);
				
		}
		fclose(fp1);
		free(fileInput);
	}
	
//HERE BEGINS THE FILE MANIPULATION
	free(grepOutput);
	NODE * temp = pop(grepList);
	free(temp);
	int length = loList(grepList);
	if(grepList->head == NULL){
		printf("No hits \n");
		exit(1);
	}
	
	FILE *fp;
	temp = pop(grepList);
	
	if(bannerFlag == 1  && lineFlag == 1){
		printf("THERE ARE %d LINES THAT MATCH\n\n ", length );
	}
	if(bannerFlag == 1 && wordFlag == 1){
		printf("THERE ARE %d MATCHING WORDS\n\n", wordBannerCount);
	}
	printf("===================%s\n", temp->fileName); 
	fp = fopen(temp->fileName , "r");
	char * fileInput;
	fileInput = malloc(sizeof(char) * LINE_MAX);
	int lineCounter = 1;
	while(grepList->tail != NULL){
		while(fgets(fileInput, LINE_MAX, fp)){
			if(temp != NULL){
				if(lineCounter == temp->lineNumber){
					if(lineFlag == 1){
				    	printf("* ");
			    	}
					free(temp->fileName);
					free(temp);
					temp = pop(grepList);
				}
			}
			if(numberFlag == 1){
				printf("%d: ", lineCounter);
			}
			if(lineFlag == 1){
			    printf("%s",fileInput);
		    }
		    if(wordFlag == 1){
				char * string = strcasestr(fileInput, theWord);
				int j = 0;
				if(string != NULL){
					while(string != NULL){
						int index = strlen(fileInput)- strlen(string);

						while(j < index){
							printf("%c", fileInput[j]);
							j++;
						}
						index = j + strlen(theWord);
						while(j < index){
						    printf(ANSI_COLOR_RED "%c" , fileInput[j]);
							j++;
					    } 
						printf(ANSI_COLOR_RESET);
						string += strlen(theWord);
						string = strcasestr(string, theWord);
					    
					}
					int index=strlen(fileInput);
					while(j<index){
						printf("%c", fileInput[j]);
						j++;
					}
					
				}else{
					printf("%s",fileInput);
				}
		    }
			lineCounter ++;
            free(fileInput);
            fileInput = malloc(sizeof(char) * LINE_MAX);
		}
		fclose(fp);
		errno = 0;
		if(temp == NULL){
			break;
		}
		if(temp->lineNumber > lineCounter){
			printf("Grep input is flawed; check line numbers\n");
			exit(-1);
		}
		fp = fopen(temp->fileName, "r");
		if(errno != 0){
			printf("This file didn't work: %s\n", temp->fileName);
			printf("File open error!!\n");
			exit(-1);
		}
		if(temp == NULL){
			break;
		}
		lineCounter = 1;
		printf("===================%s\n", temp->fileName);
	}
	free(fileInput);
	free(grepList);
	return 0;

}

LINKEDLIST *llalloc(){
	LINKEDLIST *l = (LINKEDLIST *) malloc (sizeof(LINKEDLIST));
	if(l == NULL){
		printf("Malloc Error\n");
		exit(1);
	}
	NODE *n = (NODE *) malloc(sizeof(NODE));
	if(n == NULL){
		printf("Malloc Error\n");
		exit(1);
	}
	n->fileName = "Start";
	n->lineNumber = -1;
	l->head = n;
	l->tail = n;
	return l;
}

NODE *nalloc(){
	NODE *n = (NODE *) malloc(sizeof(NODE));
	if(n == NULL){
		printf("Malloc Error\n");
		exit(1);
	}
	n->fileName = NULL;
	n->lineNumber = -1;
	n->next = NULL;
	return n;
}

LINKEDLIST *push(LINKEDLIST *l, char * fileName, int lineNumber){
	NODE *n = nalloc();
	n->fileName = fileName;
	n->lineNumber = lineNumber;
	l->tail->next = n;
	l->tail = n;
	return l;
}

void printList(LINKEDLIST *l){ 
	NODE * temp = l->head;
	while(temp != NULL){
		printf("File Name: %s Line Number: %d\n", temp->fileName, temp->lineNumber);
		temp = temp->next;
	}
}

NODE *pop(LINKEDLIST *l){ //implementation taken from Prof Lewis's 303 and http://stackoverflow.com/questions/18456118/pop-from-linked-list
		NODE * temp = l->head;		
		if(temp){
			l->head = temp->next;
			temp->next = NULL;
		}
		return temp;
}

int loList(LINKEDLIST *l){
	NODE * temp = l->head;
	int i = 0;
	while(temp != NULL){
		temp = temp->next;
		i++;
	}
	return i;
}




