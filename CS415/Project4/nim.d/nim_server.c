/************************************************************************\
* 			  NIMSERVER.C       			         *
* Just bind an address to a socket, wild card for host, port 0 to ask    *
* for any unallocated port. Then output addressing info.                 *
* 								         *
* MEADE NELSEN							         *
* March 23, 2015 						         *
* 								         *
\************************************************************************/

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <signal.h>

void printsin(struct sockaddr_in*, char*, char*);

char handlerMsg[] = {"Please input a handle, no more than 20 characters long: \n"};
pid_t pid1;
int i;
int passwordFlag = 0;
char password[40];
char guestPassword[40];
char yes[2] = "y";
char no[2] = "n";

typedef struct match{
	char gameOne[22];
	char gameTwo[22];
	pid_t pid;
	int flag;
	struct match * next;
	}MATCH;
	
typedef struct linkedList{
	struct match * head;
	struct match * tail;
	}LINKEDLIST;
	
LINKEDLIST * matchList;

LINKEDLIST *llalloc();
LINKEDLIST *push(LINKEDLIST *l, char * gameOne);
MATCH *mmalloc();
void printList(LINKEDLIST *l);
void listHunter(LINKEDLIST *l, int pid);

void usr2handler(int sig){
	printf("user 2 recieved\n");
	int a  = remove("file.txt");
	if(a< 0){
		perror("Remove");
	}
	int j = 0; pid_t pid2;
	while((pid2 = wait3(NULL, WNOHANG, NULL)) && j < i){
		printf("%d\n", pid2);
		listHunter(matchList, pid2); 
	//	printList(matchList);
		j++;
		i = i - 1;
	}
	signal(sig, usr2handler);
	exit(0);
}

void siginthandler(sig){
	printf("sigint recieved\n");
	int a = remove("file.txt");
	if(a< 0){
		perror("Remove");
	}
	int j = 0; pid_t pid2;
	while((pid2 = wait3(NULL, WNOHANG, NULL)) && j < i){
		printf("%d\n", pid2);
		listHunter(matchList, pid2); 
	//	printList(matchList);
		j++;
		i = i - 1;
	}
	signal(sig, siginthandler);
	exit(0);	
}

int main(int argc, char ** argv)
{
	signal(SIGINT, siginthandler);
	if(argc == 2){
		strcpy(password, argv[1]);
		passwordFlag = 1;
	}
	if(argc > 2){
		printf("Too many arguments\n");
		exit(1);
	}
//	printf("Password is %s\n", password);
	
	
//HERE BE DATAGRAM SOCKETS

	matchList = llalloc();
	int dgram_fd, dgram_ecode;
	socklen_t dgram_size;
	struct sockaddr_in *dgram_addr;
	struct addrinfo dgram_hints, *dgram_addrlist;
	
	memset(&dgram_hints, 0, sizeof(dgram_hints));
	dgram_hints.ai_family = AF_INET; dgram_hints.ai_socktype = SOCK_DGRAM;
  dgram_hints.ai_flags = AI_NUMERICSERV | AI_PASSIVE; dgram_hints.ai_protocol = 0;
  dgram_hints.ai_canonname = NULL; dgram_hints.ai_addr = NULL;
	dgram_hints.ai_next = NULL; 

  dgram_ecode = getaddrinfo(NULL, "0", &dgram_hints, &dgram_addrlist);
  if (dgram_ecode != 0) {
    fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(dgram_ecode));
    exit(1);
  }
  
  dgram_addr = (struct sockaddr_in *) dgram_addrlist->ai_addr;

	
  fflush(stdout);
	
	dgram_fd = socket (dgram_addrlist->ai_family, dgram_addrlist->ai_socktype, 0);
	if (dgram_fd < 0){
		perror ("nim_server_dgram_socket:socket");
		exit(1);
	}
	if(bind(dgram_fd, (struct sockaddr *)dgram_addr, sizeof(struct sockaddr_in)) < 0){
		perror("nim_server_dgram_socket:bind");
		exit(1);
	}
	
  pid_t pid2; int bb; 
	struct sockaddr_in d_from;
	socklen_t fsize;
	
	fsize = sizeof(d_from);


	
	
//BELOW LIES TCP CIRCUIT STUFF	
  int listener, cc, hits, ecode, put, handlerSize, num;
  struct sockaddr_in *localaddr, from;
  socklen_t length;
  struct addrinfo hints, *addrlist;
  char myhostname[128];
  fd_set mask;
	char ch;


  //socklen_t fsize;
  //struct timeval timeout;
    

/* 
   Want to specify local server address of:
      addressing family: AF_INET
      socket type:       SOCK_STREAM
      ip address:        any interface on this system 
      port:              0 => system will pick free port
*/

//Creating the socket to be used for datagram reception
  FILE *f = fopen("file.txt", "w");
  memset(&hints, 0, sizeof(hints));
	hints.ai_family = AF_INET; hints.ai_socktype = SOCK_STREAM;
  hints.ai_flags = AI_NUMERICSERV | AI_PASSIVE; hints.ai_protocol = 0;
  hints.ai_canonname = NULL; hints.ai_addr = NULL;
  hints.ai_next = NULL;

  ecode = getaddrinfo(NULL, "0", &hints, &addrlist);
  if (ecode != 0) {
    fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(ecode));  
    exit(1);
  }

  localaddr = (struct sockaddr_in *) addrlist->ai_addr;
 
  if ((listener = socket( addrlist->ai_family, addrlist->ai_socktype, 0 )) < 0 ) {
    perror("nim_server:socket");
    exit(1);
  }

  if (bind(listener, (struct sockaddr *)localaddr, sizeof(struct sockaddr_in)) < 0) {
    perror("nim_server:bind");
    exit(1);
  }

  // Print out the address info assigned with socket s.

  length = sizeof(struct sockaddr_in);
  if (getsockname(listener, (struct sockaddr *)localaddr, &length) < 0) {
    perror("myaddrs:getsockname");
    exit(1);
  }

 length = sizeof(struct sockaddr_in);
 if (getsockname(dgram_fd, (struct sockaddr *)dgram_addr, &length) < 0) {
   perror("myaddrs:getsockname");
   exit(1);
 }
 printsin(localaddr, "NIM_SERVER","IPv4 address is (TCP)");
 printsin(dgram_addr, "NIM_SERVER", "IPv4 address is (datagram)");

// Get the symbolic host name of this machine.

  if (gethostname(myhostname, 128) != 0) {
    perror("myaddrs:gethostname");
    exit(1);
  }
  fprintf(stdout,"%s\n", myhostname);
  fprintf(f,"%s\n", myhostname);
  fprintf(f, "%d\n", ntohs((unsigned short)(localaddr -> sin_port)));  
  fprintf(f, "%d\n", ntohs((unsigned short)(dgram_addr -> sin_port)));
	fclose(f);

	listen(listener, 1); 
	
	int connection1, connection2;
	struct sockaddr_in peer1;
	struct sockaddr_in peer2;
	socklen_t length1;
	socklen_t length2;
	length1 = sizeof(peer1);
	length2 = sizeof(peer2);
	char handle1[20];
	char handle2[20];
	
	while(1){
		signal(SIGINT, siginthandler);
		signal(SIGUSR2, usr2handler);
		FD_ZERO(&mask);
		FD_SET(0,&mask);
		FD_SET(listener, &mask);
		FD_SET(dgram_fd, &mask);
		if ((hits = select(listener+1, &mask, (fd_set *)0, (fd_set *)0,
		                 NULL)) < 0) {
	    perror("fancy_recv_udp:select");
	    exit(1);
	  }
		if (FD_ISSET(listener, &mask)){
			if(connection1){
				if((connection2 = accept(listener, (struct sockaddr *)&peer2, &length2)) < 0 ) {
					perror("inet_rstream:accept");
					exit(1);
				}
				//Read/Accept password here/Should this use tcp or query?? If not close and null connection 1
				bb = recvfrom(dgram_fd, &guestPassword, sizeof(guestPassword), 0, (struct sockaddr *)&d_from, &fsize);
			//	printf("Password recieved: %s \n", guestPassword);
				if(strcmp(guestPassword, password) != 0){
					  sendto(dgram_fd, &no, sizeof(no), 0, (struct sockaddr *)&d_from, 
						          fsize);
				  	close(connection2);
						connection2 = NULL;
				}else{
				sendto(dgram_fd, &yes, sizeof(yes), 0, (struct sockaddr *)&d_from, 
						          fsize);
				printsin(&peer2,"RSTREAM2::", "accepted connection from");
				handlerSize = strlen(handlerMsg); put = 0;
				num = write(connection2, handlerMsg, handlerSize);
				
				read(connection2, &handle2, 20);
				
				size_t ln = strlen(handle2) - 1;
				if (handle2[ln] == '\n'){
				    handle2[ln] = '\0';
				}
				if(strcmp(handle2, "") == 0){
					close(connection2);
					connection2 = NULL;
					continue;
				}
				strcpy(matchList->tail->gameTwo, handle2);
				printf("%s", handle2); 
				if((pid1 = fork()) == 0){
					close(listener);
					char connection1Str[15];
					sprintf(connection1Str, "%d", connection1);
					char connection2Str[15];   
					sprintf(connection2Str, "%d", connection2);
					
					char * a[] = {"nim_match_server", connection1Str, connection2Str, handle1, handle2, NULL};
					char * e[] = {NULL};
					execve("nim_match_server", a, e);
					perror("parent");
					exit(1);
				}
				close(connection1);
				close(connection2); 
				connection1 = NULL;
				connection2 = NULL;
				matchList->tail->pid = pid1;
				//printList(matchList);
	 
			//	printf("pid: %d\n", pid1);
				i++;
				
      }

				 
			}else{
				if((connection1 = accept(listener, (struct sockaddr *)&peer1, &length1)) < 0 ) {
					perror("inet_rstream:accept");
					exit(1);
				}
				//Read/Accept password here/Should this use tcp or query?? If not close and null connection 1
				bb = recvfrom(dgram_fd, &guestPassword, sizeof(guestPassword), 0, (struct sockaddr *)&d_from, &fsize);
		//		printf("Password recieved: %s \n", guestPassword);
				if(strcmp(guestPassword, password) != 0){
					sendto(dgram_fd, &no, sizeof(no), 0, (struct sockaddr *)&d_from, 
					          fsize);
					close(connection1);
					connection1 = NULL;
				}else{
				sendto(dgram_fd, &yes, sizeof(yes), 0, (struct sockaddr *)&d_from, 
					          fsize);
				printsin(&peer1,"RSTREAM1::", "accepted connection from");
				handlerSize = sizeof(handlerMsg); put = 0;
				num = write(connection1, handlerMsg, handlerSize);
				read(connection1, &handle1, 20);  
				if(strcmp(handle1, "") == 0){
					close(connection1);
					connection1 = NULL;
				}
				printf("%s", handle1);
				size_t ln = strlen(handle1) - 1;
				if (handle1[ln] == '\n'){
				    handle1[ln] = '\0';
				}
				push(matchList, handle1);
			 }
			}

		}else if(FD_ISSET(dgram_fd, &mask)){

			//via datagram, take password into guestpassword, strcmp the two passwords.  Do this every time, 
			//just reset from nopass to nopass.  if the password is nopass skip as well.  Maybe do this via
			//a blank string?  idk yet if that will work, but lets find out woopee
			
			bb = recvfrom(dgram_fd, &guestPassword, sizeof(guestPassword), 0, (struct sockaddr *)&d_from, &fsize);
			printf("Password recieved: %s \n", guestPassword);
      if(strcmp(password, guestPassword) == 0){
	    sendto(dgram_fd, &yes, sizeof(yes), 0, (struct sockaddr *)&d_from, 
					          fsize);
			int j = 0;
			printf("i, j before wait3: %d %d\n", i, j);
			while((pid2 = wait3(NULL, WNOHANG, NULL)) && j < i){
				printf("%d\n", pid2);
				listHunter(matchList, pid2); 
		//		printList(matchList);
				j++;
				i = i - 1;
			}
			
			char msg[120];
			bb = recvfrom(dgram_fd,&msg,sizeof(msg),0,(struct sockaddr *)&d_from,&fsize);
	    if (bb < 0){
		    perror("recv_udp:recvfrom");
		    }
	    printsin( &d_from, "recv_udp: ", "Packet from:");
	    //printf("Got data ::%s\n",msg);
	    fflush(stdout);
			char reply[2048] ="";
			char active[] = " is waiting for a client\n";
			char active2[] = "Active game: ";
			char vs[] = " vs ";
			char newline[] = " \n";
			MATCH * temp = matchList->head;
	//		printList(matchList);
			while(temp!=NULL){
				if(temp->flag == 0){
			//		printf("%s", temp->gameTwo);
					if(temp->gameTwo[0] == NULL && temp->gameOne != NULL){
						strcat(reply, temp->gameOne);
						strcat(reply, active);
					}else if(temp->gameTwo != NULL && temp->gameOne != NULL && temp->flag == 0){
						strcat(reply, active2);
						strcat(reply, temp->gameOne);
					  strcat(reply, vs);
						strcat(reply, temp->gameTwo);
						strcat(reply, newline);
					}
				}
				temp = temp->next;
			}
	//		printf("%s\n", reply);
			sendto(dgram_fd, &reply, sizeof(reply), 0, (struct sockaddr *)&d_from, 
			          fsize);
			perror("sendto:");
			fflush(stdout); 
		}	else{
				sendto(dgram_fd, &no, sizeof(no), 0, (struct sockaddr *)&d_from, 
					          fsize);
	}
	}
		
	}



  exit(0);
}

LINKEDLIST *llalloc(){
	LINKEDLIST *l = (LINKEDLIST *) malloc (sizeof(LINKEDLIST));
	if(l == NULL){
		printf("Malloc Error\n");
		exit(1);
	}
	MATCH *n = (MATCH *) malloc(sizeof(MATCH));
	if(n == NULL){
		printf("Malloc Error\n");
		exit(1);
	}
	n->flag = 2;
	l->head = n;
	l->tail = n;
	return l;
}

MATCH *mmalloc(){
	MATCH *n = (MATCH *) malloc(sizeof(MATCH));
	if(n == NULL){
		printf("Malloc Error\n");
		exit(1);
	} 
	strcpy(n->gameTwo, "");
	n->flag = 0;
	n->next = NULL;
	return n;
}

LINKEDLIST *push(LINKEDLIST *l, char * gameOne){
	MATCH *n = mmalloc();
	strcpy(n->gameOne, gameOne);
	l->tail->next = n;
	l->tail = n;
	return l;
}

void printList(LINKEDLIST *l){ 
	MATCH * temp = l->head;
	while(temp != NULL){
		printf("pid:%d flag:%d: Match %s vs. %s\n", temp-> pid, temp->flag, temp->gameOne, temp->gameTwo);
		temp = temp->next;
	}
}

void listHunter(LINKEDLIST *l, int pid){
	MATCH * temp = l->head;
	while(temp != NULL){
		if(temp->pid == pid){
		//	printf("Hunted\n");
			temp->flag = 1;
		}
		temp = temp->next;
	}
}

void printsin(struct sockaddr_in *sin, char *m1, char *m2 )
{
  char fromip[INET_ADDRSTRLEN];

  printf ("%s %s:\n", m1, m2);
  printf ("  ip address %s, port %d\n",
	    inet_ntop(AF_INET, &(sin->sin_addr.s_addr), fromip, sizeof(fromip)),
            ntohs((unsigned short)(sin -> sin_port)));
} 