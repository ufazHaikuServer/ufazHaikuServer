/*
  This source file is for reading Haikus from message queue 
*/
#include "msg_queue.h"


int main(){


    int msg_id;

    // array which is holding Haiku category for testing read_haiku() function
    int arr[10]= {1,2,2,1,1,2,2,1,2,1};

    // creating message queue
    msg_id = create_queue();

    // if message queue couldn't be created
    if(msg_id<0){
        printf("Failed to create message queue\n");
        exit(-1);
    }else{
        printf("Server wait for message!\n");
    }

    // reading haikus from message queue
    for(int i=0;i<10;i++){

        // reading haikus for 3 time
        for(int j=0;j<3;j++){

            read_haiku(msg_id,arr[i]);
            
        }

        sleep(1);
    }

    // removing message queue after all works were done
    remove_queue(msg_id);

return 0;


}