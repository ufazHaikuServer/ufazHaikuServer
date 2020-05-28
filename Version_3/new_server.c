#include "server_client.h"


int main(){


    pid=create_shared_memory();
    *pid = getpid();
    
    printf("Now server is receiving signals from client. It will take a little bit time. Please, wait\n");
    while(signal_counter<10) {
     receive_signal();
     sleep(1);
    }
    print(2,100,matrix);


    int msg_id;

    msg_id = create_queue();

    if(msg_id<0){
        printf("Failed to create message queue\n");
        exit(-1);
    }else{
      //  printf("Server wait for message!\n");
    }

    printf("Now server is reading Haikus\n");
    for(int i=1;i<=100;i++){
        printf("==========================================");
        read_haiku(msg_id,find_catagory(2,100,matrix,i));
        sleep(1);
    }






    return 0;
}