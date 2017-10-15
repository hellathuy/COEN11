#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#define NODE struct node

void read_data(char *);							//declare functions
void insert(char *, int);
void cancel(void);
void list(void);
void char_count(void);
void name_backwards(void);
void reverse(char *temp);
void save_data(char *);
void free_nodes();
void recursive_free();
void read_auto_saved(char *filename);
void *auto_save (void *arg);

int reservations = 0;

struct node {								//declare a structure variable
        char name [20];							//member inside struct for name 
        int size;							//member inside struct for size 
        NODE *next;							//pointer to the next item in list 
};

NODE *heads[4];								//declare head and tail pointer arrays 
NODE *tails[4];

pthread_mutex_t mutex;							//declare pthread

int main(int argc, char*argv[]) {					//main function 
        char name [20];
        int size;
        int option;

        if (argc == 1) {						//return if file name is not declared
                printf("The file name is missing!\n");
                return (-1);
        }

        else {								//read data from text file
                read_data(argv[1]);
        }

        pthread_t thread;						//pthread
        pthread_mutex_init (&mutex, NULL);
        pthread_create (&thread, NULL, auto_save, (void *) argv[2]);

        while (1) {							//forever loop to continuously repeat program 
                printf("What do you want to do?\n");
                printf(" [1] Add a name to the list.\n");
                printf(" [2] Remove a name from the list.\n");
                printf(" [3] Show the list of names.\n");
                printf(" [4] Count how many characters there are in the names.\n");
                printf(" [5] Print out names backwards.\n");
                printf(" [6] Print the auto-saved binary file.\n");
                printf(" [7] Quit the program.\n\n");

                scanf ("%d", &option);					//receive input from user 

                switch (option) {					//switch function to switch between functions 
                        case 1:
                                printf ("What is the guest's name? ");
                                scanf ("%s", name);
                                printf ("\nHow many people are in the party? ");
                                scanf ("%d", &size);
                                insert(name, size);			//calls insert function 
                                break;
                        case 2:
                                cancel();				//calls delete function 
                                break;
                        case 3:
                                list();					//calls list function 
                                break;
                        case 4:
                                char_count();				//calls character count function 
                                break;
                        case 5:
                                name_backwards();			//calls function to display name backwards
                                break;
                        case 6:
                                read_auto_saved(argv[2]);		//read data from auto save text file
                                break;
                        default:					//quits program and saves program to text file
                                save_data(argv[1]);
                                free_nodes();
                                return 0;
                }
        }
}

void read_data(char *file_name) {					//function to read data from text file 
        char name[20];
        int size;
        FILE *fp;							//declare file

        fp = fopen(file_name, "r");					//open file 

        if (fp == NULL) {
                printf ("File not found.");
                return;
        }

        fseek(fp, 45, SEEK_SET);					//skips certain amount of spaces 

        while (fscanf(fp, "%s %d", name, &size) == 2) {			//read file and inserts info into insert function
                insert(name, size);
        }

        fclose(fp);							//closes file 
        return;
}

void insert(char*name, int size) {					//function to allow user to add names to list 
        NODE *temp;
        int j;
        int flag = 0;

        for (j = 0; j < 4; j++) {					//traverses list 
                temp = heads[j];

                while (temp != NULL) {					//checks for duplicates 
                        if (strcmp(name, temp->name) == 0) {
                                printf("\nThis name has already been entered.\n");
                                return;
                        }

                        tails[j] = temp;
                        temp = temp->next;
                }
        }

        NODE *p;
        int i;

        p = (NODE*)malloc(sizeof(NODE));				//malloc for pointer p 

        if (p == NULL) {
                printf("\nNo Memory Available.\n");
                return;
        }

        strcpy (p->name, name);
        p->size = size;

        p->next = NULL;

        switch (size) {							//switch function to sort table into groups 
                case 1:
                case 2:
                        i = 0;
                        break;
                case 3:
                case 4:
                        i = 1;
                        break;
                case 5:
                case 6:
                        i = 2;
                        break;
                default:
                        i = 3;
                        break;
        }

        pthread_mutex_lock (&mutex);

        if (heads[i] == NULL) {						//adds name to list 
                heads[i] = p;
                tails[i] = p;
        }

        else {
                tails[i]->next=p;
        }

        tails[i] = p;
        pthread_mutex_unlock (&mutex);					//unlock 
        return;
}

void cancel (void) {							//function to remove names from list 
        int i;
        int temp;
        NODE *q;
        NODE *p;

        printf("\nEnter the table size:\n");
        scanf("%d", &temp);

        switch (temp) {							//determine which group the open table falls into 
                case 1:
                case 2:
                        i = 0;
                        break;
                case 3:
                case 4:
                        i = 1;
                        break;
                case 5:
                case 6:
                        i = 2;
                        break;
                default:
                        i = 3;
                        break;
        }

        for (i = i; i >= 0; i--) {					//traverses list to find best table for open table 
                if (heads[i] == NULL) {					//outputs if there are no names in the list 
                        printf("\nThere are no reservations to cancel.\n");
                }

                else {							//removes names from list 
                        q = heads[i];
                        p = q->next;

                        if (q->size <= temp) {
                                pthread_mutex_lock(&mutex);		//lock
                                printf("\n%s's table has been cleared\n", q->name);
                                heads[i] = heads[i]->next;
                                free(q);
                                pthread_mutex_unlock (&mutex);		//unlock
                                return;
                        }

                        while (p != NULL) {				
                                if (p->size <= temp) {
                                        pthread_mutex_lock (&mutex);
                                        printf("\n%s's table has been cleared\n", p->name);
                                        q->next = p->next;
                                        free(p);
                                        pthread_mutex_unlock (&mutex);
                                        return;
                                }

                                p = p->next;
                                q = q->next;
                        }
                }
        }
									//outputs if there are no tables that can fit the open table 
        printf("\nThere are no tables to accomodate that size right now.\n");
}

void list(void) {							//function to list all names 
        NODE *p;
        int i;

        for (i = 0; i < 4; i++) {					//traverses list and print names 
                p = heads[i];
                printf("\nCurrent Reservations in Group %d:", i+1);

                if (p == NULL) {
                        printf ("\n--------------EMPTY--------------\n");
                }

                else {
                        printf ("\n---------------------------------\nName\t\tGroup Size\n");
                }

                while (p != NULL) {
                        printf("%s\t\t%d\n", p->name, p->size);
                        p = p->next;
                }
        }

        return;
}

void char_count(void) {							//function to count how many instances of a certain character
        NODE *p;
        char input;
        char *q;
        int counter = 0;
        int i;

        printf ("Enter the letter you wish to count\n");		//allows user to input in a letter
        fpurge(stdin);
        scanf ("%c", &input);

        for (i = 0; i < 4; i++) {					//traverses list and counts the letter
                p = heads[i];
                while (p != NULL) {
                        q = p->name;

                        while (*q != '\0') {
                                if (*q==input) {
                                        counter++;
                                }
                        }

                        q++;
                }

                p=p->next;
        }
									//outputs how many letters there are 
        printf ("There were %d instances of %c in the guest list.", counter, input);
}

void name_backwards(void) {						//function to display names backwards
        NODE *p;
        NODE *temp;
        int i;

        for(i = 0; i < 4; i++) {
                p = heads[i];
                printf("\nCurrent Reservations in Group %d:", i+1);
                if (p == NULL) {
                        printf("\n--------------EMPTY--------------\n");
                }

                else {
                        printf ("\n---------------------------------\nName Backwards:\n");
                }

                while (p != NULL) {
                        char temp[20];
                        strcpy(temp, p->name);
                        reverse(temp);					//passes name to the reverse function
                        p = p->next;
                }
        }
}

void reverse(char *temp) {						//function to actually reverse the names
        if (*temp) {
                reverse(temp + 1);					//recursive!
                printf("%c", *temp);
        }
}

void save_data(char *file_name) {					//function to save data to text file
        FILE *fp;							//declare file
        NODE *p;
        int i;

        fp = fopen(file_name, "w");					//open file to write

        if (fp == NULL) {
                printf ("File not found\n");
                return;
        }

        fprintf (fp, "Name:\t\tSize:\n-------------------------------\n");

        for (i = 0; i < 4; i++) {
                p = heads[i];
                while (p != NULL) {					//prints info to file
                        fprintf(fp, "%s\t%d\n", p->name, p->size);
                        p = p->next;
                }
        }

        fclose (fp);							//closes file
        return;
}

void free_nodes() {							//function to free nodes
        NODE *p;
        int i;

        for (i = 0; i < 4; i++) {
                p = heads[i];
                recursive_free(p);					//passes p to recursive_free
        }
}

void recursive_free(NODE *p) {						//function to recursively free nodes
        if (p == NULL) {
                return;
        }

        recursive_free(p->next);
        free(p);
        return;
}

void *auto_save(void *arg) {						//function to auto-save data
        char *binary = (char *) arg;

        FILE *outfp;
        NODE *p;
        int i;

        while(1) {
                pthread_mutex_lock (&mutex);				//lock
                outfp = fopen(binary, "wb");

                if (outfp == NULL) {
                        printf ("File not found\n");
                }

                for (i = 0; i < 4; i++) {				//saves data to binary file
                        p = heads[i];
                        while (p != NULL) {
                                fwrite(p, sizeof(NODE), 1, outfp);
                                p = p->next;
                        }
                }

                fclose(outfp);
                pthread_mutex_unlock(&mutex);				//unlock
                sleep(5);						//repeats every 5 seconds
        }
}

void read_auto_saved(char *binary) {					//function to read auto-save binary file
        pthread_mutex_lock(&mutex);					//lock
        FILE *infp;
        NODE save_temp;

        infp = fopen(binary, "rb");

        if (infp == NULL) {
                printf ("File not found\n");
                return;
        }

        printf("\nCurrent Reservations:\n");
        printf("\n---------------------------------\nName\t\tGroup Size\n");

        while (fread(&save_temp, sizeof(NODE), 1, infp)!= 0) {		//reads info and prints data
                printf("%s\t\t%d\n", save_temp.name, save_temp.size);
        }

        fclose (infp);
        pthread_mutex_unlock(&mutex);					//unlock
        return;
}


