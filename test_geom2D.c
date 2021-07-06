#include<stdio.h>
#include<stdlib.h>
#include "geom2D.h"



int main(int argc, char **argv){
  FILE *f;
  Vecteur v1,v2;
  Point p1,p2,p3,p4;
  double s,x,y; // scalaire et coordonnée 
  Point pAdd,pMinus;
  Vecteur vAdd,vSub,vSc;
  
  //ouverture fichier
  f=fopen(argv[1],"r");
  if(f==NULL){
    fprintf(stderr,"erreur: lecture fichier");
  }
  
  //lecture 4 point et 1 scalaire
  fscanf(f,"%lf%lf",&x,&y);
  p1=set_point(x,y);
  fscanf(f,"%lf%lf",&x,&y);
  p2=set_point(x,y);
  fscanf(f,"%lf%lf",&x,&y);
  p3=set_point(x,y);
  fscanf(f,"%lf%lf",&x,&y);
  p4=set_point(x,y);
  fscanf(f,"%lf",&s);
  
  //affichage des données
  printf("DONNEES INITIALES:\n");
  printf("------------------\n");
  printf("p1=( %f , %f ) ; p2=( %f , %f )\n", (p1.x),(p1.y),(p2.x),(p2.y));
  printf("p3=( %f , %f ) ; p4=( %f , %f )\n", (p3.x),(p3.y),(p4.x),(p4.y));
  printf("s=%f\n______________________________________________________________\n",s);
  
  
  //addition de p1 et p2
  pAdd=add_point(p1,p2);
  printf("addition de p1 et p2: ( %f , %f)\n",pAdd.x,pAdd.y);
  
  //negatif d'un point
  pMinus=minus_point(p3);
  printf("negatif de p3: (%f , %f)\n", pMinus.x, pMinus.y);
  
  //distance entre deux points
  printf("distance entre p3 et p4: %f\n", dist(p3,p4));
  
  //creation de vecteur
  v1=vect_bipoint(p1,p2);
  v2=vect_bipoint(p3,p4);
  
  //affichage coordonee vecteur
  printf("v1=vect(p1p2)=(%f , %f)\n",v1.x,v1.y);
  printf("v2=vect(p3p4)=(%f , %f)\n",v2.x,v2.y);
  
  //addition de deux vecteur
  vAdd=add_vecteur(v1,v2);
  printf("v1 + v2 = (%f , %f)\n",vAdd.x,vAdd.y);
  
  //soustraction vecteur 
  vSub=sub_vecteur(v1,v2);
  printf("v1 - v2 = (%f , %f)\n",vSub.x, vSub.y);
  
  // multiplication d'un vecteur par un scalaire
  vSc=scalar_vecteur(s,v1);
  printf("s * v1 = (%f , %f)\n",vSc.x, vSc.y);
  
  //produit vectoriel
  printf("v1.v2= %f\n",prod_vecteur(v1,v2));
  
  //norme
  printf("||v1|| = %f\n", norm(v1));
  
  
  
  
  
  
  fclose(f);
  return 0;
}