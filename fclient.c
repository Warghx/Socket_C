#include "fclient.h"
#include "common.c"

// Funcio que envia un missatge amb el codi d'operacio del Hello World
int hellorWorld(int sock, struct sockaddr_in servidor){
	int res = 0; // Variable per emmagatzemar el resultat del sendto
	int size = 0; // Variable per guardar el tamany de les dades a enviar
	char buffer[512]; // Buffer de 512 bytes (1 char = 1 byte) per emmagatzemar el missatge que s'enviara al servidor
	int cap=0;
	struct sockaddr_in dir;

		 bzero(buffer, sizeof(buffer));
		 stshort(1,buffer);
		 sendto (sock, buffer, sizeof(buffer), 0, (struct sockaddr *)&servidor, sizeof(servidor));
		 bzero(buffer, sizeof(buffer));
		 res = recvfrom (sock, buffer, sizeof(buffer), 0, (struct sockaddr *)&dir, sizeof(&dir)); 
		 cap=ldshort(buffer);
		 printf(" Codi:  %d Buffer: %s \n", cap, buffer+2);
		 bzero(buffer,sizeof(buffer));
	
	return 0;
}

int mapacheck(int sock, struct sockaddr_in servidor){
	
	int res = 0;
	char buffer[1024]; 
	int cap=0;
	struct sockaddr_in dir;

	bzero(buffer, sizeof(buffer));
	stshort(3,buffer);
 	sendto(sock, buffer, sizeof(buffer), 0, (struct sockaddr *)&servidor, sizeof(servidor));
	bzero(buffer, sizeof(buffer));
	res = recvfrom (sock, buffer, sizeof(buffer), 0, (struct sockaddr *)&dir, sizeof(&dir)); 
	cap=ldshort(buffer);
	printf("\n");
	printMap(buffer+2,100);
	printf(" Codi:  %d\n", cap);
	bzero(buffer,sizeof(buffer));
}

int seientcheck(int sock, struct sockaddr_in servidor){ 
	int res = 0;
	char buffer[512]; 
	int cap=0,cap2=0;
	short fila=0;
	short columna=0;
	struct sockaddr_in dir;
	
	bzero(buffer,sizeof(buffer));
		while(fila==0){
			printf("Introduce Nº de FILA: ");
			scanf("%hd",&fila);}

		while(columna==0){
			printf("Introduce Nº de COLUMNA: ");
			scanf("%hd",&columna);}

		printf("INTRODUCIDO f:%hd, c:%hd \n\n\n",fila,columna);
		
		stshort(5,buffer);			
		
		stshort(fila,buffer+2);
		stshort(columna,buffer+4);
		
		sendto (sock, buffer, sizeof(buffer), 0, (struct sockaddr *)&servidor, sizeof(servidor));
		fila=0;
		columna=0;

		res = recvfrom (sock, buffer, sizeof(buffer), 0, (struct sockaddr *)&dir, sizeof(&dir));
		cap=ldshort(buffer);
		cap2=ldshort(buffer+2);
		if(cap==14){
		
		switch(cap2){
		
			case 1:
			printf("CODI: %d\n",cap);
			printf("CODI ERROR(%d): SEIENT INEXISTENT\n",cap2);
			break;

			case 2:
			printf("CODI: %d\n",cap);
			printf("CODI ERROR(%d): SEIENT NO DISPONIBLE\n",cap2);
			break;

			case 3:
			printf("CODI: %d\n",cap);
			printf("CODI ERROR(%d): SEIENT NO ESTAVA OCUPAT\n",cap2);
			break;
		}

		}else{
		printf("Codi:  %d \n", cap);
		printf("SEIENT: %hd \n",cap2);
		
		}

}

int buyseient(int sock, struct sockaddr_in servidor){
	
	int res = 0;
	char buffer[512]; 
	int cap=0, cap2=0;
	short fila=0;
	short columna=0;
	struct sockaddr_in dir;

	bzero(buffer,sizeof(buffer));
			while(fila==0){
			printf("Introduce Nº de FILA: ");
			scanf("%hd",&fila);}
			while(columna==0){
			printf("Introduce Nº de COLUMNA: ");
			scanf("%hd",&columna);}
			printf("INTRODUCIDO f:%hd, c:%hd \n\n\n",fila,columna);
			
			stshort(7,buffer);			
			
			stshort(fila,buffer+2);
			stshort(columna,buffer+4);
			
			sendto (sock, buffer, sizeof(buffer), 0, (struct sockaddr *)&servidor, sizeof(servidor));
			fila=0;
			columna=0;

			res = recvfrom (sock, buffer, sizeof(buffer), 0, (struct sockaddr *)&dir, sizeof(&dir));
			cap=ldshort(buffer);
			cap2=ldshort(buffer+2);
			if(cap==14){
			
			switch(cap2){
			
				case 1:
				printf("CODI: %d\n",cap);
				printf("CODI ERROR(%d): SEIENT INEXISTENT\n",cap2);
				break;

				case 2:
				printf("CODI: %d\n",cap);
				printf("CODI ERROR(%d): SEIENT NO DISPONIBLE\n",cap2);
				break;

				case 3:
				printf("CODI: %d\n",cap);
				printf("CODI ERROR(%d): SEIENT NO ESTAVA OCUPAT\n",cap2);
				break;
			}

			}else{
			printf("Codi:  %d \n", cap);
			//printf("Preu: %hd \n", cap2);
			printf("%s\n",buffer+2);
			
			}
}


int returnseient(int sock, struct sockaddr_in servidor){
	int res = 0;
	char buffer[512]; 
	int cap=0, cap2=0;
	short fila=0;
	short columna=0;
	struct sockaddr_in dir;

	bzero(buffer,sizeof(buffer));
			while(fila==0){
			printf("Introduce Nº de FILA: ");
			scanf("%hd",&fila);}
			while(columna==0){
			printf("Introduce Nº de COLUMNA: ");
			scanf("%hd",&columna);}
			printf("INTRODUCIDO f:%hd, c:%hd \n\n\n",fila,columna);
			
			stshort(10,buffer);			
			
			stshort(fila,buffer+2);
			stshort(columna,buffer+4);
			
			sendto (sock, buffer, sizeof(buffer), 0, (struct sockaddr *)&servidor, sizeof(servidor));
			fila=0;
			columna=0;

			res = recvfrom (sock, buffer, sizeof(buffer), 0, (struct sockaddr *)&dir, sizeof(&dir));
			cap=ldshort(buffer);
			cap2=ldshort(buffer+2);
			if(cap==14){
			
			switch(cap2){
			
				case 1:
				printf("CODI: %d\n",cap);
				printf("CODI ERROR(%d): SEIENT INEXISTENT\n",cap2);
				break;

				case 2:
				printf("CODI: %d\n",cap);
				printf("CODI ERROR(%d): SEIENT NO DISPONIBLE\n",cap2);
				break;

				case 3:
				printf("CODI: %d\n",cap);
				printf("CODI ERROR(%d): SEIENT NO ESTAVA OCUPAT\n",cap2);
				break;
			}

			}else{
			printf("Codi:  %d \n", cap);
			//printf("Preu: %hd \n", cap2);
			printf("%s\n",buffer+2);
			
			}	

}


/** 
* Function that sets the field addr->sin_addr.s_addr from a host name 
* address. 
* @param addr struct where to set the address. 
* @param host the host name to be converted 
* @return -1 if there has been a problem during the conversion process. 
*/ 
int setaddrbyname(struct sockaddr_in *addr, char *host) 
{ 
struct addrinfo hints, *res; 
int status; 

memset(&hints, 0, sizeof(struct addrinfo)); 
hints.ai_family = AF_INET; 
hints.ai_socktype = SOCK_DGRAM; 

if ((status = getaddrinfo(host, NULL, &hints, &res)) != 0) { 
fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(status)); 
return -1; 
} 

addr->sin_addr.s_addr = ((struct sockaddr_in *)res->ai_addr)->sin_addr.s_addr; 

freeaddrinfo(res); 

return 0; 
} 

