#pragma once
#ifndef SERVER_H
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include "../constants.h"
#include <stdbool.h>
#include <stdio.h>
#include <winsock2.h>
#include <process.h>
void clientSocket();
void mySend(char* value, char* key);
char* interactionServer();
void serverRequestParsing();
void server();
#endif 