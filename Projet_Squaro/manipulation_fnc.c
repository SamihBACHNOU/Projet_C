#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "manipulation_fnc.h"


//alocation memoire pour la clause
void init_clause(Clause* c, int n){
  c->nb_lit = n;
  c->coef = (int*)malloc(n*sizeof(int));
}

//allocation memoire pour la fnc
void init_fnc(Fnc* f, int n, int b){
  int i;

  f->nb_clse = n;
  f->nb_lit = b;
  f->lit = (int*)calloc(b, sizeof(int));
  f->clauses = (Clause*)malloc(n*sizeof(Clause));

  for (i=0; i<n; i++){
    init_clause(&(f->clauses[i]), b);
  }
}

//liberation memoire
void del_clause(Clause* c){
  free (c->coef);
}
//liberation memoire
void del_fnc(Fnc* f){
  int i=0;
  for (i=0; i<f->nb_clse; i++){
    free(f->clauses[i].coef);
  }
  free(f->clauses);
}






