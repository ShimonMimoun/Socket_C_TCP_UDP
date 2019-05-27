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
#include <stdlib.h>
#include <string.h>



int main(int argc, char *argv[])
{
  int socket_fd, cc, fsize;
  struct sockaddr_in  a,b,c, from;
  char msg[100];
  double x=0.3,random;


  random = (double)rand() / (double)RAND_MAX;
  printf("random= %lf, x= %lf\n",random,x);
   

   

  socket_fd = socket (AF_INET, SOCK_DGRAM, 0);

  memset((char *) &b,0, sizeof(b));  /* They say you must do this    */
  memset((char *) &c,0, sizeof(c));
  memset((char *) &a,0, sizeof(a));

  b.sin_family = (short)AF_INET;
  b.sin_addr.s_addr = htonl(INADDR_ANY);
  b.sin_port = 4444;                  //my port

  c.sin_family = (short)AF_INET;
  c.sin_addr.s_addr = htonl(INADDR_ANY);
  c.sin_port = 5555;                  //c port

  a.sin_family = (short)AF_INET;
  a.sin_addr.s_addr = htonl(INADDR_ANY);
  a.sin_port = 3333;                  //a port


  bind(socket_fd, (struct sockaddr *)&b, sizeof(b));// listening on 4444

  while(1) {
    fsize = sizeof(from);
    printf("hey");
    cc = recvfrom(socket_fd,&msg,100,0,(struct sockaddr *)&from,&fsize);
    printf("I Got msg");
    fflush(stdout);


    if(from.sin_port==3333){              //i got from a

      if(random>x){                       //if random bigger than X send the nsg to C
        random = (double)rand()/(double)(RAND_MAX);
        printf(" from A:\n\"%s\"\n",msg);
        fsize = sizeof(c);
        sendto(socket_fd,&msg,100,0,(struct sockaddr *)&c, fsize);
        printf("\nI decided to send the msg to C\n");
        fflush(stdout);
      }else{
        printf("I decided drop it down\n");
  }
      }else{
        printf(" from A:\n%s\n",msg);       //i got from c
        fsize = sizeof(a);
        sendto(socket_fd,&msg,100,0,(struct sockaddr *)&a, fsize);
        printf("I sent the msg to A\n");
        fflush(stdout);
      }
    }
  return 0;
}
