#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void insert();								//decclare functions
void delete();
void list();

typedef struct node {							//declare a structure variable
	char table_name[20];						//member inside struct for name 
	int table_size;							//member inside struct for size
	struct node *next;						//pointer to the next item in list
} node_t;

node_t *head;								//declare head and tail pointer
node_t *tail;

int main(void) {							//main function
	int input;

	while (1) {							//forever loop to continuously repeat program
		printf("What do you want to do?\n");
		printf(" [1] Add a name to the list.\n");
		printf(" [2] Remove a name from the list.\n");
		printf(" [3] Show the list of names.\n");
		printf(" [4] Quit the program.\n\n");
		
		scanf("%d", &input);					//receive input from user
	
		switch(input) {						//switch function to switch between functions
			case 1:
				insert();				//calls insert function
				break;
			case 2:		
				delete();				//calls delete function
				break;
			case 3: 
				list();					//calls list function
				break;
			default:
				return 0;				//quits program
		}
	}
}

void insert() {								//function to allow user to add names to list
	node_t *n = (node_t*)malloc(sizeof(node_t));			//malloc for pointer n
	printf("What is the guest's name? ");
	scanf("%s", n->table_name);

	if (head == NULL) {						//occurs if head is NULL
		head = n;
		tail = n;
		
		printf("\nHow many people are in the party? ");
		scanf("%d", &n->table_size);
		printf("\n%s has been added to the waiting list.\n\n", n->table_name);
		return;
	}

	else {								//occurs if head is not NULL
		node_t *p = head;
		while (p != NULL) {					//traverses list
			if (strcmp(p->table_name, n->table_name) == 0) {	//makes sure there are no repeats
				printf("The name is already on the waiting list!\n\n");
				return;
			}
			p = p->next;					
		}
	}

	printf("\nHow many people are in the party? ");			//adds names if head is not NULL
	scanf("%d", &n->table_size);

	printf("\n%s has been added to the waiting list.\n\n", n-> table_name);

	tail->next = n;
	tail = n;
	tail->next = NULL;
}

void delete() {								//function to remove names from list
	node_t *p = head;
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

		node_t *n = p->next;					//removes the node that fits the open table
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
	node_t *p = head;
	while (p != NULL) {						//traverses list and prints name
		printf("\n%s\t%d\n", p->table_name, p->table_size);
		p = p->next;
	}
}

