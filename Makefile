# Makefile for ex2 part A

all: recv_udp send_udp

recv_udp: recv_udp.c
	gcc -o recv_udp recv_udp.c

send_udp: send_udp.c
	gcc -o send_udp send_udp.c

clean:
	rm -f *.o recv_udp send_udp

runs:
	./recv_udp

runc:
	./send_udp localhost

runs-strace:
	strace -f ./recv_udp

runc-strace:
	strace -f ./send_udp