#include<stdio.h>
#include<stdlib.h>
#include "simplification.h"

/*programme prennant 3 arguments, une image pbm en entrée, un fichier eps en sortie et un seuil (double)
simplifie tous les contours (avec un seuil d)
 et l'ecrit sous format eps en sortie dans le fichier f_eps*/
int main(int argc, char **argv){
  double d;
  int nst; //nombre de segments total apres simplification
  if(argc!=4){
    printf("erreur nombre d'arguments incorrect\n programme avec 3 arguments\n");
  }
  else{
    d=strtod(argv[3],NULL);
    nst=simp_PBM_to_EPS(argv[1], argv[2], d);
    printf("NOMBRE TOTAL DE SEGMENTS APRES SIMPLIFICATION AVEC d=%lf:\n%d\n",d,nst);   
  }
  return 0;
  
  
  
  /*
  //test///////////////////////////////////////////
  Contour cnt=creer_liste_Point_vide();
  Point p;
  Liste_Point L;
  

  //creation du contour
  p.x=1;
  p.y=0;
  cnt=ajouter_element_liste_Point(cnt, p);
  
  p.x=2;
  p.y=0;
  cnt=ajouter_element_liste_Point(cnt, p);
  
  p.x=2;
  p.y=1;
  cnt=ajouter_element_liste_Point(cnt, p);
  
  p.x=3;
  p.y=1;
  cnt=ajouter_element_liste_Point(cnt, p);
  
  p.x=4;
  p.y=1;
  cnt=ajouter_element_liste_Point(cnt, p);
  
  p.x=4;
  p.y=2;
  cnt=ajouter_element_liste_Point(cnt, p);
  p.x=4;
  p.y=3;
  cnt=ajouter_element_liste_Point(cnt, p);
  p.x=5;
  p.y=3;
  cnt=ajouter_element_liste_Point(cnt, p);
  p.x=6;
  p.y=3;
  cnt=ajouter_element_liste_Point(cnt, p);
  p.x=6;
  p.y=4;
  cnt=ajouter_element_liste_Point(cnt, p);
  p.x=5;
  p.y=4;
  cnt=ajouter_element_liste_Point(cnt, p);
  p.x=4;
  p.y=4;
  cnt=ajouter_element_liste_Point(cnt, p);
  p.x=3;
  p.y=4;
  cnt=ajouter_element_liste_Point(cnt, p);
  p.x=3;
  p.y=3;
  cnt=ajouter_element_liste_Point(cnt, p);
  p.x=3;
  p.y=2;
  cnt=ajouter_element_liste_Point(cnt, p);
  p.x=2;
  p.y=2;
  cnt=ajouter_element_liste_Point(cnt, p);
  p.x=2;
  p.y=3;
  cnt=ajouter_element_liste_Point(cnt, p);
  p.x=2;
  p.y=4;
  cnt=ajouter_element_liste_Point(cnt, p);
  p.x=1;
  p.y=4;
  cnt=ajouter_element_liste_Point(cnt, p);
  p.x=1;
  p.y=3;
  cnt=ajouter_element_liste_Point(cnt, p);
  p.x=0;
  p.y=3;
  cnt=ajouter_element_liste_Point(cnt, p);
  p.x=0;
  p.y=2;
  cnt=ajouter_element_liste_Point(cnt, p);
  p.x=0;
  p.y=1;
  cnt=ajouter_element_liste_Point(cnt, p);
  p.x=1;
  p.y=1;
  cnt=ajouter_element_liste_Point(cnt, p);
  p.x=1;
  p.y=0;
  cnt=ajouter_element_liste_Point(cnt, p);
  //affichage Liste_Point à l'ecran, si vide affichage message liste vide
  printf("taille liste: %u\n",cnt.taille);
  affichage_Liste_Point(cnt);

  
  
  L=simplification_DP(cnt, 0, 24, 0.9);

  //affichage Liste_Point à l'ecran, si vide affichage message liste vide
  printf("taille liste: %u\n",L.taille);
  affichage_Liste_Point(L);
  

  return 0;
  */
 
}