#include <stdio.h>
#include <string.h>

struct entry {			//declare a structure variable, entry
	char names[20];		//member inside struct for guest name
	int num_people;		//member inside struct for guest party size
};

struct entry waiting_list[10];		//declare array for structures

int list_length = 0;		//global counter

int insert();			// declare functions
void delete();
int list();
int search_size();
 
int main (void) {		//main function
	int input;

	while (1) {		// forever loop to run program over and over again until user stops
		printf("What do you want to do?\n [1] Add a name to the waiting list.\n [2] Remove a name from the waiting list.\n [3] Show the waiting list.\n [4] See guests that can fit table size.\n [5] Quit.\n\n");
	
		scanf("%d", &input);		// receive input from user
		

		switch (input) {			// switch function to switch between program functions
			case 1: 
				insert();		// calls insert function
				break;
			case 2: 
				delete();		// calls delete function
				break;
			case 3:
				list();			// calls list function
				break;
			case 4:
				search_size();		// calls search_size function
				break;
			default: 
				return 0;		// quits program
		}
	}
}

int insert() {			// insert function to allow user to input names
	char name[20];			// array to receive guest name
	int party_size = 0;	
	int duplicates = 0;
	struct entry *p = &waiting_list[0];

	if (list_length == 10) {	// returns if there are already 10 names on the waiting list
		printf("Sorry, the waiting list is full. Try adding the name again later.\n\n");
	}

	else {				
		printf("What is the guest's name?\n");
		scanf("%s", name);

		while (*p->names != '\0') {		// check to see if inputted name is already on the list
			if (strcmp(p->names, name) == 0) {
				printf("The name is already on the waiting list!\n\n");
				duplicates++;
				break;
			}
			p++;
		}
		
		if (duplicates == 0) {			// add guests onto the waiting list
			strcpy(p->names, name);
			printf("\nHow many people are in the party?\n");		// recieves info on how many people are in the party
			scanf("%d", &party_size);
			p->num_people = party_size;
			printf("The name has been added to the waiting list.\n\n");
			list_length++;
		}
	}	
	return 0;
}

void delete() {					// deletes guests from waiting list once there is a table ready for them
	struct entry *p = &waiting_list[0];

	int table_size;
	int flag = 0;

	printf("What is the size of the next available table?\n");		// allows user to input how many seats are at the table
	scanf("%d", &table_size);

	while (*p->names != '\0') {
		if (p->num_people > 0 && p->num_people <= table_size) {		// finds table for guests that fit the constraints
			printf("\n%s's table for %d people is ready! The name will now be removed off of the waiting list.\n\n", p->names, p->num_people);
			
			while (*p->names != '\0') {			//shift names up
				strcpy(p->names, (p+1)->names);
				p->num_people = (p+1)->num_people;
				p++;
			}

		(p-1)->names[0] = '\0';				//resets names to null
		p->num_people = 0;
		list_length--;
		flag++;	
		return;
		}
			
	p++;
	}
	
	if (flag == 0) {				// outputs if the table can't fit anyone
		printf("\nThere are no parties that can fit that table.\n\n");
	}
	return;
}

int list() {				// function to output the waiting list
	struct entry *p = &waiting_list[0];

	printf("\nThere are %d names on the waiting list:\n", list_length);

	while (*p->names != '\0') {
		printf("%s\t%d\n", p->names, p->num_people);
		p++;
	}

	return 0;
}   

int search_size() {			//function to output which guests can exactly fit the table
	struct entry *p = &waiting_list[0];
	int table_size;
	
	printf("What is the size of the next table?\n");
	scanf("%d", &table_size);
	
	while (*p->names != '\0') { 
		if (p->num_people == table_size) {
			printf("These are the guests that can fit the table:\n");
			printf("\n%s\t%d\n", p->names, p->num_people);
		}
		p++;
	}
	return 0;
}
			
