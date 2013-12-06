
// ServidorRemoto.c -----------------------------------------------------------
// http://es.tldp.org/Tutoriales/PROG-SOCKETS/prog-sockets.html
// http://www.tutorialspoint.com/unix_sockets/socket_core_functions.htm


#include "Sockets.h"

#include <signal.h>

#define EXIT_COMMAND "exit"

void comunicate(int);
void listeningProcess(int);
void sendFile(int, int, int);

int main(int argc, char* argv[])
{
	int socketDescriptor = createInetStreamSocket();
	listenAtPort(socketDescriptor, PORT, MAX_CLIENTS_QUEUE);

	printf("%sServer listening in port %d.\n%s", WHITE, PORT, RESET_COLOR);
	printf("%sWrite \"exit\" to quit.%s\n", WHITE, RESET_COLOR);

	char command[10];

	int pid = fork();

	switch (pid)
	{
		case -1:
			perror("Error creating child process.\n");
			break;
		case 0:
			listeningProcess(socketDescriptor);
			exit(0);
		default:
			do
			{
				scanf("%s", command);
				if (strcmp(command, EXIT_COMMAND) != 0)
				{
					printf("%sInvalid command%s\n", RED, RESET_COLOR);
				}
			}
			while (strcmp(command, EXIT_COMMAND) != 0);
			break;
	}

	kill(pid, SIGKILL);
	wait();
	close(socketDescriptor);
	printf("%sSocket closed. Bye!%s\n", RED, RESET_COLOR);
}

void listeningProcess(int socketDescriptor)
{
	while (1)
	{
		int clientDescriptor = getClient(socketDescriptor);

		int pid_client = fork();
		switch (pid_client)
		{
			case -1:
				perror("Error creating fill process.\n");
				break;
			case  0:
				printf("%sClient connected.%s\n", BLUE, RESET_COLOR);
				comunicate(clientDescriptor);
				exit(0);
			default:
				break;
		}
	}
}

void comunicate(int clientDescriptor)
{
	Message fileName;
	readMessage(clientDescriptor, &fileName, sizeof(fileName));
	printf("%sThe client wants the file: \"%s\"%s\n",
			 GREEN, fileName, RESET_COLOR);

	int fileDescriptor = open(fileName, O_RDONLY);
	if (fileDescriptor < 0)
	{
		printf("%sError, file not found.%s\n", RED, RESET_COLOR);
		writeCode(clientDescriptor, FILE_NOT_FOUND);
	}
	else
	{
		int size =  getSize(fileName);
		printf("%sThe size of the file is %d.%s\n",
				GREEN, size, RESET_COLOR);
		sendFile(clientDescriptor, fileDescriptor, size);
	}

	close(fileDescriptor);
	close(clientDescriptor);
	printf("%sClient connexion closed.%s\n", YELLOW, RESET_COLOR);
}


void sendFile(int clientDescriptor, int fileDescriptor, int size)
{
	writeCode(clientDescriptor, size);

	int bytesSent = 0;
	Message message;
	printf("0%% send.\n");
	while (bytesSent < size)
	{
		int readCode = readMessage(fileDescriptor, &message, sizeof(message));		
		int writeCode = writeMessage(clientDescriptor, message, readCode);

		bytesSent += writeCode;
		printf("%d%% send.\n", (bytesSent*100)/size);
	}
}

// ServidorRemoto.c -----------------------------------------------------------
