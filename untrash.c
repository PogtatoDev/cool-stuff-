#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <unistd.h>

int main(int argc, char **argv) {
	char *trash_dirname = (char *)malloc(129 + strlen("/.trash/"));
	if (getenv("HOME") == NULL) printf("???\n");

	if (strlen(getenv("HOME")) > 128) {
		printf("username too long\n");
		free(trash_dirname);
		exit(1);
	}

	strcpy(trash_dirname, getenv("HOME"));
	strcat(trash_dirname, "/.trash/");

	if (argc == 2 && !strcmp(argv[1], "--list")) {
		DIR *trash_dir = opendir((const char *)trash_dirname);
		if (!trash_dir)
			perror("could not open trash folder");

		struct dirent *trash_file;

		while ((trash_file = readdir(trash_dir)) != NULL) {
			if (strcmp(trash_file->d_name, ".") != 0 && strcmp(trash_file->d_name, "..") != 0)
				printf("%s\n", trash_file->d_name);
		}

		free(trash_dirname);
		return 0;
	} else {
		for (int32_t i = 1; i < argc; i++) {
			

		}
	}
	free(trash_dirname);
	return 0;
}
