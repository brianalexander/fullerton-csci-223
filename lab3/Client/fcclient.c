// ============================================================================
// File: fcclient.c (Spring 2019)
// ============================================================================
// This program is a file transfer client. The user at the keyboard is prompted
// to enter the name of a file to send to the server. If the file is opened,
// the filename is sent to the server, followed by the entire contents of the
// file.
// ============================================================================

#include    <sys/types.h>
#include    <sys/socket.h>
#include    <stdio.h>
#include    <stdlib.h>
#include    <sys/un.h>
#include    <unistd.h>
#include    <string.h>
#include    <netinet/in.h>

#define BUFLEN          256
#define SERVER_PORT     50007         


// ==== main ==================================================================
//
// ============================================================================

int     main(void)
{
    auto    int                 socknum;         // return value from 'socket'
    auto    struct sockaddr_in  server_address;  // server address information
    auto    char                fname[BUFLEN];   // name of file to send
    auto    char                *bufptr;         // ptr to heap block
    auto    FILE                *fptr;           // FILE ptr to input file
    auto    int                 result;          // for retval of 'connect', 'send'...
    auto    long                fileSize;        // size of file to send

    // greet the user
    puts("Welcome to fcclient!");

    // get the filename from stdin
    printf("Please enter the name of the file to transfer: ");
    if (!fgets(fname, BUFLEN, stdin))
        {
        perror("fcclient -- unable to read the filename...");
        exit(EXIT_FAILURE);
        }
    else
        {
        // strip the trailing newline
        fname[strlen(fname) - 1] = 0;
        }
    
    // open the input file
    fptr = fopen(fname, "r");
    if (NULL == fptr)
        {
        perror("fcclient -- fopen failed");
        exit(EXIT_FAILURE);
        }

    // get the size of the file
    if (fseek(fptr, 0, SEEK_END))
        {
        perror("fcclient -- fseek failed");
        exit(EXIT_FAILURE);
        }
    fileSize = ftell(fptr);
    rewind(fptr);

    // allocate a buffer to store the file in heap memory
    if (NULL == (bufptr = malloc(fileSize)))
        {
        perror("fcclient -- malloc failed");
        fclose(fptr);
        exit(EXIT_FAILURE);
        }

    // create a socket to connect with the server
    socknum = socket(AF_INET, SOCK_STREAM, 0);
    if (-1 == socknum)
        {
        perror("fcclient -- socket failed");
        fclose(fptr);
        free(bufptr);
        exit(EXIT_FAILURE);
        }

    // setup a socket address structure to target the server
    memset(&server_address, 0, sizeof(server_address));
    server_address.sin_family = AF_INET;
    server_address.sin_addr.s_addr = htonl(INADDR_LOOPBACK);
    server_address.sin_port = htons(SERVER_PORT);

    // connect to the server
    result = connect(socknum, (const struct sockaddr*)&server_address
                                                  , sizeof(server_address));
    if (-1 == result)
        {
        perror("fcclient -- connect failed");
        free(bufptr);
        fclose(fptr);
        exit(EXIT_FAILURE);
        }

    // send the filename to the server (don't forget to include the NULL!)
    result = send(socknum, fname, strlen(fname) + 1, 0);
    if (-1 == result)
        {  
        perror("fcclient -- failed to send filename to server");
        free(bufptr);
        fclose(fptr);
        exit(EXIT_FAILURE);
        }

    // read the entire file into the allocated buffer
    if (1 != fread(bufptr, fileSize, 1, fptr))
        {
        perror("fcclient -- fread failed");
        free(bufptr);
        fclose(fptr);                                                 
        exit(EXIT_FAILURE);
        }

    // send the file data to the server
    result = send(socknum, bufptr, fileSize, 0);
    if (-1 == result)
        {
        perror("fcclient: send");
        }
    else
        {
        printf("fcclient: %s sent to server!\n", fname);
        }

    // close the input file and the sockets
    free(bufptr);
    fclose(fptr);
    close(socknum);
    return 0;

}  // end of "main"
