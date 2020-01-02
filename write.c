#include "sem_funcs.h"

int main()
{
  int sem_id = semget(SEMKEY, 1, 0);
  struct sembuf sb;
  sb.sem_num = 1;
  sb.sem_op = -1;
  printf("Trying to get in...\n");
  semop(sem_id, &sb, 1);
  int shm_id = shmget(SHMKEY, SIZE, 0600);
  if(shm_id < 0) {
      printf("error %d: %s\n", errno, strerror(errno));
      return 1;
  }
  char * data = shmat(shm_id, 0, 0);
  printf("Last addition: %s\n", data);
  printf("Your addition: ");
  fgets(data, SIZE, stdin);
  char * str = data + strlen(data);
  str = 0;
  int fd = open(NAME, O_WRONLY | O_APPEND);
  write(fd, data, SIZE);
  close(fd);
  shmdt(data);
  return 0;
}
