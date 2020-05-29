/*
 This source file is for holding definitions of functions to be used by server and client
*/

#include "shared.h"

// Global variables for only shared.c source file
int i = 0;
int j = 0;
int signal_order = 1;


//Creating shared memory segment 

int *create_shared_memory() {

     int *shmaddr = 0; 
     key_t key = ftok(".", 's');  

     int shmid = shmget(key, 5, IPC_CREAT | SHM_R | SHM_W); 

     if (errno > 0) {
          perror("shmget ERROR");
          exit (EXIT_FAILURE);
     }
     
     shmaddr = (int*)shmat(shmid, NULL, 0);

     if (errno > 0) {
          perror ("shmat ERROR");
          exit (EXIT_FAILURE);
     }
     return shmaddr;
}


/*
     Function for sending signal from client to server.
     It will be used by only client.

     @param pid server process pid 
 
 */

void send_signal(pid_t pid) {
          
     // haiku category 
     int sig_type;

     // sends random signals for SIGNAL_NUMBER times
     for (int i = 0; i<SIGNAL_NUMBER; i++) {
               
          // can get random value [0,2]
          sig_type=rand()%3;

          //gets a random value again until not zero
          while(sig_type==0){  
               sig_type=rand()%3;
               if(sig_type!=0)
               break;
          }

         //printf("%d\n", sig_type);

          // 1 for SIGINT (haiku category - Japanese)
          if (sig_type == 1) {  

               //sends a signal from client to server
               kill(pid, SIGINT);
               printf("Sent a SIGINT signal\n");
               sleep(1);
          }
          // 2 for SIGQUIT (haiku category - Western)
          else if (sig_type == 2) {

               //sends a signal from client to server
               kill(pid, SIGQUIT);     
               printf("Sent a SIGQUIT signal\n");
               sleep(1);
          }
     }
}


/*
     Function for printing matrix which holds signal orders in respect to Haiku category
*/

void print(int a, int b, int matrix[a][b]){

     for(int i=0;i<a;i++){
          
          // matrix[0][b] => Japanese
          if(i==0){
               printf("Japanese |");
          }

          // matrix[1][b] => Western
          else{
               printf("Western  |");
          }
          for(int j=0;j<b;j++){
               if(matrix[i][j] != 0){
                     printf("%d |",matrix[i][j]);
               }
          }
          printf("\n");
     }
     printf("==========================================\n");
}

/*
     Function to receive SIGINT and store it in the matrix under Haiku category Japanese
*/
void  SIGINT_handler(int sig)
{
     signal(sig, SIG_IGN);
     printf("==========================================\n");
     printf("Signal number %d => from SIGINT: just got a %d (SIGINT ^C) signal\n", signal_counter+1 , sig);
     signal(sig, SIGINT_handler);
     
     shmdt(pid);
                                                                                                                                    
     //increment the numbers of received signals
     signal_counter++;

     //store new signal order in the next available index
     matrix[0][i++] = signal_order++;

     // uncomment it to see how matrix is filled
     // print(2,100,matrix);
     
}

/*
     Function to receive SIGQUIT and store it in the matrix under Haiku category Western
*/
void  SIGQUIT_handler(int sig)
{
     signal(sig, SIG_IGN);
     printf("==========================================\n");
     printf("Signal number %d => frrom SIGQUIT: just got a %d (SIGQUIT ^\\) signal\n", signal_counter+1, sig);

     shmdt(pid);
     
     //increment the numbers of received signals
     signal_counter++;

     //store new signal order in the next available index
     matrix[1][j++]=signal_order++;

     // uncomment it to see how matrix is filled
     //  print(2,100,matrix);
     
}

/*
    Function to check and receive both SIGINT and SIGQUIT signals
*/
void receive_signal(){


     if(signal(SIGINT, SIGINT_handler)==SIG_ERR){
          printf("SIGINT install error\n");
          exit(1);
     }

     if(signal(SIGQUIT, SIGQUIT_handler)==SIG_ERR){
          printf("SIGQUIT install error\n");
          exit(2);
     }
}


/*
void delay(int sec){
 struct timespec req = {0};
 req.tv_sec = 0;
 req.tv_nsec = sec * 1000000000L;
 nanosleep(&req, (struct timespec*)NULL); 
 
}
*/