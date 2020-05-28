#include "shared.h"

int main(void)
{
    pid=create_shared_memory();
    *pid = getpid();
    while(1) {
     receive_signal();
     sleep(1);
  }
  return 0;
}