#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/un.h>
#include <unistd.h>
#include <string.h>
#include <pthread.h>
#include <netinet/in.h>


#define LEN             256
#define SOCKET_NAME     "server_socket"

void* ThreadFunc(void* vPtr);

// == main
//
// ==

int client_sock_list[100];
int numClients = 0;


int main(void) {
  auto int                server_sockfd;
  auto int                client_sockfd;
  auto socklen_t          client_len;
  auto struct sockaddr_in server_address;
  auto struct sockaddr_in client_address;


  memset(&server_address, 0, sizeof(server_address));
  memset(&client_address, 0, sizeof(client_address));
  

  auto pthread_t threadID;

  server_sockfd = socket(AF_INET, SOCK_STREAM, 0);

  server_address.sin_family = AF_INET;
  server_address.sin_addr.s_addr = htonl(INADDR_ANY);
  server_address.sin_port = htons(50007);

  if(bind(server_sockfd, 
          (struct sockaddr*) &server_address,
          sizeof(server_address))) {
    perror("server -- bind failed");
  }
  
  while(1) {
    printf("There %s currently %d client%s. Server waiting...\n", 
                      (numClients == 1)? "is" : "are", 
                      numClients,
                      (numClients == 1)? "" : "s");
    if(listen(server_sockfd, 5)) {
      perror("server -- listen failed");
    }

    

    client_len = sizeof(client_address);
    client_sockfd = accept(server_sockfd, 
                          (struct sockaddr*) &client_address,
                          &client_len);

    if(pthread_create(&threadID, NULL, ThreadFunc, &client_sockfd)) {
        // error
    }
    client_sock_list[numClients] = client_sockfd;
    numClients++;

  }

  close(server_sockfd);
  
  return 0;
}

void* ThreadFunc(void* vPtr) {
  auto int client_sockfd = *((int*) vPtr);
  auto ssize_t num_client_bytes;
  auto char               buf[LEN];

  while(1) {
    num_client_bytes = recv(client_sockfd, buf, LEN, 0);
    // if( 0 == strcmp(buf, "quit")) {
    //   break;
    // }
    if(-1 == num_client_bytes) {
      perror("server -- recv failed");
    } else if (0 == num_client_bytes) {
      perror("Client unexpectedly lost connection");
      break;
    } else {
      printf("client message: %s\n", buf);
      for(int i = 0; i < numClients; i++) {
        send(client_sock_list[i], buf, LEN, 0);
      }
    }
  }

  close(client_sockfd);
}; 
