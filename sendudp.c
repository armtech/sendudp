/* 
 * sendudp.c
 *
 * A simple UDP sender with multicast addressing.
 * This mechanism based on the Simple Service Discovery Protocol (SSDP)
 * Reference:  https://tools.ietf.org/html/draft-cai-ssdp-v1-00
 *
 * THE SOFTWARE IS PROVIDED "AS IS", 
 * WITHOUT WARRANTY OF ANY KIND!
 *
 * Author: Andrejs Tihomirovs
 * Email: armtech@its.lv
 */

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h> 

int main(int argc, char *argv[])
{

	const char MSGHELLO[] = "\"Hello, everybody!\"";
	const int DELAY_SEC = 1;	// loop delay in seconds
	char *group = argv[1]; 		// must have: 239.255.255.250
	int port = atoi(argv[2]); 	// must have: 1900
	
	// checking command line arguments
	if (argc != 3) {
		printf("sendudp: Invalid argument\n");
		printf("Try `sendudp 239.255.255.250 1900`\n");
		return 1;
	}

	// create UDP socket
	int sockfd;
	if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
		perror("sendudp");
		return 1;
	}

	// set up destination address
	struct sockaddr_in addr;
	memset(&addr, 0, sizeof(addr));
	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = inet_addr(group);
	addr.sin_port = htons(port);

	// main loop
	while (1) {
		#define BUFSIZE 256
		char buf[BUFSIZE];
		const char *message = buf;
		static int count = 1;

		// make a message
		memset(buf, 0, sizeof(buf));
		sprintf(buf, "ID:%05d\nMESSAGE:%s\n", count, MSGHELLO);

		// send UDP message
		int nbytes = sendto(sockfd, message, strlen(buf), 0,
			(struct sockaddr*) &addr, sizeof(addr));
			
		if (nbytes < 0) {
			perror("sendudp");
			return 1;
		} 

		printf("\rSending a UDP multicast message ID:%05d", count++);
		fflush(stdout);
        sleep(DELAY_SEC);
	}

    return 0;
}
