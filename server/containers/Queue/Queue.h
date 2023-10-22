#define _CRT_SECURE_NO_WARNINGS
#pragma once
#ifndef QUEUE_H
#include <stdbool.h>
#include <stdio.h>
#include "../Structure.h"

Structure* createQueue();
void addQueue(Structure* queue, char* value, const bool output);
void delQueue(Structure* queue);
void mainQueue(char* command, char* value);

#endif
