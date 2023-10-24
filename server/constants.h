#define _CRT_SECURE_NO_WARNINGS
#pragma once
#ifndef CONST_H 
#define MYSIZE 100
#define BUFFER 1024
#define PORT 6379
#include <winsock2.h>
SOCKET server_socket, client_socket;
struct sockaddr_in server_addr, client_addr;
HANDLE mutex;
char* request[BUFFER];
char fileName[MYSIZE];
#endif 
