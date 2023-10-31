#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

#include "process.h"

int main(void)
{
  int *pcounter;

  int shmid = pshmget(IPC_PRIVATE, sizeof(int), IPC_CREAT | 0600);

  pcounter = (int *) pshmat(shmid, NULL, 0);
  *pcounter = 0;

  // Semaphore 0: Pares
  // Semaphore 1: Impares
  int semid = psemget(IPC_PRIVATE, 2, IPC_CREAT | IPC_EXCL | 0600);

  while (*pcounter < 10 || *pcounter > 20) {
    printf("Enter a value between 10 and 20: ");
    scanf("%d", pcounter);
  }

  if (*pcounter % 2 == 0) psem_up(semid, 0);
  else psem_up(semid, 1);

  int i = 0;
  for (; i < 1; i++) {
    if (pfork() == 0) {
      // Child
      if (*pcounter % 2 == 0) {
        psem_down(semid, 0);
        (*pcounter)--;
        psem_up(semid, 1);
      } else {
        psem_down(semid, 1);
        (*pcounter)--;
        psem_up(semid, 0);
      }
    }
  }

  // if (pfork() == 0) {
  //   // Child
  //   int countTo = 0;
  //   while (countTo < 10 || countTo > 20) {
  //     printf("Enter a value between 10 and 20: ");
  //     scanf("%d", &countTo);
  //   }
  //   while (*pcounter != countTo + 1) {
  //     printf("(%d) %d\n", getpid(), *pcounter);
  //     (*pcounter)++;
  //   }
  //   exit(EXIT_SUCCESS);
  // } else {
  //   // Parent
  //   pwait(NULL);
  //   while (*pcounter != 1) {
  //     (*pcounter)--;
  //     printf("(%d) %d\n", getpid(), *pcounter);
  //   }
  // }

  i = 0;
  for (; i < 1; i++) {
    pwait(NULL);
  }

  psemctl(semid, 1, IPC_RMID, NULL);
  pshmdt(pcounter);
  pshmctl(shmid, IPC_RMID, NULL);

  return EXIT_SUCCESS;
}
