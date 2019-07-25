#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define _XOPEN_SOURCE 500

void* ThreadFunc(void* vPtr);

int counter = 1;

int main(int argc, char* argv[]) {
  if(argc < 2) {
    printf("usage: %s <#primary microseconds> <thread #1 microseconds> <thread #2 microseconds>...\n", argv);
    exit(EXIT_FAILURE);
  }
  
  auto int mSecs = 0;
  auto pthread_t threadID;

  if( argc >= 3) {
    for( int i = 1; i < argc; i++) {
      sscanf(argv[i], "%i", &mSecs);
      if(pthread_create(&threadID, NULL, ThreadFunc, &mSecs)) {
        // error
      }
      counter++;
    }
  }

  sscanf(argv[1], "%d", &mSecs);

  while(1) {
    printf("primary thread at %d microseconds\n", argv[0]);
    usleep(mSecs);
  }

 return 0; 
}

void* ThreadFunc(void* vPtr) {
  auto int myInt = counter;
  auto int mSecs = *((int*) vPtr);
  while(1) {
    printf("Secondary thread #%d with %d microseconds...\n", myInt, mSecs);
    usleep(mSecs);
  }
}