#include "data_utilities.h"

char* TranslatStructToChar(const Structure* structure) {
	char* line = (char*)malloc(MYSIZE * sizeof(char));

	MemoryError(line);

	StructureElement* current = structure->head;
	int currentIndex = 0;
	line[currentIndex] = ' ';
	currentIndex++;
	while (current != NULL && currentIndex < MYSIZE - 1) {
		strncpy(line + currentIndex, current->value, MYSIZE - currentIndex - 1);

		currentIndex += strlen(current->value);

		if (current->next != NULL) {
			line[currentIndex] = ' ';
			currentIndex++;
		}

		current = current->next;
	}
	line[currentIndex++] = ' ';
	line[currentIndex++] = '|';
	line[currentIndex++] = '\0';
	return line;
}

void serializeSet(const Structure* structure, char* serialized, int bufferSize) {
	for (int i = 0; i < MYSIZE; i++) {
		if (structure->hashTable[i].check) {

			char temp[MYSIZE];
			snprintf(temp, sizeof(temp), " %s", structure->hashTable[i].value);

			if (strlen(serialized) + strlen(temp) >= bufferSize) {
				bufferSize *= 2;
				serialized = (char*)realloc(serialized, bufferSize * sizeof(char));
				MemoryError(serialized);
			}

			strcat(serialized, temp);
		}
	}
}

void serializeHashTable(const Structure* structure, char* serialized, int bufferSize) {
	for (int i = 0; i < MYSIZE; i++) {
		StructureElement* current = structure->table[i];
		while (current != NULL) {
			char temp[MYSIZE];
			snprintf(temp, sizeof(temp), " %s %s", current->key, current->value);

			if (strlen(serialized) + strlen(temp) >= bufferSize) {
				bufferSize *= 2;
				serialized = (char*)realloc(serialized, bufferSize * sizeof(char));
				MemoryError(serialized);
			}

			strcat(serialized, temp);

			current = current->next;
		}
	}
}

char* serializeStructure(const Structure* structure, const int typeContainer) {
	int bufferSize = BUFFER;
	char* serialized = (char*)malloc(bufferSize * sizeof(char));
	MemoryError(serialized);
	strcpy(serialized, "");

	if (!typeContainer) serializeSet(structure, serialized, bufferSize);
	else serializeHashTable(structure, serialized, bufferSize);

	strcat(serialized, " |");
	return serialized;
}