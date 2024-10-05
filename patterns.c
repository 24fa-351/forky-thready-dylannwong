#include "random_sleep.c"
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

void pattern1(int nums) {

  pid_t pid;
  pid_t pids[nums];
  for (int i = 1; i <= nums; i++) {
    pid = fork();

    if (pid == 0) {

      int sleeping = random_slee(i);
      printf("process %d beginning, pid %d sleeping for %d seconds\n", i,
             getpid(), sleeping);
      sleep(sleeping);
      printf("process %d exiting, pid %d\n", i, getpid());
      fflush(stdout);
      exit(0);
    } else if (pid > 0) {
      pids[i - 1] = pid;
    }
  }
  for (int i = 0; i < nums; i++) {
    waitpid(pids[i], NULL, 0);
  }
}

void pattern2(int nums) {
  // array to keep track of pids
  pid_t pids[nums];
  pids[0] = fork();

  for (int i = 0; i < nums; i++) {

    if (i < nums) {

      if (pids[i] == 0) {
        int sleeping = random_slee(i);
        pid_t p_id = getpid();
        printf("Process %d beginning, process: %d\n", i + 1, p_id);
        // child making next process
        pids[i + 1] = fork();

        if (pids[i + 1] == 0) {

          printf("Process %d %d making Process %d %d\n", i + 1, p_id, i + 2,
                 getpid());
          sleep(sleeping);
          printf("Process %d exiting\n", i + 1);
        } else if (pids[i + 1] > 0) {
          sleep(sleeping);
          waitpid(pids[i + 1], NULL, 0);
          break;
        }

      } else if (pids[i] > 0) {
        waitpid(pids[i], NULL, 0);
        break;
      }

    } else {
      break;
    }
  }
}