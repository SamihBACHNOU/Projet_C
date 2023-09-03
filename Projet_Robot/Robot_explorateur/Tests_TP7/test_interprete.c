#include "environnement.h"
#include "interprete.h"
#include "programme.h"

#include <stdio.h>
#include <stdlib.h>

/* Longueur de chaîne maximum */
#define LMAX 100

void gestion_erreur_terrain(erreur_terrain e) {
	switch (e) {
		case OK:
		break;
		case ERREUR_FICHIER:
		printf("Erreur lecture du terrain : erreur d'ouverture du fichier\n");
		exit(1);
		case ERREUR_LECTURE_LARGEUR:
		printf("Erreur lecture du terrain : erreur de lecture de la largeur\n");
		exit(1);
		case ERREUR_LECTURE_HAUTEUR:
		printf("Erreur lecture du terrain : erreur de lecture de la hauteur\n");
		exit(1);
		case ERREUR_LARGEUR_INCORRECTE:
		printf("Erreur lecture du terrain : largeur incorrecte\n");
		exit(1);
		case ERREUR_HAUTEUR_INCORRECTE:
		printf("Erreur lecture du terrain : hauteur incorrecte\n");
		exit(1);
		case ERREUR_CARACTERE_INCORRECT:
		printf("Erreur lecture du terrain : caractère incorrect\n");
		exit(1);
		case ERREUR_LIGNE_TROP_LONGUE:
		printf("Erreur lecture du terrain : ligne trop longue\n");
		exit(1);
		case ERREUR_LIGNE_TROP_COURTE:
		printf("Erreur lecture du terrain : ligne trop courte\n");
		exit(1);
		case ERREUR_LIGNES_MANQUANTES:
		printf("Erreur lecture du terrain : lignes manquantes\n");
		exit(1);
		case ERREUR_POSITION_ROBOT_MANQUANTE:
		printf("Erreur lecture du terrain : position initiale du robot manquante\n");
		exit(1);
	}
}


void affichage_position_programme(erreur_programme e) {
	int i;
	printf("Ligne %d, colonne %d :\n", e.num_ligne, e.num_colonne);
	printf("%s\n", e.ligne);
	
	/* Impression de e.num_colonne-1 espaces */
	for (i = 1; i < e.num_colonne; i++) {
		printf(" ");
	}

	/* Impression d'un curseur de position */
	printf("^\n");
}


void gestion_erreur_programme(erreur_programme e) {
	
	switch (e.type_err) {
		case OK_PROGRAMME:
		break;
		case ERREUR_FICHIER_PROGRAMME:
		printf("Erreur lecture du programme : erreur d'ouverture du fichier\n");
		exit(2);
		case ERREUR_BLOC_NON_FERME:
		printf("Erreur lecture du programme : bloc non fermé\n");
		exit(2);
		case ERREUR_FERMETURE_BLOC_EXCEDENTAIRE:
		printf("Erreur lecture du programme : fermeture de blocexcédentaire\n");
		affichage_position_programme(e);
		exit(2);
		case ERREUR_COMMANDE_INCORRECTE:
		printf("Erreur lecture du programme : commande incorrecte\n");
		affichage_position_programme(e);
		exit(2);
	}
}


/* Affiche "Ok." et renvoie 0 si la position du robot correspond
aux coordonnées (ax, ay) avec l'orientation ao.
Sinon affiche les coordonnées obtenues et les coordonnées attendues,
et renvoie 1 */


int etat_attendu(Robot r, int ax, int ay, char ao) {
	int rx, ry;
	char ro;

	rx = abscisse(r);
	ry = ordonnee(r);

	switch (orient(r)) {
		case Nord:
		ro = 'N';
		break;
		case Sud:
		ro = 'S';
		break;
		case Est:
		ro = 'E';
		break;
		case Ouest:
		ro = 'O';
		break;
	}
	if ((rx == ax) && (ry == ay) && (ro == ao)) {
		printf("Ok.\n");
		return 0;
	} else {
		printf("Position attendue : (%d, %d), %c\n", ax, ay, ao);
		printf("Position obtenue : (%d, %d), %c\n", rx, ry, ro);
		printf("Test échoué.\n");
		return 1;
	}
}


int main(int argc, char **argv) {
	FILE *ftest;
	char nom_fenvt[LMAX]; /* Nom du fichier terrain */
	char nom_fprog[LMAX]; /* Nom du fichier programme */
	Environnement envt;
	Programme prog;
	erreur_terrain errt;
	erreur_programme errp;
	int nbstepmax; /* Nombre de pas maximum */
	/* Caractère représentant l'événement attendu :
	- N : position normale du robot, programme non terminé
	- F : position normale du robot, programme terminé
	- S : le robot est sorti du terrain
	- O : le robot a rencontré un obstacle
	- P : le robot est tombé dans l'eau
	*/
	char cevent;
	int ax, ay; /* Position attendue du robot (cas N et F) */
	char ao; /* Orientation attendue du robot (N, S, E, O) */
	int nbstep; /* Nombre de pas courant */
	etat_inter etat;
	resultat_inter res;

	if (argc < 2) {
		printf("Usage: %s <fichier test>\n", argv[0]);
		return 1;
	}
	
	ftest = fopen(argv[1], "r");
	fscanf(ftest, "%s\n", nom_fenvt);

	/* Initialisation de l'environnement : lecture du terrain,
	initialisation de la position du robot */
	errt = initialise_environnement(&envt, nom_fenvt);
	gestion_erreur_terrain(errt);
	fscanf(ftest, "%s\n", nom_fprog);

	/* Lecture du programme */
	errp = lire_programme(&prog, nom_fprog);
	gestion_erreur_programme(errp);
	
	/* Lecture du nombre de pas max */
	fscanf(ftest, "%d\n", &nbstepmax);

	/* Lecture du caractère indiquant l'événement attendu */
	fscanf(ftest, "%c\n", &cevent);
	
	if ((cevent == 'N') || (cevent == 'F')) {
	
		/* Lecture de la position et de l'orientation attendue du robot */
		fscanf(ftest, "%d %d\n", &ax, &ay);
		fscanf(ftest, "%c", &ao);
	}

	/* Initialisation de l'état */
	init_etat(&etat);
	res = OK_ROBOT;

	for (nbstep = 0; (nbstep < nbstepmax) && (res == OK_ROBOT); nbstep++){
		res = exec_pas(&prog, &envt, &etat);
	
		/* Affichage du terrain et du robot */
		afficher_envt(&envt);
	}

	/* Affichage du résultat */
	switch (res) {
		case OK_ROBOT:
			printf("Robot sur une case libre, programme non terminé\n");
				if (cevent == 'N') {
				return etat_attendu(envt.r, ax, ay, ao);
			} else {
				printf("Test échoué, état attendu = %c\n", cevent);
				return 1;
			}
		case SORTIE_ROBOT:
			printf("Le robot est sorti :-)\n");
			if (cevent == 'S') {
				printf("Ok.\n");
				return 0;
			} else {
				printf("Test échoué, état attendu = %c\n", cevent);
				return 1;
			}
		case ARRET_ROBOT:
			printf("Robot sur une case libre, programme terminé :-/\n");
			if (cevent == 'F') {
				return etat_attendu(envt.r, ax, ay, ao);
			} else {
				printf("Test échoué, état attendu = %c\n", cevent);
				return 1;
			}
		case PLOUF_ROBOT:
			printf("Le robot est tombé dans l’eau :-(\n");
			if (cevent == 'P') {
				printf("Ok.\n");
				return 0;
			} else {
				printf("Test échoué, état attendu = %c\n", cevent);
				return 1;
			}
		case CRASH_ROBOT:
			printf("Le robot s'est écrasé sur un rocher X-(\n");
			if (cevent == 'O') {
				printf("Ok.\n");
				return 0;
			} else {
				printf("Test échoué, état attendu = %c\n", cevent);
				return 1;
			}
		case ERREUR_PILE_VIDE:
			printf("ERREUR : pile vide\n");
			return 1;
		case ERREUR_ADRESSAGE:
			printf("ERREUR : erreur d'adressage\n");
			return 1;
		case ERREUR_DIVISION_PAR_ZERO:
			printf("ERREUR : division par 0\n");
			return 1;
	}
}
