#pragma once
#ifndef HASHTABLE_H
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include "../Structure.h"

Structure* createHashTable();
void addHashTable(Structure* structure, const int key, const char* value, const bool output);
void delHashTable(Structure* set, char* value);
void readHashTable(Structure* set, char* value);
void mainHashTable(char* command, char* key, char* value);

#endif
