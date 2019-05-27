#include <sys/types.h>
#include <netinet/in.h>
#include <inttypes.h>
#include <netdb.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <strings.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>

int main(int argc, char *argv[])
{
  int socket_fd, dsize;
  struct sockaddr_in  dest;
  struct hostent *hostptr;
  struct { char head; u_long body; char tail; } msgbuf;
  char send_message[] = "Mimoun";
  char get_message[1000];

  socket_fd = socket (AF_INET, SOCK_DGRAM, 0);//Create socket to connect to him
  memset((char *) &dest,0, sizeof(dest)); /* They say you must do this *///this function delet the firs "sizeof" chars of s_in and insert '0' instead.
  hostptr = gethostbyname(argv[1]);//resolve the dest hostname recieved as an argument
  dest.sin_family = (short) AF_INET;//insert IPv4 to s_in 
  memcpy(hostptr->h_addr, (char *)&dest.sin_addr,hostptr->h_length);//copy the dest address to our hostent struct
  dest.sin_port = htons((u_short)0x3333);//set destanation port

  msgbuf.head = '<';
  msgbuf.body = htonl(getpid()); /* IMPORTANT! */
  msgbuf.tail = '>';

  dsize=sizeof(dest);
  sendto(socket_fd,&send_message,1000,0,(struct sockaddr *)&dest, sizeof(dest));//the function returns how many bits were sent
   recvfrom(socket_fd,&get_message,1000,0,(struct sockaddr *)&dest,&dsize);
   printf("Got data ::%s \n",get_message); 
   fflush(stdout);

  return 0;
}