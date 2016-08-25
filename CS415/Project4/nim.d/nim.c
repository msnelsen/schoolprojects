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
#include <limits.h>

long int rowState1 = 1;
long int rowState2 = 3;
long int rowState3 = 5;
long int rowState4 = 7;
int row;
int column;
int sock;
char buffer[256]; char message[10]; 
char password[40];
char yes[2] = "y";
char no[2] = "n";

void move(char * r, char * c);


void printRow(int r){
	int i = 1;
	while(i <= r){
		printf(" 0");
		i++;
	}
	while(i<=7){
		printf("--");
		i++;
	}
	printf("\n");
}

void siginthandler(sig){
	bzero(message, sizeof(message));
	message[0] = 'c';
	write(sock, message, 10);
	exit(0);
}



void printState(int r1, int r2, int r3, int r4){
	printf("-------------------\n");
	printf("1:"); printRow(r1);
	printf("2:"); printRow(r2);
	printf("3:"); printRow(r3);
	printf("4:"); printRow(r4);
	printf("-------------------\n");
	printf("   1 2 3 4 5 6 7\n");
	printf("-------------------\n");
}


void invalidmove(){
	printf("Invalid move\n");
	printf("Please enter another move\n");
	printf("Enter the row you want to move: ");

	char rowStr[10];
	char columnStr[10];
	bzero(rowStr, 10); bzero(columnStr, 10);
	fgets(rowStr, 10, stdin);
	printf("\n");
	printf("Enter the column you want to move: ");
	fgets(columnStr, 10, stdin);
	printf("column %s \n", columnStr);
	move(rowStr, columnStr);
}
void move(char * r, char * c){
	//printf("%d%d%d%d\n", rowState1, rowState2, rowState3, rowState4);
	
	int i = 0;
	while (r[i] != '\n') {
		i++;
	}
	r[i] = '\0';
	i = 0;
	while (c[i] != '\n') {
		i++;
	}
	c[i] = '\0';
	i = 0;
	while (r[i] != ' ') {
		i++;
	}
	r[i] = '\0';
	i = 0;
	while (c[i] != ' ') {
		i++;
	}
	c[i] = '\0';
	char * endpointer;
	row = strtol(r, &endpointer, 10);

	//if (*endpointer != '\0' || *endpointer != '\n'){
	if (strcmp(endpointer, "")) {
		printf("Invalid Row Character\n");
		invalidmove();
		return(0);

		}
	column = strtol(c, &endpointer, 10);
//	printf("row: %lu, column: %lu, endpointer: %s\n", row, column, endpointer);
	//if (*endpointer != '\0' || *endpointer != '\n'){
	if (strcmp(endpointer, "")) {
		printf("Invalid Column Character\n");
		invalidmove();
		return(0);
		
		}
		
		if(row > 4){
			printf("1\n");
			invalidmove();
			return(0);	
		}else{
		if(row == 1){
		//	printf("changed rowState1 to %d\n", rowState1);
			if(column <= rowState1){
			//	   printf("changed rowState1 to %d\n", rowState1);
					 rowState1 = column - 1;
				//	printf("changed rowState1 to %d\n", rowState1);
					
				}else{
				//	printf("%d%d%d%d\n", rowState1, rowState2, rowState3, rowState4);
				//	printf("Rowstate 1 baby: %d\n", rowState1);
				//	printf("2\n");
					invalidmove();
					return(0);	
				}
			}
		if(row == 2){
		//	printf("changed rowState2 to %d\n", rowState2);
			if(column <= rowState2){
			//	printf("changed rowState2 to %d\n", rowState2);
					rowState2 = column - 1;
				//	printf("changed rowState2 to %d\n", rowState2);
					
			}
			else{
			//	printf("%d%d%d%d\n", rowState1, rowState2, rowState3, rowState4);
		//		printf("Rowstate 2 baby: %d\n", rowState2);
			//	printf("3\n");
				invalidmove();
				return(0);	
			}
		}
		if(row == 3){
		//		printf("changed rowState3 to %d\n", rowState3);
			if(column <= rowState3){
		//		printf("changed rowState3 to %d\n", rowState3);
					rowState3 = column - 1;
			//		printf("changed rowState3 to %d\n", rowState3);
					
			}
			else{
			//	printf("%d%d%d%d\n", rowState1, rowState2, rowState3, rowState4);
			//	printf("Rowstate 3 baby: %d\n", rowState3);
			//	printf("4\n");
				invalidmove();
				return(0);	
			}
		}
		if(row == 4){
		//	printf("changed rowState4 to %d\n", rowState4);
			if(column <= rowState4){
			//	printf("changed rowState4 to %d\n", rowState4);
					rowState4 = column - 1;
				//	printf("changed rowState4 to %d\n", rowState4);
					
			}
			else{
			//	printf("%d%d%d%d\n", rowState1, rowState2, rowState3, rowState4);
			//	printf("Rowstate 4 baby: %d\n", rowState4);
			//	printf("5\n");
				invalidmove();	
			}
		}
	}
     
		
}
// void move(int  r, int c){
// 	if(r > 4){
// 		printf("Invalid move\n");
// 		printf("Please enter another move\n");
// 		printf("Enter the row you want to move: ");
// 		char rowStr[10];
// 		char columnStr[10];
// 		fgets(rowStr, 10, stdin);
// 		printf("\n");
// 		printf("Enter the column you want to move: ");
// 		fgets(columnStr, 10, stdin);
// 		char * endpointer;
// 		row = strtol(rowStr, &endpointer, 10);
// 		if (*endpointer != '\0'){
// 			printf("Invalid Characters\n");
// 			exit(1);
// 		}
// 		column = strtol(columnStr, &endpointer, 10);
// 		if (*endpointer != '\0'){
// 			printf("Invalid Characters\n");
// 			exit(1);
// 		}
// 		move(row, column);
// 	}else{
// 		if(r == 1){
// 			if(c <= rowState1){
// 			  rowState1 = c - 1;
// 		  }
// 			else{
// 				printf("Invalid move\n");
// 				printf("Please enter another move\n");
// 				printf("Enter the row you want to move: ");
// 				char rowStr[10];
// 				char columnStr[10];
// 				fgets(rowStr, 10, stdin);
// 				printf("\n");
// 				printf("Enter the column you want to move: ");
// 				fgets(columnStr, 10, stdin);
// 				char * endpointer;
// 				row = strtol(rowStr, &endpointer, 10);
// 				if (*endpointer != '\0'){
// 					printf("Invalid Characters\n");
// 					exit(1);
// 				}
// 				column = strtol(columnStr, &endpointer, 10);
// 				if (*endpointer != '\0'){
// 					printf("Invalid Characters\n");
// 					exit(1);
// 				}
// 				move(row, column);
// 			}
// 		}else if(r == 2){
// 			if(c <= rowState2){
// 			  rowState2 = c - 1;
// 		  }else{
// 				printf("Invalid move\n");
// 				printf("Please enter another move\n");
// 				printf("Enter the row you want to move: ");
// 				char rowStr[10];
// 				char columnStr[10];
// 				fgets(rowStr, 10, stdin);
// 				printf("\n");
// 				printf("Enter the column you want to move: ");
// 				fgets(columnStr, 10, stdin);
// 				char * endpointer;
// 				row = strtol(rowStr, &endpointer, 10);
// 				if (*endpointer != '\0'){
// 					printf("Invalid Characters\n");
// 					exit(1);
// 				}
// 				column = strtol(columnStr, &endpointer, 10);
// 				if (*endpointer != '\0'){
// 					printf("Invalid Characters\n");
// 					exit(1);
// 				}
// 				move(row, column);
// 		  }
// 		}else if(r == 3){
// 			if(c <= rowState3){
// 			  rowState3 = c - 1;
// 		  }else{
// 				printf("Invalid move\n");
// 				printf("Please enter another move\n");
// 				printf("Enter the row you want to move: ");
// 				char rowStr[10];
// 				char columnStr[10];
// 				fgets(rowStr, 10, stdin);
// 				printf("\n");
// 				printf("Enter the column you want to move: ");
// 				fgets(columnStr, 10, stdin);
// 				char * endpointer;
// 				row = strtol(rowStr, &endpointer, 10);
// 				if (*endpointer != '\0'){
// 					printf("Invalid Characters\n");
// 					exit(1);
// 				}
// 				column = strtol(columnStr, &endpointer, 10);
// 				if (*endpointer != '\0'){
// 					printf("Invalid Characters\n");
// 					exit(1);
// 				}
// 				move(row, column);
// 		  }
// 		}else if( r == 4){
// 			if( c <= rowState4){
// 			  rowState4 = c - 1;
// 		}else{
// 			printf("Invalid move\n");
// 			printf("Please enter another move\n");
// 			printf("Enter the row you want to move: ");
// 			char rowStr[10];
// 			char columnStr[10];
// 			fgets(rowStr, 10, stdin);
// 			printf("\n");
// 			printf("Enter the column you want to move: ");
// 			fgets(columnStr, 10, stdin);
// 			char * endpointer;
// 			row = strtol(rowStr, &endpointer, 10);
// 			if (*endpointer != '\0'){
// 				printf("Invalid Characters\n");
// 				exit(1);
// 			}
// 			column = strtol(columnStr, &endpointer, 10);
// 			if (*endpointer != '\0'){
// 				printf("Invalid Characters\n");
// 				exit(1);
// 			}
// 			move(row, column);
// 		}
// 	}
// }
// }

int stringMaker(){
	int one, two, three, four, toReturn;
	one = rowState1*1000;
	if(one == 0){
		one = 9000;
	}
	two = rowState2*100;
	if(two == 0){
		two = 900;
	}
	three = rowState3*10;
	if(three == 0){
		three = 90;
	}
	four = rowState4;
	if(four == 0){
		four = 9;
	}
	toReturn = one + two + three + four;
	return(toReturn);
}

void translate(){
	char one = buffer[1];
	if(one == '8'){
	}else if(one == '9'){
		rowState1 = 0;
	}else{
		rowState1 = one - '0';
	}
	char two = buffer[2];
	if(two == '8'){
	}else if(two == '9'){
		rowState2 = 0;
	}else{
		rowState2 = two - '0';
	}
	char three = buffer[3];
	if(three  == '8'){
	}else if(three == '9'){
		rowState3 = 0;
	}else{
		rowState3 = three - '0';
	}
	char four = buffer[4];
	if(four == '8'){
	}else if(four == '9'){
		rowState4 = 0;
	}else{
		rowState4 = four - '0';
	}
 

//	printf("translated: %d%d%d%d\n", rowState1, rowState2, rowState3, rowState4);
	}


int main(int argc,char **argv)
{
	FILE * f = fopen("file.txt", "r");
  if(f == NULL){
		printf("File not found\n");
	exit(1);
  }
  char * symbolicName = malloc(sizeof(char) * LINE_MAX);
  char * portNumber = malloc(sizeof(char) * LINE_MAX);
	char * dgramNumber = malloc(sizeof(char) * LINE_MAX);
  fgets(symbolicName, LINE_MAX, f);
	fgets(portNumber, LINE_MAX, f);
	fgets(dgramNumber, LINE_MAX, f);
	size_t ln = strlen(symbolicName) - 1;
	if (symbolicName[ln] == '\n'){
	    symbolicName[ln] = '\0';
	}
	ln = strlen(portNumber) - 1;
	if (portNumber[ln] == '\n'){
	    portNumber[ln] = '\0';
	} 
	ln = strlen(dgramNumber) - 1;
	if (dgramNumber[ln] == '\n'){
	    dgramNumber[ln] = '\0';
	}
//	printf("%s\n", symbolicName);
//	printf("%s\n", portNumber);
//	printf("%s\n", dgramNumber);
	fclose(f);
	char received[2048];
	
	//Change password -handle inputs here!
	if(argc == 2 && strcmp(argv[1], "-p") == 0){
		printf("Enter a password, fool\n");
		exit(1);
	}
	if(argc == 4 && strcmp(argv[1], "-q") == 0 && strcmp(argv[2], "-p") == 0){
		strcpy(password, argv[3]);
	//	printf("Password is: %s\n", password);
	}
	if(argc == 3 && strcmp(argv[1], "-p") == 0){
		strcpy(password, argv[2]);
	//	printf("Password is: %s\n", password);
	}
	if(argc == 3 && strcmp(argv[1], "-q") == 0 && strcmp(argv[2], "-p") == 0){
		printf("Enter a password, fool\n");
		exit(1);
	}
	if(argc == 3 && (strcmp(argv[1], "-p") != 0 && strcmp(argv[1], "-q") != 0)){
		printf("Invalid arguments\n");
		exit(1);
	}
	if(argc > 4){
		printf("Too many arguments\n");
		exit(1);
	}
	if(argc == 2 && strcmp(argv[1], "-q") != 0){
		printf("Invalid input\n");
		exit(0);
	}
	
	int dgram_fd, dgram_ecode, hits, bb;
	struct timeval timeout;
	fd_set mask;
	socklen_t dgram_size;
	struct sockaddr_in *dest;
	struct addrinfo dgram_hints, *dgram_addrlist;
	int destsize = sizeof(dest);

	memset(&dgram_hints, 0, sizeof(dgram_hints));
	dgram_hints.ai_family = AF_INET; dgram_hints.ai_socktype = SOCK_DGRAM;
  dgram_hints.ai_flags = AI_NUMERICSERV | AI_PASSIVE; dgram_hints.ai_protocol = 0;
  dgram_hints.ai_canonname = NULL; dgram_hints.ai_addr = NULL;
  dgram_hints.ai_next = NULL;

  dgram_ecode = getaddrinfo(symbolicName, dgramNumber, &dgram_hints, &dgram_addrlist);
  if (dgram_ecode != 0) {
    fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(dgram_ecode));
    exit(1);
  }

	dest = (struct sockaddr_in *) dgram_addrlist->ai_addr;

	dgram_fd = socket (dgram_addrlist->ai_family, dgram_addrlist->ai_socktype, 0);
	if (dgram_fd < 0){
		perror ("nim_server_dgram_socket:socket");
		exit(1);
	}
	
	

	if(argc >= 2 && strcmp(argv[1], "-q") == 0){
		
		
		//send password, recieve password/permission
		bb = sendto(dgram_fd, &password, sizeof(password), 0, (struct sockaddr *) dest, 
			              sizeof(struct sockaddr_in));
		bb = recvfrom(dgram_fd,&received,sizeof(received),0,(struct sockaddr *)&dest,&destsize);
		if (bb<0){
			printf("error");
		}
		if(strcmp(received, no) == 0){
			printf("Wrong password\n");
			exit(1);
		}
		printf("Query mode\n");
		// Setting up a new Datagram Circiut

		
		char dgram_array[120] = "Message!! From dgram query!!\n";
		// if(bind(dgram_fd, (struct sockaddr *)dgram_addr, sizeof(struct sockaddr_in)) < 0){
		// 	perror("nim_server_dgram_socket:bind");
		// 	exit(1);
		// }
		bb = sendto(dgram_fd,&dgram_array,sizeof(dgram_array),0,(struct sockaddr *) &dest,
						sizeof(struct sockaddr_in));
		if(bb < 0){
			perror("send_udp:sendto");
			exit(1);
		}
		for(;;) {
			FD_ZERO(&mask);
			FD_SET(0, &mask);
			FD_SET(dgram_fd, &mask);
			timeout.tv_sec = 60;
			timeout.tv_usec = 0;
			if((hits = select(dgram_fd+1, &mask, (fd_set *)0, (fd_set *)0, &timeout)) < 0){
				perror("nim_client:select");
				exit(1);
			}
			if( (hits == 0) || ((hits > 0) && (FD_ISSET(0, &mask))) ) {
				printf("Shutting down\n");
				exit(0);
			}
			if(FD_ISSET(dgram_fd, &mask)){
				bzero(received, 2048);
				int destsize = sizeof(dest);
        bb = recvfrom(dgram_fd,&received,sizeof(received),0,(struct sockaddr *)&dest,&destsize);
	      if (bb < 0){
		      perror("recv_udp:recvfrom");
		    }
	      printf("Got data :: %s\n", received);
				if(strcmp(received, "") == 0){
					printf("No active clients\n");
				}
	      fflush(stdout);
			  exit(0);
      } 
		}		
		exit(0);
	}
	
// HERE IS THE FUN GAME TIME STUFF
	
  int	 cc, ecode, num, left, put, n;
  struct sockaddr_in *server;
  struct addrinfo hints, *addrlist; 
	char ch; 
	
	char handle[22];char opponentHandle[20]; char rowStr[10]; char columnStr[10]; 
	
	


/*
   Use getaddrinfo to create a SOCK_STREAM sockarddr_in .
*/
    
  memset(&hints, 0, sizeof(hints));
  hints.ai_family = AF_INET; hints.ai_socktype = SOCK_STREAM;
  hints.ai_flags = AI_NUMERICSERV; hints.ai_protocol = 0;
  hints.ai_canonname = NULL; hints.ai_addr = NULL;
  hints.ai_next = NULL;

  ecode = getaddrinfo(symbolicName, portNumber, &hints, &addrlist);
  if (ecode != 0) {
    fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(ecode));
    exit(1);
  }

  server = (struct sockaddr_in *) addrlist->ai_addr; // Will use in sendto().

  if ( (sock = socket( addrlist->ai_family, addrlist->ai_socktype, 0 )) < 0 ) {
    perror("inet_wstream:socket");
    exit(1);
  }

  if ( connect(sock, (struct sockaddr *)server, sizeof(struct sockaddr_in)) < 0) {
    perror("inet_wstream:connect");
    exit(1);
  }

  bb = sendto(dgram_fd, &password, sizeof(password), 0, (struct sockaddr *) dest, 
		              sizeof(struct sockaddr_in));
		
	bb = recvfrom(dgram_fd,&received,sizeof(received),0,(struct sockaddr *)&dest,&destsize);
	if(strcmp(received, no) == 0){
			printf("Wrong password\n");
			exit(1);
		 }

	bzero(received, sizeof(received));

  while ( read(sock, &ch, 1) == 1 && ch != '\n'){
		putchar(ch);
  }
	fgets(handle, 22, stdin);
//	printf("%d\n", strlen(handle));
	if(strlen(handle) > 20 ){
		printf("Handle is too long\n");
		left = sizeof(handle);
		write(sock, handle, left);
		exit(1);
	}
	printf("Your handle is %s", handle);
	left = sizeof(handle); put = 0;
	write(sock, handle, left);
	int i = 0;
  
  printf("Your opponent's Handle is: " );
	// read(sock, &opponentHandle, 20);
	bzero(opponentHandle, 21);
	while(strcmp(opponentHandle, "") == 0){
	read(sock, opponentHandle, 20);
  }

	printf("%s\n", opponentHandle); 
	printState(rowState1, rowState2, rowState3, rowState4);

	
	while(1){
		signal(SIGINT, siginthandler);
		bzero(buffer, 256);	bzero(rowStr, 10); bzero(columnStr, 10); bzero(message, 10); 
		char message2[10];
		n = recv(sock, buffer, 255, 0);
		if(strcmp(buffer, "") != 0){
		  //printf("Here is the mes0sage: %s\n", buffer);
		}
		if(buffer[0] == 'a'){
			translate();
			printf("Your turn!!\n");
			printState(rowState1, rowState2, rowState3, rowState4);
			printf("Enter the row you want to move: ");
			fgets(rowStr, 10, stdin);
			printf("Enter the column you want to move: ");
			fgets(columnStr, 10, stdin);
			// char * endpointer;
			// row = strtol(rowStr, &endpointer, 10);
			// column = strtol(columnStr, &endpointer, 10);
			move(rowStr, columnStr);
			printState(rowState1, rowState2, rowState3, rowState4);
			if(rowState1 == 0 && rowState2 == 0 && rowState3 == 0 && rowState4 == 0){
				printf("You have lost!\n");
				message[0] = 'b';
			}else if(row == 0 && column == 0){
				printf("You have terminated\n");
				message[0] = 'c';
			}else{
			  int toReturn = stringMaker();
			  message[0] = 'a';
			  sprintf(message2, "%d", toReturn);
			  strcat(message, message2);
			  printf("%s\n", message);
		  }
			n = write(sock, message, sizeof(message));
			if(message[0] == 'b' || message[0] == 'c'){
				exit(0);
			}
		}else if(buffer[0] == 'b'){
			  printState(rowState1, rowState2, rowState3, rowState4);
				printf("You have won!\n");
				exit(0);
		}else if(buffer[0] == 'c'){
			printState(rowState1, rowState2, rowState3, rowState4);
			printf("Your opponent terminated\n");
			exit(0);
		}

			
		}	

	exit(0);
	

}

/*
   Set up a datagram (UDP/IP) socket in the Internet domain.
   We will use it as the handle thru which we will send a
   single datagram. Note that, since this no message is ever
   addressed TO this socket, we do not bind an internet address
   to it. It will be assigned a (temporary) address when we send
   a message thru it.
*/
 // // Code for DGRAM SENDING
 //  socket_fd = socket (addrlist->ai_family, addrlist->ai_socktype, 0);
 //  if (socket_fd == -1) {
 //    perror ("send_udp:socket");
 //    exit (1);
 //  }
  // 
  // msgbuf.head = '<';
  // msgbuf.body = htonl(getpid());
  // msgbuf.tail = '>';
  // 
  // cc = sendto(socket_fd,&msgbuf,sizeof(msgbuf),0,(struct sockaddr *) dest,
  //                 sizeof(struct sockaddr_in));
  // if (cc < 0) {
  //   perror("send_udp:sendto");
  //   exit(1);
  // }