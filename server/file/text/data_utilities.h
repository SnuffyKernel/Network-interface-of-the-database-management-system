#pragma once
#ifndef DATA_H 
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include "../../constants.h"
#include "../../containers/Structure.h"
void reverseWordsOrder(char* str);
char* containerLine(char* text, int typeContainer);
char* TranslatStructToChar(const Structure* structure);
void serializeSet(const Structure* structure, char* serialized, int bufferSize);
void serializeHashTable(const Structure* structure, char* serialized, int bufferSize);
char* serializeStructure(const Structure* structure, const int typeContainer);
char* replaceText(char* text, const char* container, const int typeContainer);
#endif 
