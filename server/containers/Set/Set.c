#include "Set.h";

Structure* createSet() {
    Structure* set = malloc(sizeof(Structure));
    MemoryError(set);
    for (int i = 0; i < MYSIZE; i++) {
        set->hashTable[i].value = NULL;
        set->hashTable[i].check = false;
    }

    return set;
}

int hash(const char* value) {
    int hashValue = 0;
    for (int i = 0; value[i] != '\0'; i++) {
        hashValue += value[i];
    }
    return hashValue % MYSIZE;
}

void addSet(Structure* set, const char* value, const bool output) {
    int index = hash(value);

    while (set->hashTable[index].check) {
        if (strcmp(set->hashTable[index].value, value) == 0) {
            close("The element is in a container", 1);
        }
        index = (index + 1) % MYSIZE;
    }

    set->hashTable[index].value = _strdup(value);
    set->hashTable[index].check = true;
    if (output) {
        printf("-> %s\n", set->hashTable[index].value);
        mySend(set->hashTable[index].value, NULL);
        writeFile(set, 0);
    }
}

void delSet(Structure* set, const char* value) {
    int index = hash(value);

    while (set->hashTable[index].check) {
        if (strcmp(set->hashTable[index].value, value) == 0) {

            free(set->hashTable[index].value);
            set->hashTable[index].check = false;
            printf("-> %s\n", value);
            mySend(value, NULL);
            writeFile(set, 0);
            return;
        }
        index = (index + 1) % MYSIZE;
    }

    close("This element is not found\n", 1);
}

void readSet(const Structure* set, const char* value) {
    int index = hash(value);

    while (set->hashTable[index].check) {
        if (strcmp(set->hashTable[index].value, value) == 0) {
            close("-> TRUE\n", 0);
            mySend("-> TRUE\n", NULL);
            return;
        }
        index = (index + 1) % MYSIZE;
    }

    close("-> FALSE\n", 0);
    mySend("-> FALSE\n", NULL);
    return;
}

void mainSet(char* command, char* value) {
    if (value[0] == '\0') close("Missing a word\n", 1);
    Structure* Set = createSet();
    char* fileSet = readFile(1, 1, 0);

    char* token = strtok(fileSet, " \t\n");
    while (token != NULL) {
        addSet(Set, token, 0);
        token = strtok(NULL, " \t\n");
    }

    if (strcmp(command, "SADD") == 0) {
        addSet(Set, value, 1);
    }
    else if (strcmp(command, "SREM") == 0) {
        delSet(Set, value);
    }
    else if (strcmp(command, "SISMEMBER") == 0) {
        readSet(Set, value);
    }
    else close("There is no such command\n", 1);

}