#include "server_client.h"

/*
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

void print(int i, int j, int matrix[i][j]){
     for(int i=0;i<2;i++){
          for(int j=0;j<100;j++){
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
     printf("From SIGINT: just got a %d (SIGINT ^C) signal\n", sig);
     signal(sig, SIGINT_handler);
     matrix[0][i++] = counter++;
          print(2,100,matrix);
     shmdt(pid);
     
}

void  SIGQUIT_handler(int sig)
{
     signal(sig, SIG_IGN);
     printf("From SIGQUIT: just got a %d (SIGQUIT ^\\) signal"
                          " and is about to quit\n", sig);
     shmdt(pid);
  
     matrix[1][j++]=counter++;
           print(2,100,matrix);
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


int create_queue(void){
    // key for making queueu=
    key_t key;
    //id for identifying created queue
    int msg_id;
    //converting pathname to unique identifier
    key=ftok("/etc/passwd",'E');

    if(key==-1) perror("ftok");
    
    //creating queue and geting its id
    msg_id=msgget(key,IPC_CREAT|0666);

    // if id is less than 0, it means, creating queue is not successfull
    if(msg_id==-1)  perror("msgget");
    

    return msg_id;

}


//Function for accessing queue
int access_queue(void){
    key_t key;
    int msg_id;

    key=ftok("/etc/passwd",'E');

    if(key==-1) perror("ftok");
    
    msg_id=msgget(key,0);
    
    if(msg_id==-1)  perror("msgget");
    // printf("Access is successfull"); 
    return msg_id;

   
}


// Function for removing queue after sending message
void remove_queue(int msg_id){
    int r;
    r=msgctl(msg_id,IPC_RMID,NULL);

    if(r==-1)   perror("msgctl");
    
}


void write_haiku(int msg_id,char msg_text[],int msg_type){
    // message buffer for holding text for sending
    message msg;
    msg.msg_type=msg_type;

    //copy givent text to message buffer
    strncpy(msg.msg_text,msg_text,MAX);

    msg.msg_text[MAX-1]='\0';

    //sending message
    int r=msgsnd(msg_id,&msg,sizeof(message),0); 

//if message did not send, print error
    if(r==-1){
        perror("msgsnd");
        exit(1);
    }
   
}


void fill_msg_queue(int msg_id){

    FILE *fp;
    char haiku[MAX];
    char* line = NULL;
    char  fileName[50];
    char  fullName[50]; 
    size_t len = 0;
    ssize_t read;

    // Japanase 
  
  
        strcpy(fileName,"Japanese/Haiku_");

    for(int i=1;i<=6;i++){
        char nb[2];
        sprintf(nb, "%d",i);
        strcpy(fullName,fileName);
        strcat(fullName,nb);
        //strcat(fullName,".txt");
        
       
    
        //if (access(fullName, F_OK) == -1){printf("it is not ok");}
        fp = fopen(fullName, "r");
        
        if (fp == NULL){
            printf("Could not open file %s",fullName);
            exit(1);
        }

        while ((read = getline(&line, &len, fp)) != -1) {
            strcat(haiku,line);
            strcat(haiku,"\n");
        }
        
        fclose(fp);
        write_haiku(msg_id,haiku,1);
        line = NULL;
        strcpy(haiku, " ");
    }
    

       // Western
    strcpy(fileName,"Western/Haiku_");

    for(int i=1;i<=9;i++){
        char nb[2];
        sprintf(nb, "%d",i);
        strcpy(fullName,fileName);
        strcat(fullName,nb);
        //strcat(fullName,".txt");
        

        fp = fopen(fullName, "r");
        if (fp == NULL){
            printf("Could not open file %s",fullName);
            exit(1);
        }

        while ((read = getline(&line, &len, fp)) != -1) {
            strcat(haiku,line);
            strcat(haiku,"\n");
        }
        fclose(fp);
        write_haiku(msg_id,haiku,2);
        line = NULL;
        strcpy(haiku, " ");
    }
}


void read_haiku(int msg_id,int category){

    message msg;

    int n; // number of readed bytes
    // msgrcv for receiving message from identified queue
    while(1){
        n=msgrcv(msg_id,&msg,sizeof(message),0,0);

        // if there is no message, exit program
        if(n==-1){
        perror("msgrcv");
            exit(1);
        }

        if(msg.msg_type == category){
            break;
        }

    }

    printf("%s",msg.msg_text);

}
*/

int find_catagory(int a, int b, int matrix[a][b], int value){

    for(int i=0;i<a;i++){
        for(int j=0;j<b;j++){
            if(matrix[i][j]==value){
                return i;
            }
        }
    }
    return -1;

}