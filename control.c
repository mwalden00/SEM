#include "sem_funcs.h"

int main(int argc, char * argv[])
{
  if (argc == 1) {
    printf("Please give a flag: -c, -v, or -r\n");
    return 0;
  }
  if (strcmp(argv[1], "-c") == 0) {
    shm_create();
    make_file(NAME);
    sem_create();
    return 0;
  }
  if (strcmp(argv[1], "-r") == 0) {
    printf("Trying to get in...\n");
    int sem_id = semget(SEMKEY, 1, 0);
    read_story(NAME);
    int shm_id = shmget(SHMKEY, SIZE, 0600);
    shm_destroy(shm_id);
    sem_destroy(sem_id);
    destroy_story(NAME);
    return 0;
  }
  if (strcmp(argv[1], "-v") == 0) {
    read_story(NAME);
    return 0;
  }
  printf("Please give a flag: -c, -v, or -r\n");
  return 0;
}
