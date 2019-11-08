#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>


void
builtin_exit(char *args[])
{
	if (args[1] == NULL) {
		exit(EXIT_SUCCESS);
	} else {
		printf("exit: too many arguments\n");
	}
}


void
builtin_cd(char *args[])
{
	if (args[1] == NULL) {
		if (chdir(getenv("HOME")))
			printf("cd: %s\n", strerror(errno));
	} else if (args[2] == NULL) {
		if (chdir(args[1]))
			printf("cd: %s\n", strerror(errno));
	} else {
		printf("cd: too many arguments\n");
	}
}


bool
try_runbuiltin(char *args[])
{
	if (strcmp("exit", args[0]) == 0) {
		builtin_exit(args);
	} else if (strcmp("cd", args[0]) == 0) {
		builtin_cd(args);
	} else {
		return false;
	}

	return true;	// Was builtin command
}
