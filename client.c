#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <unistd.h>

#define SIZE 1024
char buf[SIZE];

int main(int argc, char *argv[]) {

    char * fileName = argv[1];
    char * IPtoConnectTo = argv[2];
    int serverPort = atoi(argv[3]);
    int sockfd;
    int nread;
    struct sockaddr_in serv_addr;
    struct hostent *h;


    /* if number of arguments is not 4, throw error */
    if (argc != 4) {
        fprintf(stderr, "usage: %s wordToReplace Port\n", argv[0]);
        exit(1);
    }


    /* create socket client-side */
    sockfd = socket(AF_INET, SOCK_STREAM, 0);


    /* connect to server */
    serv_addr.sin_family = AF_INET;
    h = gethostbyname(IPtoConnectTo);
    bcopy(h->h_addr, (char *) &serv_addr.sin_addr, h->h_length);
    serv_addr.sin_port = htons(serverPort);
    if (connect(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)));


    /* transfer data */
    send(sockfd, argv[1],strlen(argv[1]), 0);

    fprintf(stderr,"Requested %s\n",argv[1]);
    fprintf(stderr, "Receiving file...\n");



    //nread = read(sockfd, buf, SIZE);
    //write(1, buf, nread); // Writes to standard output
    close(sockfd);
    exit(0);

}
