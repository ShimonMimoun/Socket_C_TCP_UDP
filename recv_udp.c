#include <sys/types.h>
#include <netinet/in.h>
#include <inttypes.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <strings.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>


void printsin(struct sockaddr_in *sin, char *pname, char* msg){
  printf("%s\n", pname );
  printf("%s", msg);
  printf("%d", sin->sin_family);
  printf(" ");
  printf("ip= %s port= %d\n", inet_ntoa(sin->sin_addr) ,sin->sin_port );

}


int main(int argc, char *argv[])
{
  int socket_fd, cc, fsize;
  struct sockaddr_in  s_in, from;
  char get_message[1000];
  char send_message[] = "server";

  socket_fd = socket (AF_INET, SOCK_DGRAM, 0);//socket creation for UDP 

  memset((char *) &s_in,0, sizeof(s_in));  /* They say you must do this    */ //this function delet the firs "sizeof" chars of s_in and insert '0' instead.

  s_in.sin_family = (short)AF_INET; // insert IPv4 to s_in 
  s_in.sin_addr.s_addr = htonl(INADDR_ANY);    /* WILDCARD */ //transfer the IPv4 (INADDER_ANY) to net presentaion  
  s_in.sin_port = htons((u_short)0x3333); //insert s_in a port number of short type

  printsin( &s_in, "RECV_UDP", "Local socket is:"); 
  
  fflush(stdout);

  bind(socket_fd, (struct sockaddr *)&s_in, sizeof(s_in)); // connect the socket with the addres of s_in and the port sizeof(s_in)

  while(1) {
    fsize = sizeof(from); //insert the size of from to fsize
    cc = recvfrom(socket_fd,&get_message,1000,0,(struct sockaddr *)&from,&fsize); //insert cc the size of the message uoi you got
    sendto(socket_fd,&send_message,1000,0,(struct sockaddr *)&from,fsize);
    printsin( &from, "recv_udp: ", "Packet from:");
    printf("Got data ::%s\n",get_message); 
    fflush(stdout);
  }
  
  return 0;
}
