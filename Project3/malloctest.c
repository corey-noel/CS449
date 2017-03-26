// Corey Noel
// For CS 449
// Project 3
#include <stdlib.h>
#include <stdio.h>
#include "mymalloc.c"

void main() {
	int* arr;
	int i;

	printf("Brk:%p\n", sbrk(0));
	arr = (int *)my_bestfit_malloc(sizeof(int) * 10);
	printf("Brk:%p\n", sbrk(0));

	for (i = 0; i < 10; i++) {
		arr[i] = i;
	}

	for (i = 0; i < 10; i++) {
		printf("%p @ %d\n", &arr[i], arr[i]);
	}

	my_free(arr);
	printf("Brk:%p\n", sbrk(0));
}
