#include "shared.h"

void main () {
     pid_t *pid=create_shared_memory();
     send_signal(*pid, 100);
}