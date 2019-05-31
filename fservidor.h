#include "common.h"

struct cinema{
	short files;
	short *seients;
	short **aforament;
};
/*

 * Funcio que carrega el fitxer amb el mapa de butaques
 * @param cine estructura on carregar el mapa de memoria del fitxer
 * @param fitxer nom del fitxer amb el mapa de butaques.
 
int carregarFitxer(struct cinema *cine, char* fitxer);

 * Funcio que printa el mapa de butaques que hi ha carregat en memoria
 * Només s'utilitza per a debugar.
 * @param cine el mapa de butaques del cinema a mostrar
 
void mostraAforament(struct cinema *cine);

 * Funcio que converteix l'aforament del cinema carregat en memoria a una cadena
 * de bytes tot incloent la informació del número de files i els seients 
 * per fila que hi han.
 * @param cine el mapa de butaques 
 * @param cinemaToStr buffer on desarem el mapa de butaques passat a cadena de 
 * caracters

void mapToByteArray(struct cinema *cine, char *cinemaStr);


void serverhello(int sock, struct sockaddr_in cliente);

void servermapa(int sock, struct sockaddr_in cliente, struct cinema cine);

void serverprice(int sock, struct sockaddr_in cliente, struct cinema cine, short fila, short columna);

void servercompra(int sock, struct sockaddr_in cliente, struct cinema cine, short fila, short columna);

void serverdevolucio(int sock, struct sockaddr_in cliente, struct cinema cine, short fila, short columna);
*/