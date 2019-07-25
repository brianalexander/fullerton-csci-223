#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/un.h>
#include <netinet/in.h>
#include <unistd.h>
#include <string.h>

#define LEN             256
#define SOCKET_NAME     "server_socket"

// == main
//
// ==

int main(void) {
  auto char               buf[LEN];
  auto int                server_sockfd;
  auto struct sockaddr_in server_address;

  memset(&server_address, 0, sizeof(server_address));

  server_sockfd = socket(AF_INET, SOCK_STREAM, 0);
  if (-1 == server_sockfd)
    {
    perror("server -- socket failed");
    exit(EXIT_FAILURE);
    }
  
  server_address.sin_family = AF_INET;
  server_address.sin_addr.s_addr = htonl(INADDR_LOOPBACK);
  server_address.sin_port = htons(50007);

  if( 0 == connect(server_sockfd, (struct sockaddr*) &server_address, sizeof(server_address)) ) {
    while(1) {
      fgets(buf, LEN, stdin);
      send(server_sockfd, buf, LEN, 0);
      if( 0 == strcmp(buf, "quit")) {
        break;
      }
    }

    close(server_sockfd);
  }
}