#include "proj.h"

void insert(char*name, int size) {					//function to allow user to add names to list 
        NODE *temp;
        int j;
        int flag = 0;
        
	for (j = 0; j < 4; j++) {					//traverses list
                temp = heads[j];

                while (temp != NULL) {					//check for duplicates
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

        printf ("Enter the letter you wish to count\n");
        fpurge(stdin);
        scanf ("%c", &input);						//alows user to input in a letter

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


