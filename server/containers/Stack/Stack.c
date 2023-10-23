#include "Stack.h"

Structure* createStack() {
    Structure* stack = malloc(sizeof(Structure));
    MemoryError(stack);
    stack->head = NULL;
    return stack;
}

void addStack(Structure* stack, SOCKET client_socket, char* value, const bool output) {
    StructureElement* newElement = (StructureElement*)malloc(sizeof(StructureElement));
    MemoryError(newElement);
    newElement->value = _strdup(value);
    newElement->next = stack->head;
    stack->head = newElement;

    if (output) {
        printf("-> %s\n", newElement->value);
        mySend(newElement->value, NULL, client_socket);
        writeFile(stack, 1, client_socket);
    }
}

void delStack(Structure* stack, SOCKET client_socket) {
    if (stack == NULL || stack->head == NULL) {
        close("The stack is empty or invalid", 1, client_socket);
    }

    StructureElement* removed = stack->head;
    stack->head = stack->head->next;

    printf("-> %s\n", removed->value);
    mySend(removed->value, NULL, client_socket);
    writeFile(stack, 1, client_socket);
}

void mainStack(char* command, char* value, SOCKET client_socket) {
    Structure* Stack = createStack();
    char* fileStack = readFile(1, 1, 1, client_socket);
    char* token = strtok(fileStack, " \t\n");
    while (token != NULL) {
        addStack(Stack, client_socket, token, 0);
        token = strtok(NULL, " \t\n");
    }

	if (strcmp(command, "SPUSH") == 0) {
        if (value[0] == '\0') close("Missing a word\n", 1, client_socket);
		addStack(Stack, client_socket, value, 1);
	}
	else if (strcmp(command, "SPOP") == 0) {
		delStack(Stack, client_socket);
	}
	else {
		close("There is no such command\n", 1, client_socket);
	}
}