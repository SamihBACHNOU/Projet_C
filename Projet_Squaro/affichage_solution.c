#include <stdio.h>
#include <stdlib.h>

#include "grille_du_jeux.h"
#include "lecture.h"

int main(int argc, char *argv[]){
  grille p = {0, NULL, NULL};
  FILE* f = NULL;
  int i, j, n, pos;

  char *line = NULL;
  size_t len = 0;
  size_t read;

  if (argc < 2){
    printf("arguments insuffisants \n", argv[0]);
    printf(" veuillez entrer  \n");
    printf(" une grille \n");
    //fichier resultat du sat solveur
    printf("un fichier de d'assignation \n \n");
    
    exit(0);
  }

  f = fopen(argv[2], "r");
  p = open(argv[1]);

  while (( read = getline(&line, &len, f)) != -1){
    if (line[0] == 'S'){
      printf("Le plateau est resoluble : \n");
    }
    else if (line[0] == 'U'){
      printf("Le plateau n'est pas resoluble. \n");
    }
    else{
      pos = 0;
      for (i=0; i<=p.n; i++){
	for (j=0; j<=p.n; j++){
	  n = lire_int(line, &pos);
	  if (n > 0){
      //colorier la case 
	    set_pixel(&p, j, i, 1);
	  }else{
	    set_pixel(&p, j, i, 0);
	  }
	}
      }

    }
  }

  print(p);

  suppression_plateau(&p);
  fclose(f);
  return 0;
}
