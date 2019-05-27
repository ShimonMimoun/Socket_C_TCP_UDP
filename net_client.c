#include <sys/types.h>
#include <unistd.h>    
#include <strings.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <signal.h>    
#include <sys/socket.h>
#include <sys/un.h>
#include <netinet/in.h>
#define SIM_LENGTH 10 
//#define IP_ADDRESS "127.0.0.1" 
#define PORT 1337 





int main(int argc, char* argv[])
{ 
  struct addrinfo* res;
  struct sockaddr_in* serveur_addr;
  struct sockaddr_in client_name; 
  char* host_name;
  char* host_addr;
  int sock; 
  int temp_count;
  int socket_from; 
  


  if (argc != 2) {
    perror(" Error please use  hostnamelookup \n");
    exit(1);
  }

  host_name = argv[1];
  int getinfoad=getaddrinfo(host_name, NULL, NULL, &res);
  
  if (0 !=getinfoad) 
  {
    fprintf(stderr, "Error Resolving hostname %s \n", host_name);
    exit(1);
  }
  
  serveur_addr = (struct sockaddr_in*)res->ai_addr;
  host_addr = inet_ntoa(serveur_addr->sin_addr);

  printf("Address for %s is %s \n", host_name, host_addr);
  

  printf("Client is alive and establishing socket connection \n");
  
  
  sock = socket(AF_INET, SOCK_STREAM, 0);
  if (sock < 0)
    { perror ("Error Channel Opening");
      close(sock);
      exit(1);
    }
      

  memset((char *)&client_name,0, sizeof(client_name)); 
  client_name.sin_family = AF_INET; 
  client_name.sin_addr.s_addr = inet_addr(host_addr); 
  client_name.sin_port = htons(PORT);


  if (connect(sock, (struct sockaddr *)&client_name, sizeof(client_name)) < 0)
    { perror ("Error establishing communications");
      close(sock);
      exit(1);
    }


  for (temp_count = 1; temp_count <= SIM_LENGTH; temp_count++)
    { read(sock, &socket_from, 4);
      printf("Client has received %d from socket  \n", socket_from);
    }

  printf("Exiting now \n");

  close(sock); 
  exit(0); 

} 