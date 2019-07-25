#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/un.h>
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
  auto struct sockaddr_un server_address;

  server_sockfd = socket(AF_UNIX, SOCK_STREAM, 0);
  
  server_address.sun_family = AF_UNIX;
  strcpy(server_address.sun_path, SOCKET_NAME);

  if( 0 == connect(server_sockfd, (struct sockaddr*) &server_address, sizeof(server_address)) ) {
    while(1) {
      scanf("%s", buf);
      send(server_sockfd, buf, LEN, 0);
      if( 0 == strcmp(buf, "quit")) {
        break;
      }
    }

    close(server_sockfd);
  }
}