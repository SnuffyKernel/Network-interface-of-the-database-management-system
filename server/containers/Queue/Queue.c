#include "Queue.h";

Structure* createQueue() {
    Structure* queue = malloc(sizeof(Structure));
    MemoryError(queue);
    queue->head = NULL;
    return queue;
}

void addQueue(Structure* queue, SOCKET client_socket, char* value, const bool output) {
    StructureElement* newElement = (StructureElement*)malloc(sizeof(StructureElement));
    MemoryError(newElement);

    newElement->value = _strdup(value);
    newElement->next = NULL;

    if (queue->head == NULL) {
        queue->head = queue->tail = newElement;
    }
    else {
        queue->tail->next = newElement;
        queue->tail = newElement;
    }

    if (output) {
        printf("-> %s\n", value);
        mySend(value, NULL, client_socket);
        writeFile(queue, 2, client_socket);
    }
}

void delQueue(Structure* queue, SOCKET client_socket) {
    if (queue == NULL || queue->head == NULL) {
        close("The queue is empty or invalid", 1, client_socket);
    }

    StructureElement* removed = queue->head;
    if (queue->head == queue->tail) {
        queue->head = queue->tail = NULL;
    }
    else {
        queue->head = queue->head->next;
    }

    printf("-> %s\n", removed->value);
    mySend(removed->value, NULL, client_socket);
    writeFile(queue, 2, client_socket);
}

void mainQueue(char* command, char* value, SOCKET client_socket) {
    Structure* Queue = createQueue();
    char* fileSet = readFile(1, 0, 2, client_socket);

    char* token = strtok(fileSet, " \t\n");
    while (token != NULL) {
        addQueue(Queue, client_socket, token, 0);
        token = strtok(NULL, " \t\n");
    }

    if (strcmp(command, "QPUSH") == 0) {
        if (value[0] == '\0') close("Missing a word\n", 1);
        addQueue(Queue, client_socket, value, 1);
    }
    else if (strcmp(command, "QPOP") == 0) {
        delQueue(Queue, client_socket);
    }
    else close("There is no such command\n", 1);

}