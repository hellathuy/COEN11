#include <stdio.h>
#include <string.h>

char names[10][20];		// global array #1
int num_people[10];		// global array #2
int list_length = 0;		// global counter

int insert();			// declare functions
int delete();
int list();

int main (void) {
	int input;

	while (1) {		// forever loop to run program over and over again until user stops
		printf("What do you want to do?\n [1] Add a name to the waiting list.\n [2] Remove a name from the waiting list.\n [3] Show the waiting list.\n [4] Quit.\n");
	
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
				return 0;		// quits program
		}
	}
}

int insert() {			// insert function to allow user to input names
	int i;			// local variables
	int j;
	char name[20];			// array to receive guest name
	int party_size = 0;		

	if (list_length == 10) {	// returns if there are already 10 names on the waiting list
		printf("Sorry, the waiting list is full. Try adding the name again later.\n");
	}

	else {				
		printf("What is the guest's name?\n");
		scanf("%s", name);

		for (i = 0; i < 10; i++) {		// check to see if inputted name is already on the list
			if (strcmp(name, names[i]) == 0) {
				printf("The name is already on the waiting list!\n");
				break;
			}
		}

		if (i == 10) {				// add guests onto the waiting list
			for (j = 0; j < 10; j++) {
				if (names[j][0] == '\0') {
					strcpy(names[j], name);
					printf("How many people are in the party?\n");		// recieves info on how many people are in the party
					scanf("%d", &party_size);
					num_people[j] = party_size;
					printf("The name has been added to the waiting list.\n");
					list_length++;
					break;
				}
			}
		}
	}
	
	return 0;
}

int delete() {					// deletes guests from waiting list once there is a table ready for them
	int c;
	int m;

	int table_size = 0;
	int largest_table = 0;

	printf("What is the size of the next available table?\n");		// allows user to input how many seats are at the table
	scanf("%d", &table_size);

	for (c = 0; c < 10; c++) {
		if (num_people[c] > 0 && num_people[c] <= table_size) {		// finds table for guests that fit the constraints
			printf("%s's table for %d people is ready! The name will now be removed off of the waiting list.\n", names[c], num_people[c]);
			names[c][0] = '\0';
			num_people[c] = 0;
			
			for(m = c + 1; m < 10; m++) {				// shifts all names up
				strcpy(names[m - 1], names[m]);
				num_people[m - 1] = num_people[m];
			}

			names[list_length - 1][0] = '\0';
			num_people[list_length] = 0;
			list_length--;
	
			break;
		}

		if (c == 9) {				// outputs if the table can't fit anyone
			printf("There are no parties that can fit that table.\n");
		}
	}

	return 0;
}

int list() {				// function to output the waiting list
	int p;

	printf("There are %d names on the waiting list:\n", list_length);

	for (p = 0; p < list_length; p++) {			// prints waiting list
		if (names[p][0] != '\0') {
			printf("%d. %s\t%d\n", p + 1, names[p], num_people[p]);
		}
	}

	return 0;
}   
			
