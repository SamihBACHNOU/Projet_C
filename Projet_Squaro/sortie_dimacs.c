#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "grille_du_jeux.h"
#include "manipulation_fnc.h"
#include "dimacs.h"


typedef struct _lst{
  Fnc f;
  struct _lst* nxt;
}Lst_Fnc;


Fnc modelisation(grille);
Fnc fnc_case(grille, int, int);
void del_lst(Lst_Fnc*);

Fnc modelisation(grille p){
  int i, j, n;
  Lst_Fnc* res = NULL;
  Lst_Fnc* courant = NULL;
  Lst_Fnc* tmp = NULL;

  Fnc f;
  //reccuperation des clauses
  res = (Lst_Fnc*)malloc(sizeof(Lst_Fnc));
  res->f = fnc_case(p, 0, 0);
  res->nxt = NULL;

  courant = res;
  

  //recuperer les fncs

  n = 2;
  for (i=0; i<p.n; i++){
    for (j=0; j<p.n; j++){

      if (i != 0){
	n = 1;
      }
      
      if ( i != 0 || j != 0){
	tmp = (Lst_Fnc*)malloc(sizeof(Lst_Fnc));
	tmp->f = fnc_case(p, j, i);
	
	courant->nxt = tmp;
	courant = tmp;
	courant->nxt = NULL;
      }
    }
  }
  
  
  n=0;
  courant = res;
  while (courant != NULL){
    n += courant->f.nb_clse;
    courant = courant->nxt;
  }

  
  init_fnc(&f, n, (p.n+1)*(p.n+1));
  courant = res;
  n = 0;
  while (courant != NULL){
    for (i=0; i<courant->f.nb_clse; i++){
      f.clauses[n].nb_lit = courant->f.clauses[i].nb_lit;
      for (j=0; j<(courant->f.clauses[i].nb_lit); j++){
	f.clauses[n].coef[j] = courant->f.clauses[i].coef[j];
      }
      n++;
    }
    courant = courant->nxt;
  }

  for (i=0; i<((p.n+1)*(p.n+1)); i++){
    f.lit[i] = i+1;
  }

  /* liberration memoire */
  
  courant = res;
  while (courant != NULL){
    tmp = courant->nxt;
    del_fnc(&(courant->f));

    free(courant);
    courant = tmp;
  }

  return f;
}


/* retourne la forme normale conjonctive associée à une case 
   Par exemple pour une case numérotée 0 :
     G = {
          -(X_NW)
	  -(X_NE)
	  -(X_SW)
	  -(X_SE)
	 }
*/
Fnc fnc_case(grille p, int x, int y){
  Fnc res;
  int i, j;
  int a;
  
  switch (p.val[x][y]){

  case 0:
    res = lecture_dimacs("case0.fnc");
    break;

  case 1:
    res = lecture_dimacs("case1.fnc");
    break;

  case 2:
    res = lecture_dimacs("case2.fnc");
    break;

  case 3:
    res = lecture_dimacs("case3.fnc");
    break;

  case 4:
    res = lecture_dimacs("case4.fnc");
  }    

  for (i=0; i<res.nb_clse; i++){
    for (j=0; j<res.clauses[i].nb_lit; j++){
      a = abs(res.clauses[i].coef[j]);
      switch (a){
      case 1:
	res.clauses[i].coef[j] /= a; 
	res.clauses[i].coef[j] *= get_no_pixel(p, x, y, NW);
	break;
	
      case 2:
	res.clauses[i].coef[j] /= a; 
	res.clauses[i].coef[j] *= get_no_pixel(p, x, y, NE);
	break;
	
      case 3:
	res.clauses[i].coef[j] /= a; 
	res.clauses[i].coef[j] *= get_no_pixel(p, x, y, SE);
	break;
	
      case 4:
	res.clauses[i].coef[j] /= a; 
	res.clauses[i].coef[j] *= get_no_pixel(p, x, y, SW);
	break;
      }
    }
  }
  
  /* mise à jour des variables */

  res.lit[0] = get_no_pixel(p, x, y, NW);
  res.lit[1] = get_no_pixel(p, x, y, NE);
  res.lit[2] = get_no_pixel(p, x, y, SW);
  res.lit[3] = get_no_pixel(p, x, y, SE);
  
  return res;
}

int main(int argc, char* argv[]){
  
  grille p = {0, NULL, NULL};
  Fnc res;

  if (argc < 2){
    printf("arguments insuffisant \n", argv[0]);
    printf("veuillez entrer \n");
    printf("une grille \n");
    printf("un fichier de sortie \n");
    
    exit(0);
  }

  p = open(argv[1]);
  //creation d une liste chainée qui contient toutes les cases
  res = modelisation(p);
  //l ecriture de la liste chainée dans un fichier dimacs 
  ecrire_dimacs(argv[2], res);
 //liberation memoire 
  del_fnc(&res);
  return 1;
}
