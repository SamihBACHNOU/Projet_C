#ifndef MANIPULATION_FNC
#define MANIPULATION_FNC

#include <string.h>
#include <math.h>


/* contient le nombre de littéraux (nb_lit) et les coef associés literaux qui sont des coefi*/
typedef struct{
  int nb_lit;
  int* coef;
}Clause;

/*le nombre de clauses le nombre de litéraux un tableau de literaux et un tableau de clauses*/

typedef struct{
  int nb_clse;
  int nb_lit;
  int* lit;
  Clause* clauses;
}Fnc;

//allocation memoire pour une clause
void init_clause(Clause*, int);
//allocation memoire pour une fnc
void init_fnc(Fnc*, int, int);
////liberation memoire
void del_clause(Clause*);
void del_fnc(Fnc*);






#endif
