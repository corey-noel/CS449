#include <pthread.h>
#include <stdio.h>

void * threadFunct(void * ptr) {
	while (1) {
		printf("Hello from thread %d - A\n", *((int *) ptr));
		pthread_yield();
		printf("Hello from thread %d - B\n", *((int *) ptr));
	}
}

int main() {
	pthread_t thread;
	int arg1 = 1; 
	int arg2 = 2;
	pthread_create(&thread, NULL, threadFunct, (void *)&arg2);
	threadFunct((void *)&arg1);
}