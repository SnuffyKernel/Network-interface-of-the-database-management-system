#pragma once
#ifndef CLI_H 
#include "../constants.h"
#include "../handling/error_handling.h"
#include <stdio.h>
void parsing(char* request, char* command, char* value, char* key);
void flags(int argc, char* argv[]);
#endif 
