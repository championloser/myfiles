#include<stdio.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<fcntl.h>
#include<unistd.h>
#include<string.h>
#include<dirent.h>
#include<time.h>
#include<pwd.h>
#include<grp.h>
#include<malloc.h>
#include<stdlib.h>
#include<sys/mman.h>
#include<sys/wait.h>
#include<sys/ipc.h>
#include<sys/shm.h>
#include<sys/sem.h>
#include<signal.h>
#include<sys/time.h>

typedef struct node{
	char flag;
	char buf[512];
}Node,*Nodepoint;
