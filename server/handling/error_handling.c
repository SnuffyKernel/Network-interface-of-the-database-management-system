#include "error_handling.h"

void close(const char* text, bool code) {
	printf("%s\n", text);
	if (code) {
		printf("Session closed");
		char message[MYSIZE];
		sprintf_s(message, sizeof(message),"Session closed: %s", text);
		mySend(message, NULL);
		getchar();
		exit(code);
	}
	else return;
}

void MemoryError(const void* text) {
	if (text == NULL) {
		close("Memory allocation error", 1);
	}
}

void FileError(FILE* file) {
	if (file == NULL) {
		perror("Failed to create the file");
		exit(1);
	}
}