#include "common.h"




/**
* Funcio que printa el buffer amb l'aforament en format aforament
* @param buffer Punter al buffer que conte l'aforament 
* @param bufferLength Tamany de l'aforament del buffer
**/
void printMap(char *buffer, int bufferLength)
{
  int i, j;
  short files;
  short *seients;
  short *aforament;

  files = ldshort(buffer);
  buffer+=sizeof(short);
  seients = (short*)buffer;
  buffer += (files * sizeof(short)); //ens posicionem a l'inici de l'aforament
  aforament = (short *)buffer;
  for (i = 0; i < files; i++)
  {
    fflush(stdout);
    for(j = 0; j < ntohs(seients[i]); j++)
    {
      printf("%hi ", ldshort(aforament));
      fflush(stdout);
      aforament++;      
    }
    printf("\n"); //new row
  }
}





