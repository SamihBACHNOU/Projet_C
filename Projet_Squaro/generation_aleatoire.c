#include <stdio.h>
#include <stdlib.h>

#include "grille_du_jeux.h"

int main(int argc, char *argv[]){
  grille p = {0, NULL, NULL};  
  int n;
  char s[100] = {0};

  if (argc < 2){
    printf(" arguments insuffisants \n", argv[0]);
    printf("veuillez entrer : \n");
    printf("une taille pour la grille N \n");
    printf("et un fichier de sortie\n ");
    
    return 1;
  }

  /*lecture de lataille de la rentrer standard  */
  sscanf(argv[1], "%d", &n);
  //allocation memoire pour la grille 
  initialisation_plateau(&p, n);
  //le generation aléatoire de la grille
  rempli_alea(&p);
  //ecrire de la grille 
  print(p);
    ecrire(p, argv[2]);
  //liberation memoire 
  suppression_plateau(&p); 

  return 0;
}
