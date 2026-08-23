#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>


int main(int argc, char **argv) {
	int32_t verbose = 0;

	if (argc == 0) {
		printf("what are the . Files");
	}

	char *trash_dir = (char *)malloc(129 + strlen("/.trash/"));
	if (getenv("HOME") == NULL) printf("???\n");

	if (strlen(getenv("HOME")) > 128) {
		printf("username too long\n");
		free(trash_dir);
		exit(1);
	}

	strcpy(trash_dir, getenv("HOME"));
	strcat(trash_dir, "/.trash/");

	for (int32_t i = 1; i < argc; i++) {
		if (!strcmp(argv[i], "-v")) verbose = 1;
			
	}

	for (int32_t i = 1; i < argc; i++) {
		if (verbose && strcmp(argv[i], "-v")) {
			char *path = realpath(argv[i], NULL);
			
			if (path == NULL) {
				char *msg = malloc(128);
				if (strlen(argv[i]) > 80) {
					printf("filename too long\n");
					free(msg);
					free(trash_dir);
					exit(1);
				}
				
				strcpy(msg, "failed to open file ");
				strcat(msg, argv[i]);
				perror(msg);
				free(msg);
				free(trash_dir);
				exit(1);
			}

			printf("trashing file %s\n", path);
			free(path);
		}

		char *dest = malloc(strlen(argv[i]) + strlen(trash_dir) + 2);
		strcpy(dest, trash_dir);
		strcat(dest, argv[i]);
		
		rename(argv[i], dest);
	}
	
	free(trash_dir);
	
	
	return 0;
}
