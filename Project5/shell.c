#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>

int main() {
	const char del[11] = "()|&; \t\n";
	char input[1024];
	char *token;
	char *args[64];
	int numArgs;
	int lineNum = 0;
	int i;
	int err;
	FILE *outfp;
	FILE *infp;

	char *outStr;
	char *inStr;
	int outApp;


	while(1) {
		// reset variables
		numArgs = 0;
		err = 0;
		outfp = NULL;
		infp = NULL;
		outStr = NULL;
		inStr = NULL;
		outApp = 0;

		lineNum++;

		// get input
		printf("myShell (%d): ", lineNum);
		fgets(input, 1024, stdin);

		// tokenize input, store it in the args array
		token = strtok(input, del);
		while (token != NULL && numArgs < 63) {
			char* arg = (char *) malloc(strlen(token) + 1);
			strcpy(arg, token);
			args[numArgs] = arg;

			numArgs++;
			token = strtok(NULL, del);
		}

		// null terminate the array
		args[numArgs] = NULL;


		// check for file redirection
		for (i = 0; i < numArgs; i++) {
			if (args[i] != NULL) {
				if (strcmp("<", args[i]) == 0) {
					if (i < numArgs - 1) {
						inStr = args[i + 1];
						args[i] = NULL;
						args[i + 1] = NULL;
					} else {
						err = 1;
					}
				} else if (strcmp(">", args[i]) == 0) {
					if (i < numArgs - 1) {
						outStr = args[i + 1];
						args[i] = NULL;
						args[i + 1] = NULL;
						outApp = 0;
					} else {
						err = 1;
					}
				} else if (strcmp(">>", args[i]) == 0) {
					if (i < numArgs - 1) {
						outStr = args[i + 1];
						args[i] = NULL;
						args[i + 1] = NULL;
						outApp = 1;
					} else {
						err = 1;
					}
				} 
			}
		}


		if (args[0] != NULL) {
			if (err == 0) {

				// exit
		 		if (strcmp(args[0], "exit") == 0) {
					exit(0);

				// cd
				} else if (strcmp(args[0], "cd") == 0) {
					if (args[1] != NULL) {
						err = chdir(args[1]);
						if (err != 0) {
							printf("Error: %s\n", strerror(errno));
						}
					}

				// execvp
				} else {

					// child
					if (fork() == 0) {

						// check if we need to redirect files
						if (outStr != NULL) {
							if (outApp) {
								outfp = freopen(outStr, "a", stdout);
							} else {
								outfp = freopen(outStr, "w", stdout);
							}

							if (outfp == NULL)
								err = 1;
						} 

						if (inStr != NULL) {
							infp = freopen(outStr, "r", stdin);

							if (infp == NULL)
								err = 1;
						}

						// if file redirection didn't fail
						if (err == 0) {
							err = execvp(args[0], args);
							if (err != 0) {
								printf("Error: %s\n", strerror(errno));
							}

						// failed file redirection
						} else {
							printf("Error: Could not redirect file IO\n");
						}

						// kill child 
						exit(0);

					// parent
					} else {
						int status;
						wait(&status);
					}
				}
			} else {
				printf("Error: No redirect file specified\n");
			}
		} 

		// free space allocated for seperate arg strings
		for (i = 0; i < numArgs; i++) {
			if (args[i] != NULL) {
				free(args[i]);
				args[i] = NULL;
			}
		}	
	}
}