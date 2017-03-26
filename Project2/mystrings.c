// Corey Noel
// For CS 449
// Assignment 2

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
	char *input;
	long inputSize;
	FILE *file;

	long lastNP = -1;
	long pos = 0;


	if (argc < 2) {
		printf("Error: no filename specified.\n");
		return 1;
	}

	file = fopen(argv[1], "r");
	if (file == 0) {
		printf("Error: could not open file %s.\n", argv[1]);
		return 1;
	}

	// read in entire file
	file = fopen(argv[1], "rb");
	fseek(file, 0, SEEK_END);
	inputSize = ftell(file);
	rewind(file);

	input = malloc(inputSize + 1);
	fread(input, 1, inputSize, file);
	fclose(file);
	input[inputSize] = 0;

	// search through, looking for characters 
	while (pos < inputSize) {
		if (input[pos] < 32 || input[pos] > 126) {
			if (pos - lastNP > 4) {
				printf("%.*s\n", (pos - lastNP + 1), input + lastNP + 1);
			}
			lastNP = pos;
		}
		pos++;
	}

	// trailing string
	if (pos - lastNP > 4) {
		printf("%.*s\n", (pos - lastNP + 1), input + lastNP + 1);
	}

	free(input);
}