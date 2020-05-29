/*
This header file is for holding the global variables and the function declarations to be used by server and client.
*/

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

#define SIGNAL_NUMBER 100


// Global variable for holding process ID in shared memory segment
pid_t *pid;

// Global variable for the array of the association between haiku category, signal type and order.
int matrix[2][SIGNAL_NUMBER];

// Global variable for counting the received signal
int signal_counter;



int *create_shared_memory();
void send_signal(pid_t pid);
void receive_signal();
void print(int haiku_category, int b,int matrix[haiku_category][b]);
void SIGINT_handler(int sig);
void SIGQUIT_handler(int sig);

//void delay(int sec);
