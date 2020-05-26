#include "msg_queue.h"

void main(){


    int msg_id;
    int rc;
    struct msqid_ds buf;
    
    msg_id=access_queue();

    rc = msgctl(msg_id, IPC_STAT, &buf);
    printf("loading");
    fill_msg_queue(msg_id);
     printf("%ld\n",buf.msg_qnum );
  /*  while(1){

        if(buf.msg_qnum == 0){
            fill_msg_queue(msg_id);
        }
        printf("%ld\n",buf.msg_qnum );
    }*/




}