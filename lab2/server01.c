#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/un.h>
#include <unistd.h>
#include <string.h>
#include <netinet/in.h>

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
  auto struct sockaddr_in server_address;
  auto struct sockaddr_in client_address;

  memset(&server_address, 0, sizeof(server_address));
  memset(&client_address, 0, sizeof(client_address));


  server_sockfd = socket(AF_INET, SOCK_STREAM, 0);

  server_address.sin_family = AF_INET;
  server_address.sin_addr.s_addr = htonl(INADDR_ANY);
  server_address.sin_port = htons(50007);
  
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


  close(client_sockfd);
  close(server_sockfd);
  
  return 0;
}