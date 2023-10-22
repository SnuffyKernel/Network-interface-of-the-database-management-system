#pragma once
#ifndef STACK_H
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include "../Structure.h"

Structure* createStack();
void addStack(Structure* stack, char* value, const bool output);
void delStack(Structure* stack);
void mainStack(char* command, char* value);

#endif
