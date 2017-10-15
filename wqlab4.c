#include <stdio.h>
#include <string.h>

typedef union {									//declare union for types depending on age
	char school_name[10];
	float salary;
	int retirement_year;
} UNION_T;

typedef struct {								//declare a structure variable 
	char name[10];								//member inside struct for name
	int age;								//member inside struct for age
	UNION_T u;								//union member inside struct
} INFO; 

INFO array[10];									//declare array for structs

void insert();									//declare functions
void delete();
void list();
int list_length = 0;								//global counter

int main(void) {								//main function
	int input;						
	
	while (1) {								//forever loop to continuously repeat program
		printf("What do you want to do?\n");				
		printf(" [1] Add a name to the list.\n");
		printf(" [2] Remove a name from the list.\n");
		printf(" [3] Show the list of names.\n");
		printf(" [4] Quit the program.\n\n");

		scanf("%d", &input);						//receive input from user

		switch (input) {						//switch function to switch between functions
			case 1:
				insert();					//calls insert function
				break;
			case 2:
				delete();					//calls delete function
				break;
			case 3:
				list();						//calls list function 
				break;
			default:
				return 0;					//quits program 
		}
	}
}

void insert() {									//function to allow user to add entries
	if (list_length == 10) {
		printf("Sorry, the list of people is full.\n\n");		//returns if array is full
		return;
	}

	else {
		printf("What is your name?\n");
		scanf("%s", array[list_length].name);				//receives name from user
		printf("What is your age?\n");
		scanf("%d", &array[list_length].age);				//receives age from user
		if (array[list_length].age <= 21) {				//if age < 21, asks for school name
			printf("What school do you go to?\n");
			scanf("%s", array[list_length].u.school_name);		//receives school name from user
		}
		else if (array[list_length].age > 21 && array[list_length].age < 65) {	//if 21 < age < 65, asks for salary
			printf("What is your monthly salary?\n");
			scanf("%f", &array[list_length].u.salary);
		}
		else {
			printf("How many years have you been in retirement?\n");	//if age > 65, asks for retirement years
			scanf("%d", &array[list_length].u.retirement_year);
		}

		printf("The name has been added to the list!\n\n");		
		list_length++;
		return;
	}
}

void delete() {
	if (list_length == 0) {							//outputs if there are no names in the list 
		printf("There are no names to be removed.\n");
		return;
	}

	int i;
	int pos = 0;
	char temp[10];								//temp string to receive name from user 
	
	printf("What name do you want to remove?\n");
	scanf("%s", temp);
	
	for (i = 0; i < list_length; i++) {					//traverses array to find matching name
		if (strcmp(temp, array[i].name) == 0) {
			pos = i;						//records position of matching name
			break;
		}
	}

	if (i != list_length) {
		array[pos] = array[list_length - 1];				//shifts name of bottom up to replace removed name
		list_length--;
	}

	printf("The name has been removed from the list.\n\n");
}

void list() {
	if (list_length == 0) {							//outputs if there are no names in list
		printf("There is currently no one on the list!\n");
		return;
	}
	
	int i;
	for (i = 0; i < list_length; i++) {					//prints all info 
		if (array[i].age <= 21) {
			printf("%s | %d | School Name: %s\n", array[i].name, array[i].age, array[i].u.school_name);
		}
		else if (array[i].age > 21 && array[i].age < 65) {
			printf("%s | %d | Monthly Salary: $%0.2f\n", array[i].name, array[i].age, array[i].u.salary);
		}
		else {
			printf("%s | %d | Years in Retirement: %d\n", array[i].name, array[i].age, array[i].u.retirement_year);
		}
	}
}
	

	
		





























