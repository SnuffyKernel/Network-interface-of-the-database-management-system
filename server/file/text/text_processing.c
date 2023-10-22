#include "data_utilities.h"

void reverseWordsOrder(char* str) {
	char* words[MYSIZE];
	int wordCount = 0;

	char* token = strtok(str, " \t\n");
	while (token != NULL) {
		words[wordCount++] = token;
		token = strtok(NULL, " \t\n");
	}

	for (int i = 0, j = wordCount - 1; i < j; i++, j--) {
		char* temp = words[i];
		words[i] = words[j];
		words[j] = temp;
	}

	char reversedStr[BUFFER] = "";
	for (int i = 0; i < wordCount; i++) {
		strcat(reversedStr, words[i]);
		strcat(reversedStr, " ");
	}

	strcpy(str, reversedStr);
}

char* containerLine(char* text, int typeContainer) {
	char line[MYSIZE];
	for (int i = 0, j = 0, count = -1; text[i] != '\0'; i++) {
		if (text[i] == '|') {
			count++;
			continue;
		}
		if (count == typeContainer) {
			line[j] = text[i];
			if (text[i + 1] == '|') {
				line[j + 1] = '\0';
				break;
			}
			j++;
		}
	}
	return _strdup(line);
}

char* replaceText(char* text, const char* container, const int typeContainer) {
	char* start = text;
	char* end = NULL;
	int count = -1;

	while (*start) {
		if (*start == '|') {
			count++;
			if (count == typeContainer) {
				start++;
				end = strchr(start, '|');
				break;
			}
		}
		start++;
	}

	if (end != NULL) {
		size_t containerLength = end - start;

		size_t newLength = strlen(text) - containerLength + strlen(container) + 1;

		char* result = (char*)malloc(newLength);
		MemoryError(result);

		strncpy(result, text, start - text);
		result[start - text] = '\0';
		strcat(result, container);
		strcat(result, end + 1);

		return result;
	}

	return _strdup(text);
}