/************************************************************************\
* 			  MYADDRS.C       			         *
* Just bind an address to a socket, wild card for host, port 0 to ask    *
* for any unallocated port. Then output addressing info.                 *
* 								         *
* Phil Kearns							         *
* March 21, 2015 						         *
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

void printsin(struct sockaddr_in*, char*, char*);

int main()
{
  int s;
  struct sockaddr_in *localaddr;
  int ecode;
  socklen_t length;
  struct addrinfo hints, *addrlist;
  char myhostname[128];

/* 
   Want to specify local server address of:
      addressing family: AF_INET
      socket type:       SOCK_STREAM
      ip address:        any interface on this system 
      port:              0 => system will pick free port
*/

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
 
  if ((s = socket( addrlist->ai_family, addrlist->ai_socktype, 0 )) < 0 ) {
    perror("myaddrs:socket");
    exit(1);
  }

  if (bind(s, (struct sockaddr *)localaddr, sizeof(struct sockaddr_in)) < 0) {
    perror("myaddrs:bind");
    exit(1);
  }

  // Print out the address info assigned with socket s.

  length = sizeof(struct sockaddr_in);
  if (getsockname(s, (struct sockaddr *)localaddr, &length) < 0) {
    perror("myaddrs:getsockname");
    exit(1);
  }
  printsin(localaddr, "MYADDRS","IPv4 address is");

  // Get the symbolic host name of this machine.

  if (gethostname(myhostname, 128) != 0) {
    perror("myaddrs:gethostname");
    exit(1);
  }
  printf("MYADDRS Symbolic host name is %s\n", myhostname);  

  // That's all we want to do.

  exit(0);
}

void printsin(struct sockaddr_in *sin, char *m1, char *m2 )
{
  char fromip[INET_ADDRSTRLEN];

  printf ("%s %s:\n", m1, m2);
  printf ("  ip address %s, port %d\n",
	    inet_ntop(AF_INET, &(sin->sin_addr.s_addr), fromip, sizeof(fromip)),
            ntohs((unsigned short)(sin -> sin_port)));
}