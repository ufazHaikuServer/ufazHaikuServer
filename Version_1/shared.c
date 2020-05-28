#include "shared.h"

int i = 0;
int j = 0;
int counter = 1;

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


void send_signal(pid_t pid, int nb_signal) {
     int c;
     for (int i = 0; i<nb_signal; i++) {
               c=rand()%3;
               while(c==0){
                    c=rand()%3;
                    if(c!=0)
                    break;
               }
              printf("%d\n", c);
          if (c == 1) {  
               kill(pid, SIGINT);
               printf("Sent a SIGINT signal\n");
               sleep(1);
          }
          else if (c == 2) {
               printf("About to send a SIGQUIT signal\n");
               kill(pid, SIGQUIT);     
               sleep(1);
          }
}
}

void print(int a, int b, int matrix[a][b]){
     for(int i=0;i<a;i++){
          if(i==0){
               printf("Japanese |");
          }else{
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


void  SIGINT_handler(int sig)
{
     signal(sig, SIG_IGN);
     printf("==========================================\n");
     printf("From SIGINT: just got a %d (SIGINT ^C) signal\n", sig);
     signal(sig, SIGINT_handler);
     signal_counter++;
     matrix[0][i++] = counter++;
         // print(2,100,matrix);
     shmdt(pid);
     
}

void  SIGQUIT_handler(int sig)
{
     signal(sig, SIG_IGN);
     printf("==========================================\n");
     printf("From SIGQUIT: just got a %d (SIGQUIT ^\\) signal"
                          " and is about to quit\n", sig);
     shmdt(pid);
     signal_counter++;
     matrix[1][j++]=counter++;
         //  print(2,100,matrix);
}



void receive_signal(){
          if(signal(SIGINT, SIGINT_handler)!=SIG_ERR){
     }else{
          printf("SIGINT install error\n");
          exit(1);
     }

     if(signal(SIGQUIT, SIGQUIT_handler)!=SIG_ERR){
          
       }else{
          printf("SIGQUIT install error\n");
          exit(2);
     }
}

void delay(int sec){
 struct timespec req = {0};
 req.tv_sec = 0;
 req.tv_nsec = sec * 1000000000L;
 nanosleep(&req, (struct timespec*)NULL); 
 
}