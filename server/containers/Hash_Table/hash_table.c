#include "hash_table.h";

Structure* createHashTable() {
	Structure* hashTable = malloc(sizeof(Structure));
	MemoryError(hashTable);
	for (int i = 0; i < MYSIZE; i++) {
		hashTable->table[i] = NULL;
	}

	return hashTable;
}

void addHashTable(Structure* structure, SOCKET client_socket, const int key, const char* value, const bool output) {
	if (key == NULL || value == NULL) return;
	int index = hash(key);

	StructureElement* current = structure->table[index];
	while (current != NULL) {
		if (strcmp(current->key, key) == 0) {
			close("Not a unique key", 1, client_socket);
		}
		current = current->next;
	}

	StructureElement* newElement = malloc(sizeof(StructureElement));
	MemoryError(newElement);

	newElement->key = _strdup(key);
	newElement->value = _strdup(value);
	newElement->next = structure->table[index];

	structure->table[index] = newElement;
	if (output) {
		printf("-> %s %s\n", key, value);
		mySend(value, key, client_socket);
		writeFile(structure, 3, client_socket);
	}
}

void delHashTable(Structure* hashTable, SOCKET client_socket, const char* key) {
	int index = hash(key);

	StructureElement* current = hashTable->table[index];
	StructureElement* prev = NULL;

	while (current != NULL) {
		if (strcmp(current->key, key) == 0) {
			if (prev != NULL) {
				prev->next = current->next;
			}
			else {
				hashTable->table[index] = current->next;
			}
			printf("-> %s\n", current->value);
			mySend(current->value, key, client_socket);
			free(current->key);
			free(current->value);
			free(current);
			writeFile(hashTable, 3, client_socket);
			return;
		}
		prev = current;
		current = current->next;
	}

	close("This element is not found\n", 1, client_socket);
}

void readHashTable(const Structure* hashTable, SOCKET client_socket, const char* key) {
	int index = hash(key);

	StructureElement* current = hashTable->table[index];

	while (current != NULL) {
		if (strcmp(current->key, key) == 0) {
			close("-> TRUE\n", 0);
			mySend("-> TRUE\n", NULL, client_socket);
			return;
		}
		current = current->next;
	}

	close("-> FALSE\n", 0);
	mySend("-> FALSE\n", NULL, client_socket);
	return;
}

void mainHashTable(char* command, char* key, char* value, SOCKET client_socket) {
	Structure* HashTable = createHashTable();
	char* file = readFile(1, 1, 3, client_socket);

	char* token = strtok(file, " \t\n");
	while (token != NULL) {
		char* VALUE = token;
		token = strtok(NULL, " \t\n");
		char* KEY = token;
		addHashTable(HashTable, client_socket, KEY, VALUE, 0);
		token = strtok(NULL, " \t\n");
	}

	if (strcmp(command, "HSET") == 0) {
		if (value[0] == '\0') close("Missing a key or value\n", 1, client_socket);
		addHashTable(HashTable, client_socket, key, value, 1);
	}
	else if (strcmp(command, "HDEL") == 0) {
		if (key[0] == '\0') key = value;
		delHashTable(HashTable, client_socket, key);
	}
	else if (strcmp(command, "HGET") == 0) {
		if (key[0] == '\0') key = value;
		readHashTable(HashTable, client_socket, key);
	}
	else close("There is no such command\n", 1, client_socket);
}