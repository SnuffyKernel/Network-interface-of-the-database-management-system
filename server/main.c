#include "server/server.h"

int main() {
	server();
	while (true)
	{
		clientSocket();
	}
	getchar();
	return 0;
}