/*
This header file is for holding the global variables and the function declarations to be used by writer and reader.
*/

#include <stdio.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <errno.h>

// Capacity of message text
#define MAX 2048


//Structure of message
typedef struct message{

    // Haiku category
    long msg_type; 
    
    char msg_text[MAX];

}message;




int create_queue(void);
int access_queue(void);
void remove_queue(int msg_id);
void write_haiku(int msg_id,char msg_text[],int msg_priority);
void fill_msg_queue(int msg_id);
void read_haiku(int msg_id,int category);



