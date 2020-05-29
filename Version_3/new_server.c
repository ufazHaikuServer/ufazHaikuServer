/*
    This source file is the server that receives signals from client and prints to the screen
    the maching type of Haiku 

    We have used the header files of Version 1 and Version 2
    
*/

#include "../Version_1/shared.h"
#include "../Version_2/msg_queue.h"


int main(){

    // Initializing shared memory segment and putting server process pid into it
    pid=create_shared_memory();
    *pid = getpid();


    printf("\n==========================================\n");
    printf("Now server is receiving signals from client. It will take a little bit time. Please, wait\n");
    printf("==========================================\n");
    


    // Receiving and printing signals for signal number for SIGNAL_NUMBER times                                                                                                                                                            
    while(signal_counter<SIGNAL_NUMBER) {
        receive_signal();
        sleep(1);
    }
    
    // Printing Haiku category matrix after receiving all signals 
    printf("\n==========================================\n");
    print(2,SIGNAL_NUMBER,matrix);
    printf("\n==========================================\n");


    int msg_id;
    int haiku_category;


    // creating message queue
    msg_id = create_queue();

    // if message queue couldn't be created
    if(msg_id<0){
        printf("Failed to create message queue\n");
        exit(-1);
    }


    printf("Now server is reading Haikus\n");

    // reading haikus from message queue for SIGNAL_NUMBER times
   for(int i=1;i<=SIGNAL_NUMBER;i++){
        printf("\n==========================================\n");
        
         for(int k=0;k<2;k++){
         
          // finding Haiku category with going through matrix index
          for(int j=0;j<SIGNAL_NUMBER;j++){
               if(matrix[k][j] == i){

                       haiku_category= k+1;
                  
               }
          }
          
        }
        // reading haikus for 3 time
        for(int i=0; i<3;i++){

            read_haiku(msg_id,haiku_category);
   
        sleep(1);
        }
    }

    // removing message queue after all works were done
    remove_queue(msg_id);

    return 0;
}