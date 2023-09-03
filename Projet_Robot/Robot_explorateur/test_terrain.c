#include <stdio.h>
#include "terrain.h"

int main(int argc, char **argv) {
  Terrain t;
  FILE *f;
  int x, y;
  char nom_fichier;

  if (argc < 2) {
    printf("Usage : %s <fichier>\n", argv[0]);
    return 1;
  }

 nom_fichier = argv[1];
 f = fopen(argv[1], "r");
  while (f == NULL) {
    printf("Entrer le nom d'un fichier '\n'");
    scanf("%c", &nom_fichier);
  }

  lire_terrain(argv[1], &t, &x, &y);
  afficher_terrain(&t);
  printf("Position initiale du robot : (%d, %d)\n", x, y);
}
