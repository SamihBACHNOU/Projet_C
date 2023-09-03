#include <stdio.h>
#include "observateur.h"
#include "environnement.h"

void main(int argc, char **argv){
FILE *ftest;
	char nom_fenvt[LMAX]; /* Nom du fichier terrain */
	char nom_fprog[LMAX]; /* Nom du fichier programme */
	Environnement envt;
	Programme prog;
	erreur_terrain errt;
	erreur_programme errp;
	int nbstepmax;
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
	
	/* Résultat de l’observateur */
	if(resultat_observateur(&envt)){
		printf("Observateur : propriété valide\n");
	} else {
		printf("Observateur : propriété fausse\n");
	}
}
