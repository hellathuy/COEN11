#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void insert(char*, int);						//declare functions
void delete();
void list();
void save_data (char*);
void read_data (char*);

typedef struct node {							//declare a structure variable
	char table_name[20];						//member inside struct for name 
	int table_size;							//member inside struct for size
	struct node *next;						//pointer to the next item in list
} INFO_NODE;

INFO_NODE *head = NULL;							//declare head and tail pointer
INFO_NODE *tail = NULL;

int main(int argc, char *argv[]) {					//main function
	int input;
	char name[20];
	int size;

	if (argc == 1) {						//return if file name is not declared
		printf("The file name is missing.\n");
		return -1;
	}

	else {
		read_data(argv[1]);
	}

	while (1) {							//forever loop to continuously repeat program
		printf("What do you want to do?\n");
		printf(" [1] Add a name to the list.\n");
		printf(" [2] Remove a name from the list.\n");
		printf(" [3] Show the list of names.\n");
		printf(" [4] Quit the program.\n\n");
		
		scanf("%d", &input);					//receive input from user
	
		switch(input) {						//switch function to switch between functions
			case 1:
				printf("What is the guest's name? ");
				scanf("%s", name);
				printf("\nHow many people are in the party? ");
				scanf("%d", &size);
				
				insert(name, size);			//calls insert function
				break;
			case 2:		
				delete();				//calls delete function
				break;
			case 3: 
				list();					//calls list function
				break;
			default:
				save_data(argv[1]);
				return 0;				//quits program
		}
	}
}

void insert(char *name, int size) {					//function to allow user to add names to list
	INFO_NODE *n = (INFO_NODE*)malloc(sizeof(INFO_NODE));		//malloc for pointer n
	
	if (n == NULL) {						
		printf("Could not allocate memory.\n");
		return;
	}

	n->table_size = size;
	strcpy(n->table_name, name);

	if (head == NULL) {						//occurs if head is NULL
		head = n;
		tail = n;
		
		printf("\n%s has been added to the waiting list.\n\n", n->table_name);
		return;
	}

	else {								//occurs if head is not NULL
		INFO_NODE *p = head;

		while (p != NULL) {					//traverses list
			if (strcmp(p->table_name, n->table_name) == 0) {	//makes sure there are no repeats
				printf("The name is already on the waiting list!\n\n");
				free(n);
				return;
			}
			
			p = p->next;

			if (p == NULL) {
				break;
			}					
		}
	}

	tail->next = n;
	tail = n;
	tail->next = NULL;
	printf("\n%s has been added to the waiting list.\n\n", n->table_name);
}

void delete() {								//function to remove names from list
	INFO_NODE *p = head;
	int open_table = 0;

	if (head == NULL) {						//outputs if there are no names in list
		printf("There are no parties to cancel.\n");
		return;
	}

	printf("What is the size of the next available table? ");
	scanf("%d", &open_table);

	if (head->table_size > open_table) {				//if head is greater than the open table size
		while (p->next != NULL) {				//traverses list to find a size that fits
			if (p->next->table_size <= open_table) {
				break;
			}
			
			p = p->next;
		
			if (p->next == NULL) {				//outputs if nothing in the list fits
				printf("\nThere are no parties that can fit that table.\n\n");
				return;
			}
		}

		INFO_NODE *n = p->next;					//removes the node that fits the open table
		p->next = p->next->next;
		if (p->next == NULL) {
			tail = p;
		}

		free(n);						//frees memory
	}
	
	else {								//if head fits the open table size
		head = head->next;
		free(p);						//frees memory
	}

	printf("\n%s will be removed off of the waiting list.\n\n", p->table_name);
}

void list() {								//function to list all names
	INFO_NODE *p = head;
	
	while (p != NULL) {						//traverses list and prints name
		printf("\n%s\t%d\n", p->table_name, p->table_size);
		p = p->next;
	}
}

void read_data (char *file_name) {					//reads data from text file
	FILE *fp;							//declare file
	char name[20];
	int size;

	fp = fopen(file_name, "r");					//open file

	if (fp == NULL) {						
		printf("Can't open file %s", name);
		return;
	}

	fseek(fp, 50, SEEK_SET);					//skips certain amount of spaces

	while (fscanf(fp, "%s %d", name, &size) == 2) {			//reads file and inserts info into insert function
		printf("Reading file.\n");
		insert(name, size);
	}

	fclose(fp);							//closes file
	return;
}

void save_data (char *file_name) {					//saves data to text file
	FILE *fp;							//declare file
	INFO_NODE *p = head;						

	fp = fopen(file_name, "w");					//open file to write

	if (fp == NULL) {
		printf("Can't open file.\n");
		return;
	}

	fprintf(fp, "Name:\t\tGroup Size:\t\n------------------------------\n");

	while (p != NULL) {						//prints info to file
		fprintf(fp, "%s %d\n", p->table_name, p->table_size);
		p = p->next;
	}

	fclose(fp);							//closes file
	return;
}













