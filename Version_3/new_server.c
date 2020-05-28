#include "../Version_1/shared.h"
#include "../Version_2/msg_queue.h"


int main(){


    pid=create_shared_memory();
    *pid = getpid();
    printf("==========================================\n");
    printf("Now server is receiving signals from client. It will take a little bit time. Please, wait\n");
    printf("==========================================\n");
    while(signal_counter<100) {
     receive_signal();
     sleep(1);
    }
    
    printf("==========================================\n");
    print(2,100,matrix);
    printf("==========================================\n");


    int msg_id;
    int haiku_category;

    msg_id = create_queue();

    if(msg_id<0){
        printf("Failed to create message queue\n");
        exit(-1);
    }




    printf("Now server is reading Haikus\n");
   for(int i=1;i<=100;i++){
        printf("\n==========================================\n");
        
         for(int k=0;k<2;k++){
         
          for(int j=0;j<10;j++){
               if(matrix[k][j] == i){
                
                       haiku_category= k+1;
                  
               }
          }
        
          
     }
        for(int i=0; i<3;i++){
      read_haiku(msg_id,haiku_category);
   
        sleep(1);
        }
    }

    remove_queue(msg_id);




    return 0;
}