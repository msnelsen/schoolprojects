#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <limits.h>
#include <string.h>
#include <errno.h>
#include <pthread.h>
#include <time.h>

#define BUFFER_SIZE 20

int numlines;
int maxcounter;
int filedelay;
int threaddelay;
int i;
int o = 0;
int killFlag = 1;
pthread_t th_a, th_b[26];
char* alphabet[27] = {"a","b","c","d","e","f","g","h","i","j","k","l","m","n","o"
      ,"p","q","r","s","t","u","v","w","x","y","z"};
int alphabetIndex = 0;

struct timespec fileTime;
struct timespec threadTime;

typedef struct node{
	char word[2048];
	int count;
	struct node * next;
	}NODE;
	
typedef struct linkedList{
	struct node * head;
	struct node * tail;
	pthread_mutex_t lock;
	}LINKEDLIST;

LINKEDLIST * oddList;
LINKEDLIST * evenList;

LINKEDLIST *llalloc();
LINKEDLIST *insert(LINKEDLIST *l, char * word);
NODE *nmalloc();
void printList(LINKEDLIST *l);
void listHunter(LINKEDLIST *l, int pid);
int isEmpty();
int isFull();

struct megaBuffer{
	pthread_mutex_t lock;
	int readpos, writepos;
	pthread_cond_t notempty;
	pthread_cond_t notfull;
	char ** buffer;
	}MEGABUFFER;
	
struct readerParams {
	int argc;
	char ** argv;
};
	
struct megaBuffer b;
	
static void init(struct megaBuffer *b, int numberLines){
  b->buffer = malloc(numberLines * sizeof(char *));
	int i;
	for(i = 0; i < numberLines; i++){
		b->buffer[i] = malloc(2048 * sizeof(char));
		memset(b->buffer[i], 0, 2048);
	}
	pthread_mutex_init (&b->lock, NULL);
	pthread_cond_init (&b->notempty, NULL);
	pthread_cond_init (&b->notfull, NULL);
	b->readpos = 0;
	b->writepos = 0;
}


static void * reader(void * data);
static void * counter(void * data);
static void put(struct megaBuffer * b, char * line);
void get(struct megaBuffer *b,  char * data);

int main(int argc, char *argv[]){
	
	char numlinesStr[LINE_MAX] = "";
	char maxcounterStr[LINE_MAX] = "";
	char filedelayStr[LINE_MAX] = "";
	char threaddelayStr[LINE_MAX] = "";
	int errno;
	char * endptr;
	
	if (argc < 10){
		printf("Too few arguments\n");
		exit(1);
	}
	i = 1;
	while (i < 9){
		if(strcmp(argv[i],"-b") == 0 || strcmp(argv[i],"-t") == 0 ||
		   strcmp(argv[i],"-d") == 0 || strcmp(argv[i],"-D") == 0){
				printf("Correct argument found!\n");
				if(strcmp(argv[i],"-b") == 0){
					i++;
					if(strcmp(numlinesStr, "") == 0){
						printf("new number of lines\n");
						strcpy(numlinesStr, argv[i]);
						errno = 0;
						numlines = strtol(numlinesStr, &endptr, 10);
						if(errno == ERANGE){
							if(numlines == LONG_MIN){
								printf("Invalid Number: Underflow\n");
								exit(1);
							}else if(numlines == LONG_MAX){
								printf("Invalid Number: Overflow\n");
								exit(1);
							}
						}
						if (*endptr != '\0'){
							printf("Invalid Characters\n");
							exit(1);
						}
						if(numlines <= 0){
							printf("Invalid number of lines");
							exit(1);
						}
					}else{
						printf("Argument used multiple times\n");
						exit(1);
					}
				}else if(strcmp(argv[i],"-t") == 0){
					i++;
					if(strcmp(maxcounterStr, "") == 0){
						printf("new maxcounter\n");
						strcpy(maxcounterStr, argv[i]);
						errno = 0;
						maxcounter = strtol(maxcounterStr, &endptr, 10);
						if(errno == ERANGE){
							if(maxcounter == LONG_MIN){
								printf("Invalid Number: Underflow\n");
								exit(1);
							}else if(maxcounter == LONG_MAX){
								printf("Invalid Number: Overflow\n");
								exit(1);
							}
						}
						if (*endptr != '\0'){
							printf("Invalid Characters\n");
							exit(1);
						}
						if(maxcounter <= 0 || maxcounter > 26){
							printf("Invalid maximum number of counters\n");
							exit(1);
						}
					}else{
						printf("Argument used multiple times\n");
						exit(1);
					}
				}else if(strcmp(argv[i],"-d") == 0){
					i++;
					if(strcmp(filedelayStr, "") == 0){
						printf("new filedelay\n");
						strcpy(filedelayStr, argv[i]);
						errno = 0;
						filedelay = strtol(filedelayStr, &endptr, 10);
						if(errno == ERANGE){
							if(filedelay == LONG_MIN){
								printf("Invalid Number: Underflow\n");
								exit(1);
							}else if(filedelay == LONG_MAX){
								printf("Invalid Number: Overflow\n");
								exit(1);
							}
						}
						if (*endptr != '\0'){
							printf("Invalid Characters\n");
							exit(1);
						}
						if(filedelay < 0 ){
							printf("Invalid file delay number\n");
							exit(1);
						}
					}else{
						printf("Argument used multiple times\n");
						exit(1);
					}
				}else if(strcmp(argv[i],"-D") == 0){
					i++;
					if(strcmp(threaddelayStr, "") == 0){
						printf("new threaddelay\n");
						strcpy(threaddelayStr, argv[i]);
						errno = 0;
						threaddelay = strtol(threaddelayStr, &endptr, 10);
						if(errno == ERANGE){
							if(threaddelay == LONG_MIN){
								printf("Invalid Number: Underflow\n");
								exit(1);
							}else if(threaddelay == LONG_MAX){
								printf("Invalid Number: Overflow\n");
								exit(1);
							}
						}
						if (*endptr != '\0'){
							printf("Invalid Characters\n");
							exit(1);
						}
					}else{
						printf("Argument used multiple times\n");
						exit(1);
					}
					if(threaddelay < 0){
						printf("Invalid thread delay\n");
						exit(1);
					}
				}else{
					printf("Incorrect argument\n");
					exit(1);
				}
		}else{
		//	printf("%d\n", i);
			

			  printf("Incorrect argument\n");
			  exit(1);
		}
		i++;
	}
	printf("Number of lines: %d, max counters: %d \n file delay: %d, thread delay %d\n",
		numlines, maxcounter, filedelay, threaddelay);

	
	init(&b, numlines);
	
	double ftime= (double) filedelay / 1000;
	double ttime = (double) threaddelay /1000;
	fileTime.tv_sec = (time_t) ftime;
	fileTime.tv_nsec = (long) ((ftime - threadTime.tv_sec) * 1e+9);
	threadTime.tv_sec = (time_t) ttime;
	threadTime.tv_nsec = (long) ((ttime - threadTime.tv_sec) * 1e+9);

	void *retval;
	struct readerParams readParams;
	readParams.argc = argc;
	readParams.argv = argv;
	pthread_create (&th_a, NULL, reader, &readParams);
	 
	
	pthread_join (th_a, &retval);
	
	int l = 0;
//	printf("%d\n", th_b[l]);
	while(l < alphabetIndex){
		
		pthread_join (th_b[l], &retval);
		printf("terminated: %d\n", th_b[l]);
		l++;
	}
	
	printf("------Odd List-------");
	printList(oddList); 
	printf("------Even List-------"); printList(evenList);
	free(oddList);
	free(evenList);
  
	
	
}

static void * reader(void *data){
	
	char file[4098];
	
	struct readerParams *readParams = data;
	oddList = llalloc();
	evenList = llalloc();
	printf("%d, %d\n", i ,  readParams->argc);
	char textline[2048];
	char pthreadname[40];
	struct megaBuffer * c = &b;
	int created = 0;
	while(i < readParams->argc){
		strcpy(file, readParams->argv[i]);
		printf("file: %s\n", file);
		i++;
		FILE * f = fopen(file, "r");
		if(f == NULL){
			printf("File does not exist\n");
			exit(1);
		}
		int j = 1;

		printf("Pre-reading\n");

		while(fgets(textline, 2048, f) != NULL){
		//	printf("Stuck in put\n");
		 // if(isFull() == 1){
	  		put(&b, textline);
	   // }
			j++;
			bzero(textline, 0);
			
			
			if(isFull()  == 0 && created  < maxcounter){
				
			//		printf("%d, %d\n", alphabetIndex, maxcounter);
				int y = 0;
			//	printf("prething: %d\n", isFull());

				if(isFull() == 0){
			//		printf("here\n");
				  
					pthread_create (&th_b[created], NULL, counter, 0);
					created ++;
					while(isFull() == 0){
						
						nanosleep(&threadTime, &threadTime); 
					}
			//		printf("out of reader wait\n");
			//		pthread_cond_signal(&b.notempty);
				//	pthread_mutex_unlock (&b.lock);
					

				}
			}
			nanosleep(&fileTime, &fileTime);
		}
	}

	killFlag = 0;
	pthread_cond_signal(&b.notempty);
	pthread_mutex_unlock (&b.lock);
	return NULL; 
}

static void * counter(void*data){
	char array[2048];
	char word[2048];
	char pthreadname[40];
	//printf("%s\n", alphabet[alphabetIndex]);
	int rc;
  rc=	pthread_setname_np(pthread_self(), alphabet[alphabetIndex]);
	if(rc != 0){
		printf("setname error\n");
	}
//	printf("%d", sizeof(pthreadname));  
	rc = pthread_getname_np(pthread_self(), pthreadname, 40);
	if(pthreadname == NULL){
		printf("Trouble\n");
	}
	if(rc != 0){
		printf("getname error\n");
		perror("getname:: ");
		exit(1); 
	}
	printf("named thread: %s\n", pthreadname);
	alphabetIndex++;
	int k = 0;
	while(killFlag == 1 ){
		if(isEmpty() == 1){
		  get(&b, array);
	  }
	  
		nanosleep(&threadTime, &threadTime);
		strtok(array, "\n");

//		printf("%c", pthreadname);
		if(strcmp(array, "") != 0){
		  //printf("%d %s: Data from buffer : %s\n", pthread_self(), pthreadname,array );
	  }
	  
		char*  m = strtok(array, " \t"); 
		int length;
		while(m != NULL){
	//		printf("%s ", m);
			
			if (m != NULL){
				length = strlen(m);
				if(length % 2 == 1){
					insert(oddList, m);
				}else{
					insert(evenList, m);
				}
			}
			m = strtok(NULL, " \t");
			
		}
	  
		bzero(array, sizeof(array));
		k++;
	}
	
	while(isEmpty()==1){
		//printf("%d\n", isEmpty(&b));
		get(&b, array);
		
		if(strcmp(array, "") != 0){
		 // printf("%d %s: Special Data from buffer : %s", pthread_self(), pthreadname,array );
	  }
		strtok(array, "\n");
		//printf("ERINS SPECIALS ARRAY: %s\n", array);
	  char*  m = strtok(array, " \t");
		int length; 
		while(m != NULL){
			//printf("%s ", m);
			if (m != NULL){
				length = strlen(m);
				if(length % 2 == 1){
				//	printf("Special %s ", pthreadname);
					insert(oddList, m);
				}else{
			//		printf("Special %s ", pthreadname);
					insert(evenList, m);
				}
		  }
			m = strtok(NULL, " \t");
		//	printf("%s \n", m);	 
		//	printf("array: %s\n", array);  
		}
	//	printf("out of the loop\n");
		  bzero(array, sizeof(array));
		
	}

} 

static void put(struct megaBuffer * b, char * line){ //NUMLINES INDEXING!!
	pthread_mutex_lock (&b->lock);
//	printf("%s", line);

	while(isFull() == 0 && killFlag == 1){
	//	printf("put wait!!\n");
		pthread_cond_wait(&b->notfull, &b->lock);
	}
	if(b->buffer[b->writepos] != NULL){
	 // printf("%s\n", b->buffer[b->writepos]);
	  bzero(b->buffer[b->writepos], 2048);
	}
	
	strcpy(b->buffer[b->writepos], line);
	b->writepos ++;
	if(b->writepos >= numlines){
	//	printf("Write pos now is 0\n");
		b->writepos = 0;
	}
	
	pthread_cond_signal(&b->notempty);
	pthread_mutex_unlock (&b->lock);
}

void get(struct megaBuffer * b, char * data){
	pthread_mutex_lock(&b->lock);
	while(isEmpty() == 0 && killFlag == 1){
		printf("get wait");
		pthread_cond_wait (&b->notempty, &b->lock);
	}


	strcpy(data, b->buffer[b->readpos]);
	bzero(b->buffer[b->readpos], 2048);
	b->readpos++;

	if(b->readpos >= numlines){
	//	printf("readpos is now 0\n");
		b->readpos  = 0;
	}
	pthread_cond_signal(&b->notfull);
	pthread_mutex_unlock(&b->lock);

}

LINKEDLIST *llalloc(){
	LINKEDLIST *l = (LINKEDLIST *) malloc (sizeof(LINKEDLIST));
	if(l == NULL){
		printf("Malloc Error\n");
		exit(1);
	}
	pthread_mutex_init (&l->lock, NULL);
	NODE *n = (NODE *) malloc(sizeof(NODE));
	if(n == NULL){
		printf("Malloc Error\n");
		exit(1);
	}
	strcpy(n->word, "");
	l->head = n;
	l->tail = n;
	return l;
}

NODE *nmalloc(){
	NODE *n = (NODE *) malloc(sizeof(NODE));
	if(n == NULL){
		printf("Malloc Error\n");
		exit(1);
	} 
	n->count = 1;
	n->next = NULL;
	return n;
}

LINKEDLIST *insert(LINKEDLIST *l, char * word){
	pthread_mutex_lock(&l->lock);
	NODE *n = nmalloc();
	NODE *temp = l->head;
	NODE *prev = l->head;
	
//	NODE *prev = l->head;
	int insertedFlag = 0;	
	strcpy(n->word, word);
	while(temp != NULL){
		 if(temp != NULL && strcasecmp(n->word, temp->word) > 0){ // if new words word is lower in the alphabet ie if its n is dog after t iscat
		// 	temp = temp->next;
		//	printf("Greater than\n");
		 }
		// 
		if(temp != NULL && strcasecmp(n->word, temp->word) < 0 ){//
			//printf("less than\n"); 
			prev->next = n;
			n->next = temp;
			insertedFlag = 1;
			break;	
		 }
		if(strcasecmp(n->word, temp->word) == 0){
			temp->count ++;
			insertedFlag = 1;
			break;
		}
		prev = temp;
		temp = temp->next;
	}
	if(insertedFlag == 0){
	  l->tail->next = n;
	  l->tail = n;
  }
	pthread_mutex_unlock(&l->lock);
	return l;
}

void printList(LINKEDLIST *l){ 
	NODE * temp = l->head;
	while(temp != NULL){
		printf("Word:%s Counter:%d\n", temp->word, temp->count);
		temp = temp->next;
	}
}

int isEmpty(){
	int i = 0;
	int toReturn = 0;
	while(i<numlines){ 
		if (b.buffer[i][0] != '\0'){
			return(1);
		}
		i++;
	}
	return(0);
}

int isFull(){
	int i = 0;
	int toReturn = 0;
	while(i<numlines){
	//	printf("%s\n", b.buffer[i]);
		if (b.buffer[i][0] == '\0'){
			return(1);
		}
		i++;
	}
	return(0);
}