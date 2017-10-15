#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void insert(char*, int);						//declare functions 
void delete();
void list();
void char_count();
void display_backwards();
void backwards(char*);
void save_data (char*);
void read_data (char*);

typedef struct node {							//declare a structure variable
	char table_name[20];						//member inside struct for name 
	int table_size;							//member inside struct for size
	struct node *next;						//pointer to the next item in list
} INFO_NODE;

INFO_NODE *heads[4];							//declare head and tail pointer arrays
INFO_NODE *tails[4];

int main (int argc, char *argv[]) {					//main function
	int input;
	char name[20];
	int size; 
	
	if (argc == 1) {						//return if file name is not declared 
		printf("The file name is missing.\n");
	}

	else {
		read_data(argv[1]);
	}

	while (1) {							//forever loop to continuously repeat program
		printf("What do you want to do?\n");
		printf(" [1] Add a name to the list.\n");
		printf(" [2] Remove a name from the list.\n");
		printf(" [3] Show the list of names.\n");
		printf(" [4] Count how many characters there are in the names.\n");
		printf(" [5] Print out names backwards.\n");
		printf(" [6] Quit the program.\n\n");

		scanf("%d", &input);					//receive input from user

		switch (input) {					//switch function to switch between functions
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
			case 4:
				char_count();				//calls character count function
				break;			
			case 5:
				display_backwards();			//calls function to display name backwards
				break;	
			default:
				save_data(argv[1]);			//quits and saves program to text file
				return 0;

		}
	}
}

void insert (char *name, int size) {					//function to allow user to add names to list 
	INFO_NODE *temp;						//declare temp and p pointers
	INFO_NODE *p;	
	int i;
	int j;

	for (i = 0; i < 4; i++) {					//traverses lists 
		temp = heads[i];
		while (temp != NULL) {					//checks for duplicates
			if (strcmp(name, temp->table_name) == 0) {
				printf("The name is already on the waiting list!\n\n");
				return;
			}
			
			tails[i] = temp;
			temp = temp->next;
		}
	}

	p = (INFO_NODE *)malloc(sizeof(INFO_NODE));			//malloc for pointer p

	if (p == NULL) {
		printf("Could not allocate memory.\n");
		return;
	}
	
	p->table_size = size;
	strcpy(p->table_name, name);

	p->next = NULL;

	switch (size) {							//switch function to sort table sizes into groups
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
	
	if (heads[j] == NULL) {						//adds name to list
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

void delete() {								//function to remove names from list
	INFO_NODE *p;
	INFO_NODE *q;
	int open_table = 0;
	int i;

	printf("What is the size of the next available table? ");
	scanf("%d", &open_table);

	switch (open_table) {						//determine which group the open table falls into
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
									//outputs if there are no tables that can fit the open table
	printf("\nThere are no tables to accomodate that size right now.\n");

}

void list() {								//function to list all names
	INFO_NODE *p;
	int i;

	for (i = 0; i < 4; i++) {					//traverses list and prints name
		p = heads[i];
		while (p != NULL) {
			printf("\n%s\t%d\n", p->table_name, p->table_size);
			p = p->next;
		}
	}
	return;
}

void char_count () {							//function to count how many instances of a certain character
	INFO_NODE *p;
	char *q;
	int i;
	char letter;
	int counter = 0;
	
	printf("Input a letter. ");					//allows user to input in a letter
	fpurge(stdin);			
	scanf("%c", &letter);

	for (i = 0; i < 4; i++) {					//traverses list and counts the letter
		p = heads[i];
		while (p != NULL) {
			q = p->table_name;
			while (*q != '\0') {
				if (*q == letter) {
					counter++;
				}
				q++;
			}
			p = p->next;
		}		
	}								//outputs how many letters there are
	printf("There were %d instances of %c in the guest list.\n\n", counter, letter);
}

void display_backwards () {						//function to display how names backwards
	INFO_NODE *p;
	INFO_NODE *temp;
	int i;

	printf("Here are the names in the waiting list reversed backwards.\n");
	for (i = 0; i < 4; i++) {
		p = heads[i];
		while (p != NULL) {
			char temp[20];
			strcpy(temp, p->table_name);
			backwards(temp);				//passes each name to the backwards function
			printf("\n");
			p = p->next;
		}
	}
}

void backwards (char *temp) {						//function to actually reverse the names
	if (*temp) {
		backwards(temp + 1);					//recursive!
		printf("%c", *temp);
	}
}

void read_data (char *file_name) {					//function to read data from text file
	FILE *fp;							//declare file
	char name[20];
	int size;
	
	fp = fopen(file_name, "r");					//open file

	if (fp == NULL) {
		printf("Can't open file %s", name);
		return;
	}

	fseek(fp, 50, SEEK_SET);					//skips certain amount of spaces
	
	while (fscanf(fp, "%s %d", name, &size) == 2) {			//read file and inserts infor into insert function
		printf("Reading file.\n");
		insert(name, size);
	}

	fclose(fp);							//closes file
	return;
}

void save_data (char *file_name) {					//function to save data to text file
	FILE *fp;							//declare file
	INFO_NODE *p;
	INFO_NODE *q;
	int i;

	fp = fopen(file_name, "w");					//open file to write

	if (fp == NULL) {
		printf("Can't open file.\n");
		return;
	}

	fprintf(fp, "Name:\t\tGroup Size:\t\n------------------------------\n");
	
	for (i = 0; i < 4; i++) {	
		p = heads[i];
		q = p;
		while (p != NULL) {					//prints info to file
			fprintf(fp, "%s %d\n", p->table_name, p->table_size);
			p = p->next;
			free(q);
		}
	} 

	fclose(fp);							//closes file
	return;
}

