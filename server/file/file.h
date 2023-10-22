#pragma once
#ifndef FILE_H 
#include "../constants.h"
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "../file/text/data_utilities.h"
#include "../containers/Structure.h"
#include "../containers/Set/Set.h"
#include "../containers/Stack/Stack.h"
#include "../containers/Queue/Queue.h"

FILE* createFile(char* formatOpen);
char* readFile(const bool a, const bool code, const int typeContainer);
void writeFile(Structure* structure, const int typeContainer);
#endif 
