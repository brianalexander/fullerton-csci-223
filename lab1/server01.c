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
  auto int                client_sockfd;
  auto socklen_t          client_len;
  auto ssize_t            num_client_bytes;
  auto struct sockaddr_un server_address;
  auto struct sockaddr_un client_address;

  unlink(SOCKET_NAME);
  server_sockfd = socket(AF_UNIX, SOCK_STREAM, 0);

  server_address.sun_family = AF_UNIX;
  strcpy(server_address.sun_path, SOCKET_NAME);
  if(bind(server_sockfd, 
          (struct sockaddr*) &server_address,
          sizeof(server_address))) {
    perror("server -- bind failed");
  }
  
  if(listen(server_sockfd, 5)) {
    perror("server -- listen failed");
  }

  puts("server waiting...");

  client_len = sizeof(client_address);
  client_sockfd = accept(server_sockfd, 
                        (struct sockaddr*) &client_address,
                        &client_len);
  
  while(1) {
    num_client_bytes = recv(client_sockfd, buf, LEN, 0);
    if( 0 == strcmp(buf, "quit")) {
      printf("Client has closed the connection\n");
      break;
    } else if (0 == num_client_bytes) {
      perror("Client unexpectedly lost connection");
      break;
    }
    if(-1 == num_client_bytes ) {
      perror("server -- recv failed");
    } else {
      printf("client message: %s\n", buf);
    }
  }


  unlink(SOCKET_NAME);
  close(client_sockfd);
  close(server_sockfd);
  
  return 0;
}