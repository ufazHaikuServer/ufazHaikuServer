#include "msg_queue.h"

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
  
  
        strcpy(fileName,"../Japanese/Haiku_");

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
    strcpy(fileName,"../Western/Haiku_");

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