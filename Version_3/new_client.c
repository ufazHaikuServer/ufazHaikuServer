/*
    This source file is the client that sends signals to server and 
    writes Haikus into message queue with heir category 

    We have used the header files of Version 1 and Version 2
    
*/

#include "../Version_1/shared.h"
#include "../Version_2/msg_queue.h"


int main(){

    // Getting the server pid from shared memory segment
     pid_t *pid=create_shared_memory();

    // Sending signals for SIGNAL_NUMBER time 
     send_signal(*pid);


    int msg_id;
    int rc;
    struct msqid_ds buf;
    
    // accessing created queue by reader
    msg_id=access_queue();

    /*  Copy information from the kernel data structure associated
        with msg_id into the msqid_ds structure pointed to by buf.  The
        caller must have read permission on the message queue.
    */ 
    rc = msgctl(msg_id, IPC_STAT, &buf);
   
   // filling queue until it is removed by reader
   while(1){

       // if there is 0 Haiku in message queue, refill it
        if(buf.msg_qnum == 0){
            fill_msg_queue(msg_id);
        }

    }


    return 0;
}