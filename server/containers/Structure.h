#pragma once
#ifndef STRUCTURE_H 
#include <stdbool.h>
#include "../constants.h"
typedef struct StructureElement {
    char* key;
    char* value;
    bool check;
    struct StructureElement* next;
} StructureElement;

typedef struct {
    StructureElement* table[MYSIZE];
    StructureElement hashTable[MYSIZE];
    StructureElement* head;
    StructureElement* tail;
} Structure;
#endif 
