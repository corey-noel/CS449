#include <time.h>
#include <stdlib.h>
#include <stdio.h>

int main() {
	// game info
	int point = 0;
	int roll = 0;
	int die1 = 0;
	int die2 = 0;

	// input info
	char name[100];
	char input[100];

	// control
	int playing = 1;
	int looping = 0;

	int wins = 0;
	int losses = 0;

	// seeding rng
	srand(time(NULL));

	printf("Welcome to Corey's Casino!\n");
	printf("Please enter your name: ");
	scanf("%s", &name);

	// seeing if user wants to play
	looping = 1;
	while (looping) {
		printf("%s, would you like to Play or Quit? ", name);
		scanf("%s", &input);
		if (input[0] == 'p' || input[0] == 'P') {
			looping = 0;
			playing = 1;
		} else if (input[0] == 'q' || input[0] == 'Q') {
			looping = 0;
			playing = 0;
		} else {
			printf("I didn't get that! Try again.\n");
		}
	}
	
	while (playing) {
		printf("\n");
		looping = 1;

		// first roll
		die1 = rollDie() + 1;
		die2 = rollDie() + 1;
		roll = die1 + die2;

		printf("You rolled %d + %d = %d\n", die1, die2, roll);

		// win, lose, or set point and keep rolling
		if (roll == 7 || roll == 11) {
			looping = 0;
			wins++;
			printf("You win!\n");
		} else if (roll == 2 || roll == 3 || roll == 12) {
			looping = 0;
			losses++;
			printf("You lose!\n");
		} else {
			point = roll;
		}

		// while trying to achieve point
		while (looping) {
			printf("The point is %d.\n", point);
			die1 = rollDie() + 1;
			die2 = rollDie() + 1;
			roll = die1 + die2;

			printf("You rolled %d + %d = %d\n", die1, die2, roll);

			// win, lose, or new point
			if (roll == 7) {
				looping = 0;
				losses++;
				printf("You lose!\n");
			} else if(roll == point) {
				looping = 0;
				wins++;
				printf("You win!\n");
			} else {
				printf("\n");
			}
		}

		// see if user wants to play again
		printf("\nYou have %d wins and %d losses.\n", wins, losses);
		looping = 1;
		while (looping) {
			printf("%s, Would you like to play again? ", name);
			scanf("%s", &input);
			if (input[0] == 'y' || input[0] == 'Y') {
				looping = 0;
				playing = 1;
			} else if (input[0] == 'n' || input[0] == 'N') {
				looping = 0;
				playing = 0;
			} else {
				printf("I didn't get that! Try again.\n");
			}
		}
	}

	printf("Goodbye!\n");
}

int rollDieOld() {
	return rand() % 6;
}

int rollDie() {
	File *file = fopen("/dev/dice", "rb");
	char* buf;
	fread(buf, 1, 1, file);
	printf("Rolled %d", (int)*buf);
	return (int)*buf;
}