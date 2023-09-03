#ifndef GRILLE
#define GRILLE
#include <time.h>
 #define NOIR 1
 #define BLANC 0
 #define VAL 0
 #define NE 1
 #define NW 2
 #define SE 3
 #define SW 4
 #define N 5
 #define S 6
 #define E 7
 #define W 8
 
 typedef struct {
     int n;
     int** val;
     int** pixels;
 }grille;
 
 typedef struct {
     int x;
     int y;
 }Case;
 
 
/* initialise un plateau vide */
void initialisation_plateau(grille *p, int n);

/* remplis un plateau rempli aléatoirement */
void rempli_alea(grille *p);


grille open(char* fichier);

/* détruit un plateau */
void suppression_plateau(grille *p);

/* retourne la valeur bool du pixel dir d'une case */
int get_pixel(grille p, int x, int y, int dir);

/* retourne le numéro unique d'un pixel dir */
int get_no_pixel(grille p, int x, int y, int dir);
int ecrire(grille p, char* fichier);
/* met à jour le pixel (x,y) à la valeur val */
void set_pixel(grille* p, int x, int y, int val);
/* Affiche le plateau en console */
void print(grille p);
 #endif
 
