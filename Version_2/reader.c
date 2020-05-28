#include "msg_queue.h"


int main(){


    int msg_id;


    int arr[10]= {1,2,2,1,1,2,2,1,2,1};

    msg_id = create_queue();

    if(msg_id<0){
        printf("Failed to create message queue\n");
        exit(-1);
    }else{
        printf("Server wait for message!\n");
    }


    for(int i=0;i<10;i++){
        read_haiku(msg_id,arr[i]);
        sleep(1);
    }


return 0;


}