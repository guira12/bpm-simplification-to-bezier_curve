#include<stdio.h>
#include<stdlib.h>
#include "simplification.h"

/*programme prennant 3 arguments, une image pbm en entrée, un fichier eps et un seuil (double)
simplifie tous les contours selon des beziers3 (avec un seuil d)
 et l'ecrit sous format eps en sortie dans le fichier f_eps*/
int main(int argc, char **argv){
  double d;
  UINT tot_B; //nombre de courbes de beziers total
  if(argc!=4){
    printf("erreur nombre d'arguments incorrect\n programme avec 3 arguments\n");
  }
  else{
    d=strtod(argv[3],NULL);
    tot_B=simp_PBM_to_EPS_bezier3(argv[1], argv[2], d);
    printf("NOMBRE TOTAL DE BEZIER 3 APRES SIMPLIFICATION AVEC d=%lf:\n%u\n",d,tot_B);   
  }
  return 0;
}