// ============================================================================
// File: fcserver.c (Spring 2019)
// ============================================================================
// This is the file transfer server program. A client connects to this server
// and sends the name of a file that is about to be sent, followed immediately
// by the contents of the file.
// 
// The server extracts the filename from the first transmission and uses it to
// open a local output file. Then any remaining bytes the client sends are 
// written to the output file, creating a copy of the client file.
// ============================================================================

#include    <arpa/inet.h>
#include    <sys/types.h>
#include    <sys/socket.h>
#include    <stdio.h>
#include    <stdlib.h>
#include    <sys/un.h>
#include    <unistd.h>
#include    <string.h>
#include    <netinet/in.h>

// defined constants
#define BUFLEN          256
#define SERVER_PORT     50007
#define TRUE            1
#define FALSE           0

// function prototypes
long    CopyFile(int  src_sock);


// ==== main ==================================================================
//
// ============================================================================

int     main(void)
{
    auto    char                buf[BUFLEN];
    auto    socklen_t           client_addr_size;  // used for call to 'accept'
    auto    int                 client_socket;     // used for call to 'accept'
    auto    int                 server_socket;     // used for call to 'socket'
    auto    int                 file_size;         // used for call to 'CopyFile'
    auto    struct sockaddr_in  client_address;    // used for call to 'accept'
    auto    struct sockaddr_in  server_address;    // used for call to bind

    // greet the user
    puts("Welcome to fcserver!");
    puts("Waiting to recieve file from client...");

    // create a socket for the server
    server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (-1 == server_socket)
        {
        perror("fcserver -- socket failed");
        exit(EXIT_FAILURE);
        }

    // prepare the TCP socket address structure so the server will accept
    // connections from any client (e.g., INADDR_ANY)
    memset(&server_address, 0, sizeof(server_address));
    server_address.sin_family = AF_INET;
    server_address.sin_addr.s_addr = htonl(INADDR_ANY);
    server_address.sin_port = htons(SERVER_PORT);

    // bind the server socket to an address, using the address structure
    if (bind(server_socket, (struct sockaddr*)&server_address
                                        , sizeof(server_address)))
        {
        perror("fcserver -- bind failed");
        close(server_socket);
        exit(EXIT_FAILURE);
        }

    // put the server socket into a listening state
    if (listen(server_socket, 5))
        {
        perror("server -- listen failed");
        exit(EXIT_FAILURE);
        }   

    // let stdout know the server is waiting for a connection
    puts("server waiting...");

    // wait for an actual client connection (this will block...)
    client_addr_size = sizeof(client_address);
    client_socket = accept(server_socket, (struct sockaddr*)&client_address
                                                        , &client_addr_size);

    // if the connection fails, write an error message and exit, otherwise
    // display a 'success' message and the IP address of the client to stdout
    // (hint: try the 'inet_ntop' function...)
    if (-1 == client_socket)
        {
        perror("fcserver -- accept failed");
        close(server_socket);
        exit(EXIT_FAILURE);
        }
    else
        {
            inet_ntop(AF_INET, &client_address.sin_addr.s_addr, buf, BUFLEN);
            printf("Success! Client IP address: %s\n", buf);
        }

    // client is connected, and the socket representing this connection
    // is returned by the 'accept' function, so forward the socket to
    // the 'CopyFile' function so the file from the client can be
    // received
    file_size = CopyFile(client_socket);
    printf("*** fcserver -- CopyFile returned %ld\n", file_size);

    // close the client and server sockets
    close(client_socket);
    close(server_socket);
    return 0;

}  // end of "main"



// ==== CopyFile ==============================================================
// 
// This function uses the socket parameter to create a local copy of the file
// that's being sent through the connection. The first block of data read from
// the client socket contains a null-terminated filename, which is used to
// create an output file. Then, any remaining bytes following the filename are
// written to the output file, creating a copy. Once there are no more bytes
// being sent through the socket, the file is closed.
// 
// Input:
//      src_sock [IN]   -- a socket descriptor that represents the current
//                         connection with the client
// 
// Output:
//      If no errors occur, the total number of bytes written to the output
//      file is returned; else, a value of -1 to indicate error
// 
// ============================================================================

long    CopyFile(int  src_sock)
{
    auto    char            buf[BUFLEN];       // dest buffer for 'recv'
    auto    char            fname[BUFLEN];     // name of file from client
    auto    FILE            *fptr;             // used to open output file
    auto    int             num_client_bytes;  // return value from 'recv'
    auto    long            total_bytes = 0;   // total # bytes written to file

    // get the filename from the client (should be a null-terminated string)
    num_client_bytes = recv(src_sock, buf, BUFLEN, 0);
    if (-1 == num_client_bytes)
        {
        perror("fcserver, CopyFile -- failed to get filename");
        return -1L;
        }

    // the data should begin with the filename as a null-terminated string,
    // so extract the filename
    auto int offset = 0;
    for(; offset < num_client_bytes; ++offset) {
        fname[offset] = buf[offset];

        if(buf[offset] == 0) {
            break;
        }
        total_bytes++;
    }


    // open an output file
    fptr = fopen(fname, "w");
    if(fptr == NULL) {
        return 0;
    }

    // adjust the number of bytes to write to the output file so that it doesn't
    // include the filename, and use the result to write the rest of the data to
    // the output file
    offset = offset+1;
    fwrite(buf+offset, BUFLEN-offset, 1, fptr);


    // read the rest of the file from the client
    do  {
        // try to read a full buffer from the input stream; if successful,
        // write a message to stdout indicating how many bytes were read
        // and write the data to the output file, but if no bytes were
        // read, break out of the loopp
        num_client_bytes = recv(src_sock, buf, BUFLEN, 0);

        if(num_client_bytes == 0) {
            break;
        }

        if (-1 == num_client_bytes)
            {
            perror("fcserver, CopyFile -- failed to get filename");
            return -1L;
            }

            fwrite(buf, BUFLEN, 1, fptr);
            printf("%d bytes were read and written to disk\n", num_client_bytes);
            total_bytes += num_client_bytes;


        } while (TRUE);

    // close the output file stream
    fclose(fptr);


    // write a summary message to stdout indicating how many bytes were
    // written to the output file, and the name of the output file
    printf("%d bytes were written to the outputfile: %s\n", total_bytes, fname);


    // return the total number of bytes written to the output file
    return total_bytes;

}  // end of "CopyFile"
