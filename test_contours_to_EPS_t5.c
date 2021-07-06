#include<stdio.h>
#include<stdlib.h>
#include"contour.h"

/*ce programme prend en entrée une image PBM est en sortie le nom d’un fichier EPS contenant la séquence des contours de l’image */ 
int main(int argc, char **argv){
  Image I;
  Robot r;
  UINT largeur,hauteur; // dimension image
  int err_del; //resultat de la fct suppression fichier tmp

  //lecture fichier image et stockage dans la structure uinformatique I
  I=lire_fichier_image(argv[1]);
  // calcul contours de I et ecriture dans le fichier ensemble de contours tmp
  calcul_contours(I, &r,"tmp_235116032021");
  // calcul dimension
  largeur=largeur_image(I);
  hauteur=hauteur_image(I);
  // création de tous les fichiers eps contenant tout les contours 
  contours_to_EPS(largeur, hauteur, "tmp_235116032021", argv[2]);
  //supression du fichier tmp contenant l'ensemble des contours
  err_del=remove("tmp_235116032021");//err_del=0 si supression reussi sinon =autre chose
  if(err_del){
    fprintf(stderr,"erreur lors de la supression du fichier temporaire dans le programme <test_contours_to_EPS_t5>.\n");
    exit(-2);
  }
  return 0;
}