#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

#include "delays.h"
#include "process.h"

int main(void)
{
  pid_t ret = pfork();
  
  if (ret == 0) { // child
    int i;
    for (i = 1; i <= 10; i++) {
        printf("%d\n", i);
    }
  } else { // parent
    pwait(NULL);
    int i;
    for (i = 11; i <= 20; i++) {
        printf("%d\n", i);
    }
  }
  
  return EXIT_SUCCESS;
}

