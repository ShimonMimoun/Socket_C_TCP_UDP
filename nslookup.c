
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <netinet/in.h>
#include <arpa/inet.h>

int main(int argc, char* argv[]) {
  struct addrinfo* res;
  char* hostname
  char* hostaddr;
  struct sockaddr_in* saddr;
  
  if (argc != 2) {
    perror("Usage: hostnamelookup <hostname>\n");
    exit(1);
  }

  hostname = argv[1];
  
  if (0 != getaddrinfo(hostname, NULL, NULL, &res)) { //get address information, if its not succeed print eror message.
    fprintf(stderr, "Error in resolving hostname %s\n", hostname);
    exit(1);
  }
  
  saddr = (struct sockaddr_in*)res->ai_addr;//setting the info from the strucy addrinfo res (the info provided by the function getadderinfo) into those variables and prints them.
  hostaddr = inet_ntoa(saddr->sin_addr);//--------^^^^^^^

  printf("Address for %s is %s\n", hostname, hostaddr);
  exit(0);
}