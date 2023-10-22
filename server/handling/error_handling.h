#pragma once
#ifndef ERROR_H 
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "../constants.h"
void close(char* text, bool code);
void MemoryError(const void* text);
#endif 
