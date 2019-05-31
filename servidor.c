#include "fservidor.c"
#include "common.c"
int main(int argc, char *argv[]){
	int i = 0; // comptador
	int parametre; // variable per parsejar els parametres introduits pel prompt
	int ctrl_fitxer = 0; // variable de control del parametre -f
	char *fitxer; // Punter per crear dinamicament un string amb el nom del fitxer
	struct cinema cine; // Estructura per emmagatzemar les dades del cinema
	int port = DEFAULT_PORT; // Port per a l'estructura del nom del servidor
  	char cineBuffer[1024]; // Buffer on guardarem el mapa a enviar al client
	char buffer[1024];
	int fila, columna;
	//int x=2;
	// Tractem els parametres introduits pel prompt
	while((parametre = getopt(argc, argv, "p:f:")) != -1){
		switch((char) parametre){
			case 'p':
				// Donat que hem inicialitzat amb valor DEFAULT_PORT (veure common.h) 
				// la variable port, aquest codi nomes canvia el valor de port en cas
				// que haguem especificat un port diferent amb la opcio -p
				port = atoi(optarg);
				break;
			case 'f':
				// Capturem el nom del fitxer
				// Creem dinamicament espai per emmagatzemar la cadena de text que conte el nom del fitxer
				// en la variable fitxer. L'espai requerit es la longitud de la cadena (obtinguda
				// amb strlen, mes 1, donat que totes les cadenes de text acabem amb el caracter '\0'
				// que no es tingut en compte per strlen, ni es mostra per pantalla al fer printf
				fitxer = (char*) malloc(sizeof(char)*(strlen(optarg)+1));
				// Un cop creat l'espai, podebufferm copiar la cadena
				strcpy(fitxer, optarg);
				ctrl_fitxer = 1;
				break;
			default:
				printf("Error: parametre %c desconegut\n\n", (char) parametre);
				return -1;
		}
	}

	// Controlem que s'hagi introduit el nom d'un fitxer	
	if(!ctrl_fitxer){
		perror("No s'ha especificat un fitxer\n\n");
		return -1;
	}
	
	
	// Cridem a la funcio per carregar les dades del fitxer
	// a la estructura "cine"
	if (carregarFitxer(&cine, fitxer) == -1){
		perror("Les dades del fitxer no s'han carregat correctament\n\n");
		free(fitxer);
		//close(sock);
		return -1;
	}

  //DEBUG
  //Codi de prova on s'encapsula l'aforament en un buffer per enviar-lo al 
  //client i es printa el contingut d'aquest buffer per comprovar que sigui
  //correcte.
  mapToByteArray(&cine, cineBuffer);
  printMap(cineBuffer, 100);
  printf("\n\n");

	int sock = socket(PF_INET,SOCK_DGRAM,0);
	
	struct sockaddr_in  cliente, servidor;
	socklen_t tcliente = sizeof(cliente);

	servidor.sin_family = AF_INET;;
	servidor.sin_port = htons(port);
	servidor.sin_addr.s_addr = INADDR_ANY;
	bind ( sock, (struct sockaddr *)&servidor, sizeof (servidor));

	// Entrem en un bucle infinit per rebre peticions
	while(1)
  	{
	i = recvfrom (sock, buffer,sizeof(buffer),0, (struct sockaddr*)&cliente, &tcliente);

	
	switch(ldshort(buffer))
	{
		//HELLO
		case 1:
			serverhello(sock,cliente);	
		break;

		//MAP
		case 3:	
		  	servermapa(sock,cliente,cine);
		break;
		
		//PRICE//RECIBE FILA I COLUMNA I ENVIA AL CLIENTE EL PRECIO
		case 5:
	
		 fila=(ldshort(buffer+2))-1;
		 columna=(ldshort(buffer+4))-1;
		 serverprice(sock, cliente, cine, fila, columna);
		break;
		
		////BUY//////FILA I COLUMNA , RETORNA OK o ERROR
		case 7:
		 
 		 fila=(ldshort(buffer+2))-1;
		 columna=(ldshort(buffer+4))-1;
		 servercompra(sock, cliente, cine, fila, columna);
		 
		break;

		///RETURN SEIENT/// FILA COLUMNA, RETORNA OK o ERROR
		case 10:
		 
 		 fila=(ldshort(buffer+2))-1;
		 columna=(ldshort(buffer+4))-1;
		 serverdevolucio(sock, cliente, cine, fila, columna);
		 
		break;
		

			/*
		case 8:
			while(x<sizeof(buffer)){
			fila=(ldshort(buffer+x))-1;
		 	columna=(ldshort(buffer+x+2))-1;
			
			
			if((fila>cine.files)||(columna>(cine.seients[fila])))
			 {
			  
			
			 bzero(buffer,sizeof(buffer));
			 stshort(14,buffer);
			 stshort(1,buffer+x);
			 strcat(buffer+x,"\0");
			 sendto(sock, buffer, sizeof(buffer), 0, (struct sockaddr *)&cliente, sizeof(cliente));
			 
			 }else{
			 if(cine.aforament[(int)fila][(int)columna]<0)
			 {
			  
			
			 bzero(buffer,sizeof(buffer));
			 stshort(14,buffer);
			 stshort(2,buffer+x);
			 strcat(buffer+x,"\0");
			 sendto(sock, buffer, sizeof(buffer), 0, (struct sockaddr *)&cliente, sizeof(cliente));
			 
			 }else{

			 bzero(buffer,sizeof(buffer));
			 stshort(13,buffer);
	
			 mapToByteArray(&cine, cineBuffer);
		
			 butaca=cine.aforament[(int)fila][(int)columna];
			 stshort(butaca,buffer+x);
			 cine.aforament[(int)fila][(int)columna]=butaca*(-1);
			 mapToByteArray(&cine, cineBuffer);

			 
			}}
				x=x+4;
			} 
			
			 strcat(buffer+x,"COMPRA REALITZADA");	
			 strcat(buffer+x,"\0");
			 sendto(sock, buffer, sizeof(buffer), 0, (struct sockaddr *)&cliente, sizeof(cliente));
		break;*/
	}





  }	

	// Alliberem la memoria reservada per a cada fila de la "sala de cine"
	for (i=0;i<cine.files;i++){
		free(cine.aforament[i]);
	}
	// Alliberem la memoria de la primera dimensio de l'array
	free(cine.aforament);
	// Alliberem la memoria de l'array de butaques
	free(cine.seients);
	// Tanquem el socket
	//close(sock);
	return 0;
}

