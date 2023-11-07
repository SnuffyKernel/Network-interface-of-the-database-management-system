#include "server/server.h"
#include "constants.h"

int main() {
	mutex = CreateMutex(NULL, FALSE, NULL);
	server();
	while (true)
	{
		clientSocket();
	}
	getchar();
	return 0;
}