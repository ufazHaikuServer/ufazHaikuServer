#include "../Version_1/shared.h"
#include "../Version_2/msg_queue.h"

/*
#include  <stdio.h>
#include <stdlib.h>
#include  <sys/types.h>
#include  <signal.h>
#include  <sys/ipc.h>
#include  <sys/shm.h>
#include <ctype.h>
#include <errno.h>
#include <unistd.h>
#include <time.h>
#include <sys/msg.h>
#include <string.h>



#define MAX 2048

//Data for message
typedef struct message{
    long msg_type; 
    char msg_text[MAX];

}message;


pid_t *pid;
int matrix[2][100];



int *create_shared_memory();
void send_signal(pid_t pid, int nb_signal);
void receive_signal();
void print(int i, int j,int matrix[i][j]);
void  SIGINT_handler(int sig);
void  SIGQUIT_handler(int sig);
void delay(int sec);






int create_queue(void);
int access_queue(void);
void remove_queue(int msg_id);
void write_haiku(int msg_id,char msg_text[],int msg_priority);
void fill_msg_queue(int msg_id);
void read_haiku(int msg_id,int category);


*/


int find_catagory(int a, int b, int matrix[a][b], int value);