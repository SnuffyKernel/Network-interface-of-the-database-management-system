#include "server/server.h"

int main() {
	server();
	while (true)
	{
		serverRequestParsing();
	}
	getchar();
	return 0;
}