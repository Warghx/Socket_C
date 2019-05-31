#include "fclient.h"
#include <sys/socket.h>
#include "fclient.c"

int main(int argc, char *argv[]){
	
	int parametre; // variable per processar els parametres amb els que es crida l'aplicatiu
	int ctrl_host = 0; // variable de control d'especificacio del host per parametre
	int port = DEFAULT_PORT; // variable per al port inicialitzada al valor DEFAULT_PORT (veure common.h)
	char *host; // variable per copiar el nom del host des de l'optarg
	int opcio = 0; // variable de control del menu d'opcions
	int sock = socket(PF_INET,SOCK_DGRAM,0); //variable per emmagatzemar el resultat de la crida socket() per crear el socket del client


	// Processem els parametres obtinguts del prompt
	while((parametre = getopt(argc, argv, "p:h:")) != -1){
		switch((char) parametre){
			case 'p':
				// Donat que hem inicialitzat amb valor DEFAULT_PORT (veure common.h) 
				// la variable port, aquest codi nomes canvia el valor de port en cas
				// que haguem especificat un port diferent amb la opcio -p
				port = atoi(optarg);
				break;
			case 'h':
				// Capturem el nom del host on es troba el servidor (ex: ccd-dc10.uab.es)
				// Creem dinamicament espai per emmagatzemar la cadena de text que conte el host
				// en la variable host. L'espai requerit es la longitud de la cadena (obtinguda
				// amb strlen, mes 1, donat que totes les cadenes de text acabem amb el caracter '\0'
				// que no es tingut en compte per strlen, ni es mostra per pantalla al fer printf
				host = (char*) malloc(sizeof(char)*strlen(optarg)+1);
				// Un cop creat l'espai, podem copiar la cadena
				strcpy(host, optarg);
				ctrl_host = 1;
				break;
			default:
				printf("Parametre %c desconegut\n\n", (char) parametre);
				return -1;
		}
	}

	// Comprovem que s'hagi introduit un host. En cas contrari, terminem l'execucio de
	// l'aplicatiu	
	if(!ctrl_host){
		perror("No s'ha especificat el nom del servidor\n\n");
		return -1;
	}

	//CREACIO DEL
	struct sockaddr_in servidor;
	bzero(&servidor,sizeof(servidor));
	servidor.sin_family = AF_INET;
	servidor.sin_port = htons(port);

	setaddrbyname(&servidor,host);

	bind ( sock, (struct sockaddr *)&servidor, sizeof (servidor));


	while(opcio!=9){
		// Mostrem un menu perque l'usuari pugui triar quina opcio fer
		printf("\nAplicatiu per la compra d'entrades\n");
		printf("  0. Hola mon!\n");
		//printf("  1. Consulta butaca\n");
		printf("  1. Mostra mapa de seients\n");
		printf("  2. Consulta seient\n");
		printf("  3. Comprar entrada\n");
		printf("  4. Devolucio entrada\n");
		printf("  5. Comprar varies entrades\n");
		printf("  6. Devolucio varies entrades\n");
		printf("  9. Sortir\n\n");
		printf("Escolliu una opcio: ");
		// Obtenim la opcio introduida per l'usuari
		scanf("%d",&opcio);
		printf("\n\n");
		switch(opcio){
	
			//HELLO WORLD
			case 0:
				hellorWorld(sock,servidor);
			break;

			//MOSTRA MAPA SEIENT
			case 1: 
				mapacheck(sock,servidor);
			break;
				

			//CONSULTA DE UNA BUTACA//ENVIA FILA I COLUMNA I RECIBE PRECIO
			case 2:
				seientcheck(sock,servidor);
			break;

			
			///////////////////////////////////////////////////////////////
			//COMPRA D'UNA ENTRADA/////////
			case 3:
				buyseient(sock,servidor);
			break;
			
			//DEVOLUCION ENTRADA
			case 4:
				returnseient(sock,servidor);
			break;

			/*
			////COMPRAR VARIOS////
			case 5:
			do{
			bzero(buffer,sizeof(buffer));
			while(fila==0){
			printf("Introduce Nº de FILA: ");
			scanf("%hd",&fila);}
			while(columna==0){
			printf("Introduce Nº de COLUMNA: ");
			scanf("%hd",&columna);}
			printf("INTRODUCIDO f:%hd, c:%hd \n\n\n",fila,columna);
			printf("DESEA SEGUIR COMPRANDO(s/n): ");
			scanf("%c",&control);}
			stshort(8,buffer);			
			
			stshort(fila,buffer+x);
			stshort(columna,buffer+x+2);
			x=x+2;
			}while(control=='s');
			
			sendto (sock, buffer, sizeof(buffer), 0, (struct sockaddr *)&servidor, sizeof(servidor));
			fila=0;
			columna=0;
			
			i = recvfrom (sock, buffer, tamany_maxim, 0, (struct sockaddr *)&dir, &longdir);
			
			
			break;*/
		}
	}
	// Donat que ja no el farem servir mes, tanquem el socket
	//close(sock);

	// Sortim de l'aplicatiu
	return 0;

}
