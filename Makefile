CC = gcc
CFLAGS = -Wall

all: fservidor.o fclient.o
	$(CC) $(CFLAGS) -o client client.c common.c fclient.o
	$(CC) $(CFLAGS) -o servidor servidor.c common.c fservidor.o

clean:
	rm *.o
	rm client
	rm servidor

fclient.o:
fservidor.o:
