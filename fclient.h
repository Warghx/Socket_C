#include "common.h"

int hellorWorld(int sock, struct sockaddr_in server_addr);

int setaddrbyname(struct sockaddr_in *addr, char *host); 

int mapacheck(int sock, struct sockaddr_in server_addr);

int seientcheck(int sock, struct sockaddr_in server_addr);

int buyseient(int sock, struct sockaddr_in servidor);

int returnseient(int sock, struct sockaddr_in servidor);
