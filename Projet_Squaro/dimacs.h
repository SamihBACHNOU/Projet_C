#ifndef DEF_DIMACS
#define DEF_DIMACS

#include "manipulation_fnc.h"
#include "lecture.h"

//lit un fichier dimacs et genere une fnc
Fnc lecture_dimacs(char* nf);
//ecrit les fnc generer dans un fichier dimacs
int ecrire_dimacs(char* nf, Fnc fnc);
//insere un literale dans une clause(tableau de literaux) en position n
void inserer_literau(Fnc* fnc, int a, int* n); 
int comparer (const void * a, const void * b);
#endif
