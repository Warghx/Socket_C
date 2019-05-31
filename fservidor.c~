#include "fservidor.h"

/**
 * Funcio que carrega el fitxer amb el mapa de butaques
 * @param cine estructura on carregar el mapa de memoria del fitxer
 * @param fitxer nom del fitxer amb el mapa de butaques.
 */
int carregarFitxer(struct cinema *cine, char* fitxer){
	FILE* fdesc;
	int i, j;

	// Obrim el fitxer en mode lectura
	if( (fdesc = fopen(fitxer, "r")) == NULL){
		perror("No s'ha pogut obrir el fitxer correctament\n\n");
		return -1;

	}
	// El primer sencer que trobem correspon al numero de files
	fscanf(fdesc, "%hi", &cine->files);

	// Per cada fila, hi ha un sencer amb el numero de butaques de la fila
	// Cal crear un array dinamicament amb una posicio per cada fila, on es
	// guardara el numero de butaques de la fila
	cine->seients = (short*) malloc(sizeof(short)*cine->files);
	for (i=0;i<cine->files;i++)
		fscanf(fdesc, "%hi", &cine->seients[i]);
	
	// Ara cal crear un array bidimensional per emmagatzemar els preus de les butaques
	// En la primera dimensió creem un array de punters a short. De tants punters 
	// com files tinguem. Aquests punters apunten a les butaques de cada fila.
	cine->aforament = (short**) malloc(sizeof(short*)*cine->files);
	// Per cada fila, creem la segona dimensio, que seran les butaques de la fila.
	for (i=0;i<cine->files;i++)
		cine->aforament[i] = (short*) malloc(sizeof(short)*cine->seients[i]);
	// Finalmente, emmagatzemem els preus
	for (i=0;i<cine->files;i++)
		for (j=0;j<cine->seients[i];j++)
			fscanf(fdesc, "%hi", &cine->aforament[i][j]);

    // Tanquem el fitxer
    fclose(fdesc);
  return 0;

    fclose(fdesc);
	return 0;
}

/**
 * Funcio que printa el mapa de butaques que hi ha carregat en memoria
 * Aquesta funció és només per debugar.
 * @param cine el mapa de butaques del cinema a mostrar
 */
void mostraAforament ( struct cinema *cine )
{
    int i,j;
    
    printf ( "\nMostrant Aforament: \n" );
    for ( i=0;i<cine->files;i++ )
    {
        for ( j=0;j<cine->seients[i];j++ )
            printf ( "%hi ", cine->aforament[i][j] );
        printf ( "\n" );
    }
    printf ( "\n" );
}

/**
 * Funcio que converteix l'aforament del cinema carregat en memoria a una cadena
 * de bytes tot incloent la informació del número de files i els seients 
 * per fila que hi han.
 * @param cine el mapa de butaques 
 * @param cinemaToStr buffer on desarem el mapa de butaques passat a cadena de 
 * caracters
 */
 
void mapToByteArray(struct cinema *cine, char *cinemaStr)
{
    int i,j;
    
    printf("Map To String\n"); //DEBUG
    fflush(stdout);
        
    stshort(cine->files, cinemaStr);    
    cinemaStr+=sizeof(short);
    for(i=0; i< cine->files; i++)
    {
      stshort(cine->seients[i], cinemaStr);
      cinemaStr+=sizeof(short);      
    }
    for(i=0; i< cine->files; i++)
    {
      for(j=0; j<cine->seients[i]; j++)
      {
        stshort(cine->aforament[i][j], cinemaStr);
        cinemaStr+=sizeof(short);
      }
    } 
}

void serverhello(int sock, struct sockaddr_in cliente){
	char buffer[512]; 


	bzero(buffer, sizeof(buffer));		
	stshort(2,buffer);
	strcat(buffer+2,"HELLO WORLD");
	strcat(buffer+2,"\0");
	sendto(sock, buffer, sizeof(buffer), 0, (struct sockaddr *)&cliente, sizeof(cliente));
}


void servermapa(int sock, struct sockaddr_in cliente, struct cinema cine){
	 char buffer[1024];	 
	 char cineBuffer[1024];
	 mapToByteArray(&cine, cineBuffer);
	 bzero(buffer, sizeof(buffer));		
	 stshort(4,buffer);
	 memcpy(buffer+2,cineBuffer,sizeof(cineBuffer));
	 sendto(sock, buffer, sizeof(buffer), 0, (struct sockaddr *)&cliente, sizeof(cliente));	

}


void serverprice(int sock, struct sockaddr_in cliente, struct cinema cine, short fila, short columna){

	char buffer[1024];
	int butaca=0;
	char cineBuffer[1024];

	if((fila>cine.files)||(columna>(cine.seients[fila])))
	 {
	  
	//BUTACA INEXISTENT
	 bzero(buffer,sizeof(buffer));
	 stshort(14,buffer);
	 stshort(1,buffer+2);
	 strcat(buffer+2,"\0");
	 sendto(sock, buffer, sizeof(buffer), 0, (struct sockaddr *)&cliente, sizeof(cliente));
	 
	 }else{
	//OP OK
	 bzero(buffer,sizeof(buffer));
	 stshort(6,buffer);

	 mapToByteArray(&cine, cineBuffer);
	 butaca=cine.aforament[(int)fila][(int)columna];	
	 stshort(butaca,buffer+2);
	 strcat(buffer+2,"\0");
	 
	 sendto(sock, buffer, sizeof(buffer), 0, (struct sockaddr *)&cliente, sizeof(cliente));
	 
	}
}


void servercompra(int sock, struct sockaddr_in cliente, struct cinema cine, short fila, short columna){
	
	char buffer[1024];
	int butaca=0;
	char cineBuffer[1024];

	if((fila>cine.files)||(columna>(cine.seients[fila])))
		 {
		  
		//SEIENT INEXISTENT	
		 bzero(buffer,sizeof(buffer));
		 stshort(14,buffer);
		 stshort(1,buffer+2);
		 strcat(buffer+2,"\0");
		 sendto(sock, buffer, sizeof(buffer), 0, (struct sockaddr *)&cliente, sizeof(cliente));
		 
		 }else{
		 if(cine.aforament[(int)fila][(int)columna]<0)
		 {
		  
		//SEIENT JA COMPRAT
		 bzero(buffer,sizeof(buffer));
		 stshort(14,buffer);
		 stshort(2,buffer+2);
		 strcat(buffer+2,"\0");
		 sendto(sock, buffer, sizeof(buffer), 0, (struct sockaddr *)&cliente, sizeof(cliente));
		 
		 }else{
		//OP OK
		 bzero(buffer,sizeof(buffer));
		 stshort(13,buffer);
	
		 mapToByteArray(&cine, cineBuffer);
		
		 butaca=cine.aforament[(int)fila][(int)columna];

		 cine.aforament[(int)fila][(int)columna]=butaca*(-1);
		 mapToByteArray(&cine, cineBuffer);
       
		 strcat(buffer+2,"COMPRA REALITZADA");	
		 strcat(buffer+2,"\0");
		 
		 sendto(sock, buffer, sizeof(buffer), 0, (struct sockaddr *)&cliente, sizeof(cliente));
		 
		}}	


}


void serverdevolucio(int sock, struct sockaddr_in cliente, struct cinema cine, short fila, short columna){
	char buffer[1024];
	int butaca=0;
	char cineBuffer[1024];

	if((fila>cine.files)||(columna>(cine.seients[fila])))
		 {
		  
		//ERROR SEIENT NO EXISTENT
		 bzero(buffer,sizeof(buffer));
		 stshort(14,buffer);
		 stshort(1,buffer+2);
		 strcat(buffer+2,"\0");
		 sendto(sock, buffer, sizeof(buffer), 0, (struct sockaddr *)&cliente, sizeof(cliente));
		 
		 }else{
		 if(cine.aforament[(int)fila][(int)columna]>0)
		 {
		  
		//ERROR SEIENT NO COMPRAT	
		 bzero(buffer,sizeof(buffer));
		 stshort(14,buffer);
		 stshort(3,buffer+2);
		 strcat(buffer+2,"\0");
		 sendto(sock, buffer, sizeof(buffer), 0, (struct sockaddr *)&cliente, sizeof(cliente));
		 
		 }else{
		//OP OK
		 bzero(buffer,sizeof(buffer));
		 stshort(13,buffer);
	
		 mapToByteArray(&cine, cineBuffer);
		
		 butaca=cine.aforament[(int)fila][(int)columna];
		 //stshort(butaca,buffer+2);
		 cine.aforament[(int)fila][(int)columna]=butaca*(-1);
		 mapToByteArray(&cine, cineBuffer);
       
		 strcat(buffer+2,"DEVOLUCIO REALITZADA");	
		 strcat(buffer+2,"\0");
		 
		 sendto(sock, buffer, sizeof(buffer), 0, (struct sockaddr *)&cliente, sizeof(cliente));
		 
		}}	

}















