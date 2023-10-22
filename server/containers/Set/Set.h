#pragma once
#ifndef SET_H
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include "../Structure.h"

Structure* createSet();
void addSet(Structure* set, const char* value, const bool output);
void delSet(Structure* set, char* value);
void readSet(Structure* set, char* value);
void mainSet(char* command, char* value);

#endif 
