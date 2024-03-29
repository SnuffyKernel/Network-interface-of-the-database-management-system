#include "file.h"

FILE* createFile(char* formatOpen, SOCKET client_socket) {
	WaitForSingleObject(mutex, INFINITE);
	FILE* file = fopen(fileName, formatOpen);
	if (file == NULL) {
		char userResponse = '\0';
		printf("File not found. Do you want to create a file y/n: ");
		mySend("File not found. Do you want to create a file y/n: ", NULL, client_socket);
		memset(request, 0, sizeof(request));
		recv(client_socket, request, sizeof(request), 0);
		printf(" %s\n", request);

		if (strchr(request, 'y') != NULL || strchr(request, 'Y') != NULL) {
			file = fopen(fileName, "w");
			FileError(file);
			fprintf(file, "|  |  |  |  |");
			fclose(file);
			file = fopen(fileName, formatOpen);
		}
		else exit(1);
	}
	ReleaseMutex(mutex);
	return file;
}

char* readFile(const bool readAllFile, const bool code, const int typeContainer, SOCKET client_socket) {
	FILE* file = createFile("rb+", client_socket);

	fseek(file, 0, SEEK_END);
	long file_size = ftell(file);
	fseek(file, 0, SEEK_SET);

	char* text = (char*)malloc(file_size + 1);
	MemoryError(text);

	fread(text, 1, file_size, file);
	text[file_size] = '\0';
	if (readAllFile) {
		text = containerLine(text, typeContainer);
		if (code) reverseWordsOrder(text);
	}
	fclose(file);
	return text;

}

void writeFile(Structure* structure, const int typeContainer, SOCKET client_socket) {
	WaitForSingleObject(mutex, INFINITE);
	char* text = readFile(0, 0, typeContainer, client_socket);
	char* line;
	if (!typeContainer || typeContainer == 3) {
		line = serializeStructure(structure, typeContainer);
	}
	else {
		line = TranslatStructToChar(structure);
	}
	text = replaceText(text, line, typeContainer);

	FILE* file = createFile("w", client_socket);

	fprintf(file, "%s", text);
	fclose(file);
	ReleaseMutex(mutex);
	//getchar();
	//exit(0);
}