/*
  This source file is for writing Haikus to message queue 
*/
#include "msg_queue.h"

void main(){


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
    printf("loading");
   
   // filling queue until it is removed by reader
   while(1){

        // if there is 0 Haiku in message queue, refill it
        if(buf.msg_qnum == 0){
            fill_msg_queue(msg_id);
        }
        
       //printf("%ld\n",buf.msg_qnum );
    }




}