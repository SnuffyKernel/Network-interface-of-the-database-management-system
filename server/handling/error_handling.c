#include "error_handling.h"

void close(const char* text, bool code, SOCKET client_socket) {
	printf("%s\n", text);
	if (code) {
		printf("Session closed");
		char message[MYSIZE];
		sprintf_s(message, sizeof(message),"Session closed: %s", text);
		mySend(message, NULL, client_socket);
		getchar();
		_endthread();
		exit(code);
	}
	else return;
}

void MemoryError(const void* text) {
	if (text == NULL) {
		close("Memory allocation error", 1, client_socket);
	}
}

void FileError(FILE* file) {
	if (file == NULL) {
		perror("Failed to create the file");
		_endthread();
		exit(1);
	}
}