#include <stdio.h>
#include "lecture.h"

int lire_int(char* str, int* pos){
  int n = 0;
  int neg = 0;

  /* recherche d'un chiffre ou d'un - */
  while (str[*pos] != '\0' && (str[*pos] > '9' || str[*pos] < '0')){
    if (str[*pos] == '-'){
      neg = 1;
    }
       
    *pos = *pos+1;
  }

  while (str[*pos] <= '9' && str[*pos] >= '0'){
    n *= 10;
    n += str[*pos] - '0';
    *pos = *pos+1;
  }
  

  if (neg){
    n = -n;
  }

  return n;
}
