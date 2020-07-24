/* This application may be used by administrators to verify security policies of their networks 
and by attackers to identify network services running on a host and exploit vulnerabilities */

#include <stdio.h>
#include <sys/socket.h> //main sockets header
#include <errno.h>
#include <netdb.h> //network database operations
#include <string.h>
#include <stdlib.h>

int main(int argc, char **argv){

    struct hostent *host;
    int err, i, sock, start, end;
    char host_name[100];
    struct sockaddr_in sa;

    printf("Enter your hostname or IP address:");
    gets(host_name);

    printf("\n");

    printf("Enter the starting port number: ");
    scanf("%d", &start);

    printf("\n");

    printf("Enter the ending port number: ");
    scanf("%d", &end);

    strncpy((char*)&sa, "", sizeof sa);
    sa.sin_family = AF_INET;

    if(isdigit(host_name[0])){
        sa.sin_addr.s_addr = inet_addr(host_name);
    }
    else if (  (host = gethostbyname(host_name)) != 0){
        strncpy((char*)&sa.sin_addr, (char*) host->h_addr, sizeof sa.sin_addr);
    }
    else {
        herror(host_name);
        exit(2);
    }

    for(i = start;  i <= end; i++){
        printf("Scanning port %i\n",i);

        sa.sin_port = htons(i);
        sock = socket(AF_INET, SOCK_STREAM, 0);

        if(socket < 0){
            exit(1);
        }

        err = connect(sock, (struct sockaddr*)&sa, sizeof sa);

        if (err < 0){
            fflush(stdout);
        }
        else {
            printf("Port %i is open\n", i);
        }
        close(sock);
    }
    fflush(stdout);
    return 0;
}
