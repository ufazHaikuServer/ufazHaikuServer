#include "server_client.h"


int main(){

     pid_t *pid=create_shared_memory();
     send_signal(*pid, 10);


    int msg_id;
    int rc;
    struct msqid_ds buf;
    
    msg_id=access_queue();

    rc = msgctl(msg_id, IPC_STAT, &buf);
   
   
   while(1){

        if(buf.msg_qnum == 0){
            fill_msg_queue(msg_id);
             //printf("loadiiiiiiiiing\n");
        }
     //  printf("%ld\n",buf.msg_qnum );
    }


    return 0;
}