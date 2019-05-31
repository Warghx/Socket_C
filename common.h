/***************************************************************************
 *            common.h
 *
 *  Fri Oct  1 16:04:36 2011
 *  Copyright  2011  mc
 *  <mc@<host>>
 ****************************************************************************/

#include <unistd.h> //per tipus com el socklen_t
#include <netdb.h> //pel gethostbyname
#include <errno.h> //per gestionar errors
#include <sys/types.h> //per tipus com el uint
#include <netinet/in.h> //pel INADDR_ANY
#include <sys/socket.h> //per la creació de sockets

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

// Macros per afegir i extreure el codi d'operacio d'un missatge
#define stshort(sval, addr) ( *((short *)(addr))=htons(sval) )
#define ldshort(addr) ( ntohs(*((short *)(addr)) ) ) 

// Port per defecte
// TODO: Canviar el port 8000 pel port corresponent de cada subgrup segons
// la formula proporcionada a l'enunciat
#define DEFAULT_PORT 10085

//codis dels diferents missatges
#define HELLOWORLDRQ 20
#define HELLOWORLDRP 21
#define MAPRQ 1
#define MAP 2

/**
* Funcio que printa el buffer amb l'aforament en format aforament
* @param buffer Punter al buffer que conte l'aforament 
* @param bufferLength Tamany de l'aforament del buffer
**/
void printMap(char *buffer, int bufferLength);  

/**
 * Funció que mostra el contingut d'un buffer mostrant de dos bytes en dos bytes
 * tractant-los com a short.
 * @param buffer el buffer a mostrar
 * @param bufferLength la longitud d'aquest buffer
 */
void printBuffer(char *buffer, int bufferLength);
