#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <time.h>
#include <unistd.h>

#define SIZE 1024
char buf[SIZE];
int words = 0;

char * censor(char * line, char * word);

int main(int argc, char *argv[]) {

    int proxyPort = atoi(argv[2]);
    int sockfd, client_sockfd;
    int nread, len;
    struct sockaddr_in serv_addr, client_addr;


    /* if number of arguments is less than 2, throw error */
    if (argc != 3) {
        fprintf(stderr, "usage: %s wordToReplace Port\n", argv[0]);
        exit(1);
    }

    /* create socket server-side */
    sockfd = socket(AF_INET, SOCK_STREAM, 0);


    /* bind address */
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_addr.sin_port = htons(proxyPort);
    bind(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr));


    /* specify queue */
    len = sizeof(client_addr);

    /* listen */
    listen(sockfd, 5);


    for (;;) {

        /* accept() connection */
        client_sockfd = accept(sockfd, (struct sockaddr *)&client_addr, &len);

        /* transfer data */


        recv(client_sockfd, buf, SIZE, 0);
        fprintf(stderr,"Downloading %s\n",buf);
        char cmd[] = "curl http://user.engineering.uiowa.edu/~jwryan/Communication_Networks/";
        strcat(cmd, buf);
        char param[] = " -o ";
        strcat(cmd, param);
        strcat(cmd, buf);

        int status = system(cmd);

        if(status == -1){
            fprintf(stderr,"error");
        }

        FILE * file;
        file = fopen(buf,"r");

        ssize_t len;
        size_t length;
        char *line = NULL;
        words = 0;
        while((len = getline(&line,&length,file)) != -1){
            char * newline = NULL;
            newline = censor(line,argv[1]);
            write(client_sockfd,newline,len);
        }
        fprintf(stderr,"Replacement count: %d\n", words);
        fclose(file);
        fprintf(stderr,"Closing connection");











        //len = strlen("hello world") + 1;
        //write(client_sockfd, "hello world", len);

        /*close socket*/
        close(client_sockfd);
    }
}

char * censor(char * line, char * word) {
    size_t swearLength = strlen(word); // swear is assumed null-terminated
    char *here = line;
    while ((here = strstr(here, word))) {
    memset(here, '*', swearLength);
    here += swearLength;  // to avoid searching what's already censored
    words++;
    }
    return here;
}