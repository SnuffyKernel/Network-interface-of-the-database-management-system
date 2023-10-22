#include "cli.h"

void flags(int argc, char* argv[]) {
	int i = 0;
	if (strcmp(argv[i], "--file") == 0) {
		if (i + 1 < argc) {
			strcpy(fileName, argv[i + 1]);
			if (strstr(fileName, ".data") == NULL) {
				close("Validation error: The file must have the \".data\" format\n", 1);
			}
			i += 2;
		}
		else {
			close("Missing file name after --file\n", 1);
		}
	}
	else {
		close("flag omitted --file\n", 1);
	}

	if (i + 1 <= argc && strcmp(argv[i], "--query") == 0) {
		if (fileName != NULL) {
			if (i + 1 < argc) {
				char* command[MYSIZE];
				char* value[MYSIZE];
				char* key[MYSIZE];
				key[0] = '\0';
				strcpy(command, argv[i + 1]);
				if (argc == 6) {
					if (i + 2 >= argc || i + 3 >= argc) close("Invalid request\n", 1);
					strcpy(key, argv[i + 2]);
					strcpy(value, argv[i + 3]);
				}
				else {
					if (i + 2 >= argc) close("Invalid request\n", 1);
					strcpy(value, argv[i + 2]);
				}
				if (strcmp(command, "SADD") == 0 || strcmp(command, "SREM") == 0 || strcmp(command, "SISMEMBER") == 0) mainSet(command, value);
				else if (strcmp(command, "SPUSH") == 0 || strcmp(command, "SPOP") == 0) mainStack(command, value);
				else if (strcmp(command, "QPUSH") == 0 || strcmp(command, "QPOP") == 0) mainQueue(command, value);
				else if (strcmp(command, "HSET") == 0 || strcmp(command, "HDEL") == 0 || strcmp(command, "HGET") == 0) mainHashTable(command, key, value);
				else {
					close("There is no such command\n", 1);
				}
			}
			else {
				close("Invalid request\n", 1);
			}
			i += 2;
		}
		else {
			close("File name not specified\nPlease enter --file name.data\n", 1);
		}
	}

	else {
		close("Missing flag --query", 1);
	}

}