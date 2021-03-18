// NMAE: AUSTIN REEVES
// EUID: AWR0047


#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
 
int main(int argc, char *argv[])
{
	int listenfd = 0, connfd = 0, cli_size, portno, nread;
	struct sockaddr_in serv_addr, cli_addr;

	char msgBuff[256];  
	char sendMsg[512];
 
	
	// checking for valid number of arguments
        if (argc != 2)
    	{
                fprintf(stderr, "usage: %s <svr_port>\n", argv[0]);
        	exit(EXIT_FAILURE);
    	}
	
	// creating the socker
	if ((listenfd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
	{
		printf("socket error\n");
		exit(EXIT_FAILURE);
	}

	// allocating buffer memory
	memset(&serv_addr, '0', sizeof(serv_addr));
	memset(msgBuff, '0', sizeof(msgBuff));
	memset(sendMsg, '0', sizeof(sendMsg));

	// setting address
	serv_addr.sin_family = AF_INET;    
	serv_addr.sin_addr.s_addr = htonl(INADDR_ANY); 
	portno = atoi(argv[1]);
	serv_addr.sin_port = htons(portno);  

	int on = 1;
	setsockopt(listenfd, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on));

	// binding the sockets
	if (bind(listenfd, (struct sockaddr *)&serv_addr, sizeof(struct sockaddr)) == -1)
	{
		printf("bind error\n");
		exit(EXIT_FAILURE);
	}

	// listening for cnnections
	if (listen(listenfd, 10) == -1)
	{
		printf("listen error\n");
		exit(EXIT_FAILURE);
	}

	// accepting the connection
	cli_size = sizeof(cli_addr);
        if ((connfd = accept(listenfd, (struct sockaddr *)&cli_addr, &cli_size)) == -1)
        {
        	printf("accept error\n");
               	exit(EXIT_FAILURE);
        }

	// looping forever
	while (1)
	{
		// variables for the characters being counted
		int numSpaces = 0, numVowels = 0, numLetters = 0;
		
		// clearing buffers
		bzero(msgBuff, sizeof(msgBuff));
		bzero(sendMsg, sizeof(sendMsg));

		// waiting for an input string
		strcpy(sendMsg, "\nEnter a string: ");
                write(connfd, sendMsg, strlen(sendMsg));
		nread = recv(connfd, msgBuff, sizeof(msgBuff), 0);
		
		// checking for quit message from user
		if(strcmp(msgBuff, "quit\n") == 0)
		{
			strcpy(msgBuff, "Goodbye!\n");
			write(connfd, msgBuff, strlen(msgBuff));
			close(connfd);
		}


		// sending back the input string
		strcpy(sendMsg, "\nInput:  ");
		write(connfd, sendMsg, strlen(sendMsg));
                write(connfd, msgBuff, strlen(msgBuff));

		// looping through every character in the recieved string
		for(int i = 0; i < strlen(msgBuff); i++) {

			// making every capitol letter lowercase
			if(msgBuff[i] >= 'A' && msgBuff[i] <= 'Z')
			{
         			msgBuff[i] = msgBuff[i] + 32;
			}
			// counting number of spaces
			else if(msgBuff[i] == ' ')
			{
				numSpaces++;
			}
			
			// counting every vowel
			if(msgBuff[i] == 'a' || msgBuff[i] == 'e' || msgBuff[i] == 'i' || msgBuff[i] == 'o' || msgBuff[i] == 'u')
			{
				numVowels++;
			}

			// counting every letter
			if(msgBuff[i] >= 'a' && msgBuff[i] <= 'z')
			{
				numLetters++;
			}
		}

		// capitalizing the first leter
		msgBuff[0] = msgBuff[0] - 32;

		// sending back the processed output
		strcpy(sendMsg, "Output: ");
                write(connfd, sendMsg, strlen(sendMsg));
                write(connfd, msgBuff, strlen(msgBuff));
		sprintf(sendMsg, "\tSpaces: %d\n\tVowels: %d\n\tLetters: %d\n", numSpaces, numVowels, numLetters);
		write(connfd, sendMsg, strlen(sendMsg));

	} 
 
	return 0;
}

