#include <stdio.h>
#include <stdlib.h>
#include "dimacs.h"

Fnc lecture_dimacs(char* nf){
  
  Fnc cnf;
  char *line = NULL;
  size_t len = 0;
  size_t lire;
  FILE* f = NULL;
  int i,j;
  int coef = 1;
  int position = 0;
  int nbrecolonne, nbreline;
  int k = 0;

  f = fopen(nf, "r");
  if (f == NULL) {
    printf("erreur lors ouverture du fichier DIMACS : ");
  }
  else{
    i=0;
    while (( lire = getline(&line, &len, f)) != -1){
      

	if (line[0] == 'p'){
	  position = 0;
     //recuperer le nbre de clauses et lit
	  nbreline = lire_int(line, &position);
	  nbrecolonne = lire_int(line, &position);
    //reserver de l espace memoire pour la fnc dim avec nc(nbre de clauses) et nl (nbre de lit)
	  init_fnc(&cnf, nbrecolonne, nbreline);
	  for(j=0; j<nbrecolonne; j++){
       //initialisation de l espace memoire pour la clause de taille nl 
	    init_clause(&(cnf.clauses[j]), nbreline);
	  }
	
	}else{

	  j=0;
	  position = 0;
     //lecture des literaux
	  while ((coef = lire_int(line, &position)) != 0){
      //tableau de coef
	    cnf.clauses[i].coef[j] = coef;
      //inserer literal dans une clause
      //les literaux 
	    inserer_literau(&cnf, coef, &k);
	    j++;
	  }
     //le nbre de literaux dans la clause
	  cnf.clauses[i].nb_lit = j;
	  i++;
	}
      
    }
    
    free(line);
    fclose(f);
  }
  
  return cnf;
  
}



//nf = fichier de sortie
int ecrire_dimacs(char* nf, Fnc fnc){
  
  int i, j;
  FILE* f = NULL;
  
  f = fopen(nf, "w+");
  if (f == NULL){
    printf(" erreur lors de la création du fichier DIMACS : ");

    return 0;
  }
  
  //on affiche le nombre totale des literaux et le nombre totale des clauses qui correspond a chaque grille generer 
  fprintf(f, "p cnf %d %d \n", fnc.nb_lit, fnc.nb_clse);
  for (i=0; i<fnc.nb_clse; i++){
    for (j=0; j<fnc.clauses[i].nb_lit; j++){
      fprintf(f, " %d", fnc.clauses[i].coef[j]);
    }
    fputs(" 0 \n", f);
  }
  fclose(f);
  return 1;
}


//comparer 2 entier 
int comparer (const void * a, const void * b)
{
  return ( *(int*)a - *(int*)b );
}

//insere un literale dans une clause
void inserer_literau(Fnc* fnc, int a, int* n){

  /* recherche de la valeur */

  int* lit = NULL;
  int* litm = NULL;
  int cle = -a;
  
  //cherche la valeur key(literal) dans le tableau de lit (g->lit) ds la pos n en la comparant avec toute les valeurs du tableau  
  //elle renvoie un bol pour indiquer si trouver ou pas 
  lit = (int*) bsearch(&cle, fnc->lit, *n, sizeof (int), comparer);
  litm= (int*) bsearch(&a, fnc->lit, *n, sizeof(int), comparer); 


  if (lit == NULL && litm == NULL){
    fnc->lit[*n] = abs(a);
    *n = *n + 1;

    // tri du tableau
    qsort(fnc->lit, *n, sizeof(int), comparer);
  }

}


