/*
  This source file is for receiving signals 
*/

#include "shared.h"

int main(void)
{

  // Initializing shared memory segment and putting server process pid into it
  pid=create_shared_memory();
  *pid = getpid();

  // Receiving and printing signals for signal number for SIGNAL_NUMBER times
  while(signal_counter<SIGNAL_NUMBER) {

    receive_signal();
    sleep(1);

  }

  printf("\n\nServer finished its all work\n\n");

  return 0;
}