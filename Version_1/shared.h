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



pid_t *pid;
int matrix[2][100];
int signal_counter;



int *create_shared_memory();
void send_signal(pid_t pid, int nb_signal);
void receive_signal();
void print(int a, int b,int matrix[a][b]);
void  SIGINT_handler(int sig);
void  SIGQUIT_handler(int sig);
void delay(int sec);