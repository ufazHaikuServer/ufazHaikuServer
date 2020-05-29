/*
 This source file is for holding definitions of functions to be used by writer and reader
*/

#include "msg_queue.h"


/*
    Function for creating message queue
*/
int create_queue(void){

    // key for making queueu
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


/*
    Function for accessing queue
*/
int access_queue(void){

    key_t key;
    int msg_id;

    key=ftok("/etc/passwd",'E');

    if(key==-1) perror("ftok");
    
    msg_id=msgget(key,0);
    
    if(msg_id==-1)  perror("msgget");
   
    return msg_id;

   
}


/*
    Function for removing queue after sending message
*/
void remove_queue(int msg_id){

    int r;

    r=msgctl(msg_id,IPC_RMID,NULL);

    if(r==-1)   perror("msgctl");
    
}


/*
    Function for writing haiku into message queue with their category
*/
void write_haiku(int msg_id,char msg_text[],int msg_type){

    // message buffer for holding text for sending to reader
    message msg;
    msg.msg_type=msg_type;

    //copy given text to message buffer
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



/*
    Filling nessage queue by reading Haikus from files and writing them to message queue with their category
*/
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

        // converting integer i to string
        char nb[2];
        sprintf(nb, "%d",i);

        // copying fileName to fullName for avoiding the loss of constant fileName
        strcpy(fullName,fileName);

        // getting fullName by concatinating fullname and number ( "../Japanese/Haiku_" + "2" = "../Japanese/Haiku_2")
        strcat(fullName,nb);       
    
        // opening file
        fp = fopen(fullName, "r");
        
        if (fp == NULL){
            printf("Could not open file %s",fullName);
            exit(1);
        }

        // reading file line by line
        while ((read = getline(&line, &len, fp)) != -1) {
            strcat(haiku,line);
            
        }
        strcat(haiku,"\n\n");
        fclose(fp);

        // writing haiku text message queue
        write_haiku(msg_id,haiku,1);

        // cleaning strings
        line = NULL;
        strcpy(haiku, " ");
    }
    

       // Western

       // changing fileName for Western folder
        strcpy(fileName,"../Western/Haiku_");

        for(int i=1;i<=9;i++){

            // converting integer i to string
            char nb[2];
            sprintf(nb, "%d",i);

            // copying fileName to fullName for avoiding the loss of constant fileName
            strcpy(fullName,fileName);

            // getting fullName by concatinating fullname and number ( "../Western/Haiku_" + "2" = "../Western/Haiku_2")
            strcat(fullName,nb);
            
            // opening file
            fp = fopen(fullName, "r");

            if (fp == NULL){
                printf("Could not open file %s",fullName);
                exit(1);
            }

            // reading file line by line
            while ((read = getline(&line, &len, fp)) != -1) {
                strcat(haiku,line);
               // strcat(haiku,"\n");
            }
            strcat(haiku,"\n\n");

            fclose(fp);

             // writing haiku text message queue
            write_haiku(msg_id,haiku,2);

            // cleaning strings
            line = NULL;
            strcpy(haiku, " ");
        }
}


/*
    Function for reading Haikus from message queue
*/
void read_haiku(int msg_id,int category){

    message msg;

    // number of readed bytes
    int n; 
    
    // reading Haikus from message queue until we find the sought haiku with its category

    while(1){

        // msgrcv for receiving message from identified queue
        n=msgrcv(msg_id,&msg,sizeof(message),0,0);

        // if there is no message, exit program
        if(n==-1){
        perror("msgrcv");
            exit(1);
        }

        // checking message category 
        if(msg.msg_type == category){
           
            // if searched Haikus is found, stop reading
            break;
        }

    }

    // printing read Haikus
    printf("%s",msg.msg_text);

}