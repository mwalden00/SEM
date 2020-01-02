#include "sem_funcs.h"

// Creates a new semaphore using SEMKEY, an integer variable found in sem_funcs.h
int sem_create()
{
  int sem_id = semget(SEMKEY, 1, IPC_CREAT | IPC_EXCL | 0644);
  int ctl_ret;
  if (sem_id < 0) {
    sem_id = semget(SEMKEY, 1, 0);
    ctl_ret = semctl(sem_id, 0, GETVAL, 0);
  } else {
    union semun sem_un;
    sem_un.val = 1;
    ctl_ret = semctl(sem_id, 0, SETVAL, sem_un);
  }
  printf("semaphore created\n");
  return sem_id;
}

// Removes semaphore specified by int sem_id from the system
int sem_destroy(int sem_id)
{
  int ctl_ret = semctl(sem_id, 0, IPC_RMID);
  if (ctl_ret < 0) printf("error with semctl(): %s\n", strerror(errno));
  printf("semaphore removed\n");
  return 0;
}

// Makes a new file named after char * name
int make_file(char * name)
{
  int fd = open(name, O_CREAT | O_EXCL | O_TRUNC | O_WRONLY, 0644);
  if (fd < 0) fd = open(name, O_TRUNC | O_WRONLY);
  char to_write[SIZE] = "The story so far:";
  write(fd, to_write, SIZE);
  close(fd);
  printf("file created\n");
  return fd;
}

// Creates shared memory using SHMKEY, which is an integer variable in sem_funcs.h
int shm_create()
{
  int shm_id = shmget(SHMKEY, SIZE, IPC_CREAT | 0600);
  if (shm_id < 0) printf("error: %s\n", strerror(errno));
  printf("shared memory created\n");
  return shm_id;
}

// Destroys shared memory specified by shm_id
int shm_destroy(int shm_id)
{
  int ctl_ret = shmctl(shm_id, IPC_RMID, 0);
  if (ctl_ret < 0) printf("error: %s\n", strerror(errno));
  printf("shared memory destroyed\n");
  return ctl_ret;
}

// Reads the story!
int read_story(char * story)
{
  int fd = open(story, O_RDONLY);
  if (fd < 0) printf("error: %s\n", strerror(errno));
  char buff[SIZE];
  while (read(fd, buff, SIZE)) printf("%s\n", buff);
  close(fd);
  return 0;
}

int destroy_story(char * story)
{
  remove(story);
  return 0;
}
