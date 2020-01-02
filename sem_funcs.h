#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/types.h>
#include <errno.h>
#include <sys/shm.h>
#include <fcntl.h>
#include <errno.h>

#define SEMKEY 24601
#define SHMKEY 24602
#define NAME "story"
#define SIZE 256

int sem_create();
int shm_create();
int sem_destroy(int sem);
int shm_destroy(int shm);
int make_file(char * name);
int read_story(char * story);
int destroy_story(char * story);
