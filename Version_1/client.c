/*
    This source file is for sending signals
*/

#include "shared.h"

void main () {

    // Getting the server pid from shared memory segment
     pid_t *pid=create_shared_memory();

    // Sending signals for SIGNAL_NUMBER time 
     send_signal(*pid);
}