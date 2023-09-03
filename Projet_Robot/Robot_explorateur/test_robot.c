#include "robot.h"
#include <stdio.h>

#define TAILLE_TERRAIN 10

/* Affiche une orientation sur la sortie standard */
void afficher_orientation(Orientation o) {
  switch (o) {
  case Nord:
    printf("Nord\n");
    break;
  case Est:
    printf("Est\n");
    break;
  case Sud:
    printf("Sud\n");
    break;
  case Ouest:
    printf("Ouest\n");
    break;
  }
}

void afficher_infos_robot(Robot r) {
  int x, y;
  int x1, y1;

  // Récupérer la position du robot
  position(r, &x, &y);
  // Récupérer la case devant le robot
  position_devant(r, &x1, &y1);
  // Afficher la position
  printf("Position : (%d, %d) - Orientation : ", x, y);
  afficher_orientation(orient(r));
  printf("\n");
}

int main(int argc, char **argv) {
  Terrain t;
  int x, y;
  Robot r;
  char c;

  // Lecture du terrain : nom du fichier en ligne de commande
  if (argc < 2) {
    printf("Usage: %s <fichier terrain>\n", argv[0]);
    return 1;
  }

  // Lecture du terrain
  lire_terrain(argv[1], &t, &x, &y);

  // Initialisation du robot
  init_robot(&r, x, y, Est);

  afficher_infos_robot(r);
  afficher_terrain_et_robot(t, r);

  printf("Entrer une action ([a]vancer, [g]auche, [d]roite, [f]in : ");
  scanf(" %c", &c);
    while (c != 'f') {
    int x, y; // Position devant
    switch (c) {
    case 'G':
    case 'g':
      tourner_a_gauche(&r);
      break;
    case 'D':
    case 'd':
      tourner_a_droite(&r);
      break;
    case 'A':
    case 'a':
      position_devant(r, &x, &y);
      if (robot_peut_avancer(t, r)) {
        avancer(&r);
      } else {
        printf(" !! Le robot ne peut pas avancer !!\n");
      }
    break;
    default:
        printf("Entrer une action ([a]vancer, [g]auche, [d]roite, [f]in : ");
    }
    afficher_infos_robot(r);

    printf("Entrer une action ([a]vancer, [g]auche, [d]roite, [f]in : ");
    scanf(" %c", &c);
  }
}
