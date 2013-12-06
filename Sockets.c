
#include "Sockets.h"


int createInetStreamSocket()
{
	int socketDescriptor = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (socketDescriptor == -1)
	{
		perror(ERROR_SOCKET);
		exit(-1);
	}

	return socketDescriptor;
}

void listenAtPort(int socketDescriptor, int port, int maxQueue)
{
	struct sockaddr_in dir;
	bzero((char *) &dir, sizeof(dir)); // DELETE
	dir.sin_family = AF_INET;
	dir.sin_port = htons(port);
	dir.sin_addr.s_addr = INADDR_ANY;
	int bindCode = bind(socketDescriptor, (struct sockaddr*)&dir, sizeof(dir));
	if (bindCode == -1)
	{
		perror(ERROR_BIND);
		close(socketDescriptor);
		exit(-1);
	}

	int listenCode = listen(socketDescriptor, maxQueue);
	if (listenCode == -1)
	{
		perror(ERROR_LISTEN);
		close(socketDescriptor);
		exit(-1);
	}
}

int getClient(int socketDescriptor)
{
	struct sockaddr client;
	int clientLength = sizeof(client);
	int clientDescriptor = accept(socketDescriptor, &client, &clientLength);
	if (clientDescriptor == -1)
	{
		perror(ERROR_ACCEPT);
		close(socketDescriptor);
		exit(-1);
	}

	return clientDescriptor;
}

void connectToInetServer(int socket, int port, char * ip)
{
	struct sockaddr_in server;
	server.sin_family = AF_INET;
	server.sin_port = htons(port);
	server.sin_addr.s_addr = inet_addr(ip);
	int connectCode = connect(socket,
			(struct sockaddr *) &server, sizeof(server));
	if (connectCode == -1)
	{
		perror(ERROR_CONNECT);
		close(socket);
		exit(-1);
	}
}

int getSize(char* filename)
{
	struct stat staticstics;
	stat(filename, &staticstics);

	return staticstics.st_size;
}

int writeCode(int descriptor, Code code)
{
	code = htonl(code);
	int writeCode = write(descriptor, &code, sizeof(code));
	if (writeCode == -1)
	{
		perror(ERROR_WRITE);
		close(descriptor);
		exit(-1);
	}

	return writeCode;
}

int readCode(int descriptor, Code * code)
{
	int readCode = read(descriptor, code, sizeof(*code));
	if (readCode == -1)
	{
		perror(ERROR_WRITE);
		close(descriptor);
		exit(-1);
	}
	(*code) = ntohl(*code);

	return readCode;
}

int writeMessage(int descriptor, Message msg, int bytes)
{
	int writeCode = write(descriptor, msg, bytes);
	if (writeCode == -1)
	{
		perror(ERROR_WRITE);
		close(descriptor);
		exit(-1);
	}

	return writeCode;
}

int readMessage(int descriptor, Message * msg, int bytes)
{
	int readCode = read(descriptor, msg, bytes);
	if (readCode == -1)
	{
		perror(ERROR_READ);
		close(descriptor);
		exit(-1);
	}

	return readCode;
}
