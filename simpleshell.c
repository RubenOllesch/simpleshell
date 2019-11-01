#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <unistd.h>


#define SHELL_INPUT_BUFSIZE	1024
#define SHELL_TKN_BUFSIZE	64

#define SHELL_ARG_DELIM		" \t\r"

void
die(const char *fmt, ...)
{
	va_list vl;
	va_start(vl, fmt);

	vfprintf(stderr, fmt, vl);

	va_end(vl);

	exit(EXIT_FAILURE);
}

void
print_prompt()
{
	printf("> ");
}

char*
read_line()
{
	int bufsize = SHELL_INPUT_BUFSIZE;
	int pos = 0;
	int c;
	char *buffer = malloc(bufsize * sizeof(char));
	
	if (!buffer)
		die("shell: allocation error\n");
	
	while (1) {
		// Read a character
		c = getchar();
		
		// If we hit EOF, replace it with a null character and return.
		if (c == EOF || c == '\n') {
			buffer[pos] = '\0';
			return buffer;
		} else {
			buffer[pos++] = c;
		}
		
		// If we have exceeded the buffer, reallocate.
		if (pos >= bufsize) {
			bufsize += SHELL_INPUT_BUFSIZE;
			buffer = realloc(buffer, bufsize * sizeof(char));
			if (!buffer)
				die("shell: allocation error\n");
		}
	}
}

char**
parse_line(char *line)
{
	int bufsize = SHELL_TKN_BUFSIZE;
	int pos = 0;
	char *tkn;
	char **tokens = malloc(bufsize * sizeof(char*));
	
	if (!tokens)
		die("shell: allocation error\n");
	
	tkn = strtok(line, SHELL_ARG_DELIM);

	while (tkn != NULL) {
		tokens[pos++] = tkn;

		if (pos >= bufsize) {
			bufsize += SHELL_TKN_BUFSIZE;
			tokens = realloc(tokens, bufsize * sizeof(char*));
			if (!tokens)
				die("shell: allocation error\n");
		}

		tkn = strtok(NULL, SHELL_ARG_DELIM);
	}

	tokens[pos] = NULL;
	return tokens;
}

int
exec_cmd(char *args[])
{
	execvp(args[0], args);
	return 1;
}


int
main(int argc, char *argv[])
{
	char *line;
	char **args;

	while(1) {
		print_prompt();
		line = read_line();
		args = parse_line(line);
		exec_cmd(args);
	}
}