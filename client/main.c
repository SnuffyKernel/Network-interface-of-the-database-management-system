#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <stdio.h>
#include <winsock2.h>

void main() {
    WSADATA wsa;
    SOCKET client_socket;
    struct sockaddr_in server_addr;
    char command[1024];
    char response[1024];

    if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0) {
        perror("Failed to initialize Winsock");
        return 1;
    }

    client_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (client_socket == INVALID_SOCKET) {
        perror("Failed to create socket");
        return 1;
    }

    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    server_addr.sin_port = htons(6379);

    if (connect(client_socket, (struct sockaddr*)&server_addr, sizeof(server_addr)) == SOCKET_ERROR) {
        perror("Failed to connect to the server");
        return 1;
    }

    while (1) {
        printf("Enter a command (or 'exit' to quit): ");
        fgets(command, sizeof(command), stdin);

        if (strcmp(command, "exit\n") == 0) {
            send(client_socket, command, strlen(command), 0);
            break;
        }

        send(client_socket, command, strlen(command), 0);
        while (1) {
            memset(response, 0, sizeof(response));
            int bytes_received = recv(client_socket, response, sizeof(response), 0);
            if (bytes_received > 0) {
                printf("Server response: %s", response);
                break;
            }
            else if (bytes_received == 0) {
                printf("Server disconnected.\n");
                closesocket(client_socket);
                WSACleanup();
                return;
            }
            else {
                perror("Failed to receive response from the server");
                break; 
            }
        }
    }

    closesocket(client_socket);
    WSACleanup();
}