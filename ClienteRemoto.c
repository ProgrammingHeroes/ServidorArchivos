
// ClienteRemoto.c ------------------------------------------------------------

#include "Sockets.h"


int main(int argc, char* argv[])
{
	if (argc == 4)
	{
		int socketDescriptor = createInetStreamSocket();
		connectToInetServer(socketDescriptor, PORT, argv[1]);
		
		printf("%sConnected successful.%s\n", BLUE, RESET_COLOR);

		Message message;
		strcpy(message, argv[2]);
		writeMessage(socketDescriptor, message, sizeof(message));
		printf("I've requested for: \"%s\"\n", message);

		Code size = 4;
		readCode(socketDescriptor, &size);

		printf("Code: %d\n", size);

		if (size == FILE_NOT_FOUND)
		{
			printf("%sError, file not found.%s\n", RED, RESET_COLOR);
		}
		else
		{
			Message message;
			int fileDescriptor = creat(argv[3], 0777);
			while (size > 0)
			{
				int readCode = readMessage(socketDescriptor, &message, sizeof(message));
				int writeCode = writeMessage(fileDescriptor, message, readCode);
				//write(1, message, readCode);
				size -= readCode;
			}
			close(fileDescriptor);
		}
		
		close(socketDescriptor);
		printf("%sServer connexion closed, socket closed.%s\n", RED, RESET_COLOR);
	}
	else
	{
		perror("Invalid sintax. Use: ClienteRemoto IP SERVER_FILE CLIENT_FILE\n");
		exit(-1);
	}
}

// ClienteRemoto.c ------------------------------------------------------------
