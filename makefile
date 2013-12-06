CC=gcc

all: ServidorRemoto ClienteRemoto

ServidorRemoto: ServidorRemoto.o Sockets.o
	$(CC) ServidorRemoto.o Sockets.o -o ServidorRemoto

ServidorRemoto.o: ServidorRemoto.c Sockets.o
	$(CC) -c ServidorRemoto.c

ClienteRemoto: ClienteRemoto.o Sockets.o
	$(CC) ClienteRemoto.o Sockets.o -o ClienteRemoto

ClienteRemoto.o: ClienteRemoto.c Sockets.o
	$(CC) -c ClienteRemoto.c

Sockets.o: Sockets.c Sockets.h
	$(CC) -c Sockets.c

clean:
	rm *.o