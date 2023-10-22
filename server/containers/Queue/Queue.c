#include "Queue.h";

Structure* createQueue() {
    Structure* queue = malloc(sizeof(Structure));
    MemoryError(queue);
    queue->head = NULL;
    return queue;
}

void addQueue(Structure* queue, char* value, const bool output) {
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
        mySend(value, NULL);
        writeFile(queue, 2);
    }
}

void delQueue(Structure* queue) {
    if (queue == NULL || queue->head == NULL) {
        close("The queue is empty or invalid", 1);
    }

    StructureElement* removed = queue->head;
    if (queue->head == queue->tail) {
        queue->head = queue->tail = NULL;
    }
    else {
        queue->head = queue->head->next;
    }

    printf("-> %s\n", removed->value);
    mySend(removed->value, NULL);
    writeFile(queue, 2);
}

void mainQueue(char* command, char* value) {
    Structure* Queue = createQueue();
    char* fileSet = readFile(1, 0, 2);

    char* token = strtok(fileSet, " \t\n");
    while (token != NULL) {
        addQueue(Queue, token, 0);
        token = strtok(NULL, " \t\n");
    }

    if (strcmp(command, "QPUSH") == 0) {
        if (value[0] == '\0') close("Missing a word\n", 1);
        addQueue(Queue, value, 1);
    }
    else if (strcmp(command, "QPOP") == 0) {
        delQueue(Queue);
    }
    else close("There is no such command\n", 1);

}