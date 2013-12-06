
#ifndef _SHOCKETS_H_
#define _SHOCKETS_H_

#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <fcntl.h>

#define PORT 9999
#define BUFFER_SIZE	50000
#define MAX_CLIENTS_QUEUE 1
#define FILE_NOT_FOUND -1

#define RESET_COLOR "\x1B[0m"
#define RED    "\x1B[31m"
#define GREEN  "\x1B[32m"
#define YELLOW "\x1B[33m"
#define BLUE   "\x1B[34m"
#define WHITE  "\x1B[37m"

#define ERROR_CONNECT "Error in connect()\n"
#define ERROR_BIND "Error in bind()\n"
#define ERROR_LISTEN "Error in listen()\n"
#define ERROR_ACCEPT "Error in accept()\n"
#define ERROR_SOCKET "Error in socket()\n"
#define ERROR_WRITE "Error in write()\n"
#define ERROR_READ "Error in read()\n"

typedef char Message[BUFFER_SIZE];
typedef int Code;

int createInetStreamSocket();
void listenAtPort(int, int, int);
int getClient(int);
void connectToInetServer(int, int, char*);

int getSize(char*);
int writeMessage(int, Message, int);
int readMessage(int, Message *, int);
int writeCode(int, Code);
int readCode(int, Code *);

#endif
