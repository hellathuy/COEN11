#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void insert(char*, int);
void delete();
void list();
void save_data (char*);
void read_data (char*);

typedef struct node {
	char table_name[20];
	int table_size;
	struct node *next;
} INFO_NODE;

INFO_NODE *heads[4];
INFO_NODE *tails[4];

int main (int argc, char *argv[]) {
	int input;
	char name[20];
	int size; 
	
	if (argc == 1) {
		printf("The file name is missing.\n");
	}

	else {
		read_data(argv[1]);
	}

	while (1) {
		printf("What do you want to do?\n");
		printf(" [1] Add a name to the list.\n");
		printf(" [2] Remove a name from the list.\n");
		printf(" [3] Show the list of names.\n");
		printf(" [4] Quit the program.\n\n");

		scanf("%d", &input);

		switch (input) {
			case 1:
				printf("What is the guest's name? ");
				scanf("%s", name);
				printf("\nHow many people are in the party? ");
				scanf("%d", &size);

				insert(name, size);
				break;
			case 2: 
				delete();
				break;
			case 3: 
				list();
				break;
			default:
				save_data(argv[1]);
				return 0;

		}
	}
}

void insert (char *name, int size) {
	INFO_NODE *temp;
	INFO_NODE *p;	
	int i;
	int j;

	for (i = 0; i < 4; i++) {
		temp = heads[i];
		while (temp != NULL) {
			if (strcmp(name, temp->table_name) == 0) {
				printf("The name is already on the waiting list!\n\n");
				return;
			}
			
			tails[i] = temp;
			temp = temp->next;
		}
	}

	p = (INFO_NODE *)malloc(sizeof(INFO_NODE));			

	if (p == NULL) {
		printf("Could not allocate memory.\n");
		return;
	}
	
	p->table_size = size;
	strcpy(p->table_name, name);

	p->next = NULL;

	switch (size) {
		case 1:
		case 2:
			j = 0;
			break;
		case 3:
		case 4:
			j = 1;
			break;
		case 5:
		case 6:
			j = 2;
			break;
		default:
			j = 3;
			break;
	}
	
	if (heads[j] == NULL) {
		heads[j] = p;
		tails[j] = p;

		printf("\n%s has been added to the waiting list.\n\n", p->table_name);
		return;
	}

	else {
		tails[j]->next = p;
	}

	tails[i] = p;
	return;
}

void delete() {
	INFO_NODE *p;
	INFO_NODE *q;
	int open_table = 0;
	int i;

	printf("What is the size of the next available table? ");
	scanf("%d", &open_table);

	switch (open_table) {
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

	for (i = i; i >= 0; i--) {
		if (heads[i] == NULL) {
			printf("\nThere are no reservations to cancel.\n");
		}

		else {
			q = heads[i];
			p = q->next;

			if (q -> table_size <= open_table) {
				printf("\n%s's table has been cleared.\n", q->table_name);
				heads[i] = heads[i]->next;
				free(q);
				return;
			}

			while (p != NULL) {
				if (p->table_size <= open_table) {
					printf("\n%s's table has been cleared.\n", p->table_name);
					q->next = p->next;
					free(p);
					return;
				}

				p = p->next;
				q = q->next;
			}
		}
	}

	printf("\nThere are no tables to accomodate that size right now.\n");

}

void list() {
	INFO_NODE *p;
	int i;

	for (i = 0; i < 4; i++) {
		p = heads[i];
		while (p != NULL) {
			printf("\n%s\t%d\n", p->table_name, p->table_size);
			p = p->next;
		}
	}
	return;
}

void read_data (char *file_name) {
	FILE *fp;
	char name[20];
	int size;
	
	fp = fopen(file_name, "r");

	if (fp == NULL) {
		printf("Can't open file %s", name);
		return;
	}

	fseek(fp, 50, SEEK_SET);
	
	while (fscanf(fp, "%s %d", name, &size) == 2) {
		printf("Reading file.\n");
		insert(name, size);
	}

	fclose(fp);
	return;
}

void save_data (char *file_name) {
	FILE *fp;
	INFO_NODE *p;
	INFO_NODE *q;
	int i;

	fp = fopen(file_name, "w");

	if (fp == NULL) {
		printf("Can't open file.\n");
		return;
	}

	fprintf(fp, "Name:\t\tGroup Size:\t\n------------------------------\n");
	
	for (i = 0; i < 4; i++) {	
		p = heads[i];
		q = p;
		while (p != NULL) {
			fprintf(fp, "%s %d\n", p->table_name, p->table_size);
			p = p->next;
			free(q);
		}
	} 

	fclose(fp);
	return;
}

	 


