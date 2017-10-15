#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#define NODE struct node

void read_data(char *, int);				//declare all functions
void insert(char *, int);
void cancel(void);
void list(void);
void char_count(void);
void name_backwards(void);
void reverse(char *temp);
void save_data(char *, int);
void free_nodes();
void recursive_free();
void read_auto_saved(char *filename);
void *auto_save (void *arg);

int reservations;

struct node {						//declare struct variable
        char name [20];
        int size;
        NODE *next;
};

NODE *heads[4];						//declare head and tail pointer arrays
NODE *tails[4];

pthread_mutex_t mutex;					//pthread
