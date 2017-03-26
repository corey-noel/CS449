// Corey Noel
// For CS 449
// Assignment 1

#include <stdio.h>
#include <time.h>
#include <stdlib.h>

// function to get a string name from a num value
// 0 = rock, 1 = paper, 2 = scissors
char *getName(int value) {
    if (value == 0) 
        return "rock";

    if (value == 1)
        return "paper";

    if (value == 2) 
        return "scissors";
}


int main() {
    int humanScore = 0;
    int humanChoice;
    int compScore = 0;
    int compChoice;
    int looping = 1;
    char input[100];
    // seeding rand
    srand((unsigned int)time(NULL)); 


    printf("Welcome to rock paper scissors!\n");
    printf("Would you like to play? ");

    // loops until it gets a valid input (starts with y or n)
    // exits program if n, continues on if y
    while (looping) {
        scanf("%s", input);

        if (input[0] == 'y' || input[0] == 'Y') {
            looping = 0;
        } else if (input[0] == 'n' || input[0] == 'N') {
            printf("Well, thanks anyway!\n");
            return 0;
        } else {
            printf("Sorry, I couldn't understand that.\n");
            printf("Do you want to play? [Y]es or [N]o? ");
        }
    }

    printf("Alright, let's get started!\n");
    printf("You can throw [R]ock, [P]aper, or [S]cissors.\n");

    // the main game loop
    // loops for each round
    while (1) {
        printf("\n");
        printf("Throw down! ");

        // loops for valid human choice
        looping = 1;
        while (looping) {
            scanf("%s", input);

            if (input[0] == 'r' || input[0] == 'R') {
                looping = 0;
                humanChoice = 0;
            } else if (input[0] == 'p' || input[0] == 'P') {
                looping = 0;
                humanChoice = 1;
            } else if (input[0] == 's' || input[0] == 'S') {
                looping = 0;
                humanChoice = 2;
            } else {
                printf("What was that? [R]ock, [P]aper, or [S]cissors. ");
            }
        }

        // generate computer choice
        compChoice = rand() % 3;

        // calculate victor and change scores
        printf("You picked: %s. \nThe Computer picked: %s. \n", getName(humanChoice), getName(compChoice));    
        if (humanChoice == compChoice) {                    
            // tie
            printf("It was a draw! Nobody wins!\n");
        } else if (humanChoice == (compChoice + 2) % 3) {   
            // computer won
            printf("Uh oh! Looks like the computer won.\n");
            compScore++;
        } else {
            // human won
            printf("You did it! You beat the computer this round.\n");
            humanScore++;
        }

        // display scores
        printf("You: %d \nThe Computer: %d\n", humanScore, compScore);

        // loop for input on exiting or playing again
        printf("Do you want to keep playing? ");
        looping = 1;
        while (looping) {
            scanf("%s", input);

            if (input[0] == 'y' || input[0] == 'Y') {
                looping = 0;
            } else if (input[0] == 'n' || input[0] == 'N') {
                printf("Goodbye!\n");
                return 0;
            } else {
                printf("Sorry, I couldn't understand that.\n");
                printf("Do you want to keep playing? [Y]es or [N]o? ");
            }
        }
    }
}   