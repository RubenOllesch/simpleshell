#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <unistd.h>


bool
try_runbuiltin(char *args[])
{
	if (strcmp("exit", args[0]) == 0) {
		exit(EXIT_SUCCESS);
	} else if (strcmp("cd", args[0]) == 0) {
		chdir(args[1]);
	} else {
		return false;
	}

	return true;	// Was builtin command
}
