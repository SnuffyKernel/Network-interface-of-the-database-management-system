#include "server.h"

SOCKET server_socket;
struct sockaddr_in server_addr, client_addr;
char* request[BUFFER];
int addr_len = sizeof(client_addr);

void clientSocket() {
    SOCKET client_socket = accept(server_socket, (struct sockaddr*)&client_addr, &addr_len);
    if (client_socket == INVALID_SOCKET) {
        close("Failed to accept client connection", 1);
    }
    _beginthread(serverRequestParsing, 0, client_socket);
}

void mySend(char* value, char* key, SOCKET client_socket) {
    char SEND[MYSIZE];
    if (key == NULL && value == NULL) {
        closesocket(client_socket);
        closesocket(server_socket);
        WSACleanup();
        _endthread();
    }
    else if (key == NULL) {
        sprintf(SEND, "-> %s\n", value);
        send(client_socket, SEND, sizeof(SEND), 0);
    }
    else {
        sprintf(SEND, "-> %s %s\n", key, value);
        send(client_socket, SEND, sizeof(SEND), 0);
    }
}

char* interactionServer(SOCKET client_socket) {
    memset(request, 0, sizeof(request));
    recv(client_socket, request, sizeof(request), 0);
    if (strcmp(request, "exit\n") == 0) {
        printf("Session closed\n");
        return 0;
    }
    printf("Received: %s", request);
    return request;
}

void serverRequestParsing(SOCKET client_socket) {
    while (true)
    {
        char* buffer = interactionServer(client_socket);
        char* args[20];
        int argc;

        char* token = strtok((char*)buffer, " \n");
        argc = 0;

        while (token != NULL) {
            char* newline = strchr(token, '\n');
            if (newline != NULL) {
                *newline = '\0';
            }
            args[argc] = token;
            argc++;
            token = strtok(NULL, " ");
        }
        flags(argc, args, client_socket);
    }
}

void server() {
    WSADATA wsa;

    if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0) {
        close("Failed to initialize Winsock", 1);
    }

    server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket == INVALID_SOCKET) {
        close("Failed to create socket", 1);
    }

    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(PORT);

    if (bind(server_socket, (struct sockaddr*)&server_addr, sizeof(server_addr)) == SOCKET_ERROR) {
        close("Failed to bind", 1);
    }

    if (listen(server_socket, 5) == SOCKET_ERROR) {
        close("Failed to listen", 1);
    }

    printf("Server listening on port %d...\n", PORT);
}