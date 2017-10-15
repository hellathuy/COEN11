#include <stdio.h>
#include <time.h>
#include <stdlib.h>

int correct = 0;
int ans;
int i = 0;
int c = 0;
int division(int, int, int);

int main (void) {
	srand ((int) time(NULL));

	/*generates random numbers 10 times*/	
	while (i < 10) {
		/*generate random numbers for the divisor and quotient*/
		int y = rand() % 12 + 1;
		int z = rand() % 13;
		int x = y * z;

		printf("What is %d/%d?\n", x, y);
		c = division(x, y, z);
		
		/*counts how many correct answers there are*/
		if (c == 1) {
			correct++;
		}

		i++;
	}

	/*calculates percentage*/
	double p = ((double)correct/10) * 100;

	printf("You got %.0f%% of the questions right!\n", p);
}

/*function to check user input*/
int division (int x, int y, int z) {
	scanf("%d", &ans);

	if (ans == z) {
		printf("You got the answer right!\n\n");
		return 1;
	}

	else { 
		printf("You got the answer wrong. The correct answer is %d.\n\n", z);
		return 0;
	}
}
