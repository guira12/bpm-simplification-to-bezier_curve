#include<stdio.h>
#include<stdlib.h>
#include "contour.h"


/*ce programme prend 2 ou 3  argument une image .pbm,  un fichier1.txt  et (un fichier2.txt)
dans le fichier1.txt il ecrit le contour de l'image (format:nombre de contours(ici =1), nombre de points, et les points)    SI 2 ARGUMENT 
dans le fichier2.txt il ecrit le nom de l'image ses dimension et le nombre de segment du contour calculé (attention ecriture dans fichier2.txt avec append)  SI TROIS ARGUMENT EFFECTUENT TOUTE LES OPERATION*/


int main(int argc, char **argv){
  
  Image I;
  Robot r;
  Point pi;
  Contour C;
  unsigned int nb_segment;
  
  if(argc!=3 && argc!=4){
    fprintf(stderr, "erreur nombre d'argument incorrecte, entrer 2 ou 3 argument pour ce programme\n");
    exit(-1);
  }
  
  //lecture fichier image et stockage dans la structure uinformatique I
  I=lire_fichier_image(argv[1]);
  //recherche du point de depart
  pi=point_depart(I);
  //initialisation robot et affichage contour
  C=calcul_contour(I, &r, pi);
  
  
  //ecriture du fichier un contenant le contour de l'image
  ecrire_contour_inFile(C, argv[2] );
  
  
  /*si ajout des donnée (nom image, dimention image et nombre de segment du contour ) souhaité,
   il faut ajouter un troisieme argument au programme le nom du fichier ou ces données seront ecritent*/
  if(argc==4){ 
    FILE *f;      //descripteur fichier2.txt
    //ouverture fichier en ecriture w+ et test si succes ouverture
    f=fopen(argv[3],"a");
    if(f==NULL){
      fprintf(stderr,"erreur ouverture fichier en ecriture w+");
      exit(-1);
    }
    
    fprintf(f,"%s\n",argv[1]); // ecriture nom image
    fprintf(f,"largeur: %d  hauteur: %d\n", largeur_image(I), hauteur_image(I));    //ecriture largeur et hauteur image
    nb_segment=C.taille-1;       //nombre de segment= nombre de points du contour moin 1
    fprintf(f,"nb segment: %d", nb_segment);   // ecriture nembre de segment du contour
    fprintf(f,"\n\n\n");  //espacement pour lisibilité
    fclose(f);
  }
  
  supprimer_liste_Point(C);    //liberation de la memoire
  return 0;                   
}