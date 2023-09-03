#include <stdio.h>
#include "observateur.h"


/* Renvoie l’état initial de l’automate */
Etat initial(){
	Return Init ;
}

/* Fonction de transition de l’automate */
Etat transition(Etat e, Alphabet c){
	switch(e){
		case Init :
		
			switch(c){
				case A : 
					return Erreur ;
				case G 
				case D : 
					return Init;
				case M : 
					return Mes;
				}
		case Mes:
			
			switch(c){
				case A : 
				case G : 
				case D : 
					return Init;
				case M : 
					return Mes;
				}
		case Erreur: 
			return Erreur;
		}
}

/* Renvoie vrai ssi e est un état final de l’automate */
int est_final(Etat e){
return e != Erreur ;
}
