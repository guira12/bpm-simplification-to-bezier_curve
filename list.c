#include<stdio.h>
#include<stdlib.h>
#include "list.h"


/*Creer une cellule de liste avec l'element v renvoie le pointeur 
sur la cellule de liste cree la fct s'arrete si la creation n'a pas pu se faire*/
Cellule_Liste_Point *creer_element_liste_Point(Point v){
  Cellule_Liste_Point *el;
  el=(Cellule_Liste_Point *)malloc(sizeof(Cellule_Liste_Point));
  if(el==NULL){
    fprintf(stderr,"creer_element_liste_Point : allocation impossible \n");
    exit(-1);
  }
  el->data=v;
  el->suiv=NULL;
  return el;
}

/*creer une liste vide*/
Liste_Point creer_liste_Point_vide(){
  Liste_Point L={0, NULL, NULL};
  return L;
}


/*ajouter l'element e en fin de la liste L, renvoie la liste L modifiée */
Liste_Point ajouter_element_liste_Point(Liste_Point L, Point e){
  Cellule_Liste_Point *el;
  
  el=creer_element_liste_Point(e);
  if(L.taille==0){
    L.first=L.last=el;    // premier et dernier element de la liste a la fois
  }
  else{
    L.last->suiv=el;
    L.last=el;
  }
  L.taille++;
  return L;
}


/*supression de tous les elements de la liste, renvoie la liste L vide*/
Liste_Point supprimer_liste_Point(Liste_Point L){
  Cellule_Liste_Point *el=L.first;
  while(el!=NULL){
    Cellule_Liste_Point *suiv=el->suiv;
    free(el);
    el=suiv;
  }
  L.first=L.last=NULL;
  L.taille=0;
  return L;
}


/*concatène L2 a la suite de L1, renvoie la liste L1 modifiée*/
Liste_Point concatener_liste_Point(Liste_Point L1,Liste_Point L2){
  //cas ou l'un des deux listes est vide
  if(L1.taille==0)
    return L2;
  if(L2.taille==0)
    return L1;
  
  //cas ou les deux listes sont non vides
  L1.last->suiv=L2.first; // lien entre L1.last et L2.first
  L1.last =L2.last;      //le dernier element de L1 est celui de L2
  L1.taille+=L2.taille;  //nouvelle taille pour L1
  return L1;
}

/*creer une sequence de points sous forme d'un tableau de points
 a partir de la liste de points L*/
Tableau_Point sequence_points_liste_vers_tableau(Liste_Point L){
  Tableau_Point T;
  
  T.taille=L.taille;  //taille de T = taille de L
  
  T.tab=malloc(sizeof(Point)*T.taille);    //allocation dynamique du tableau de Point
  if(T.tab==NULL)                      // allocation impossible : arret diu programme avec un message
  {
    fprintf(stderr,"sequence_points_liste_vers_tableau : ");
    fprintf(stderr,"allocation impossible \n ");
    exit(-1);
  }
  
  /*remplire de tableau de points T en parcourant la liste L*/
  int k=0;   //indice de l'element dans T.tab
  Cellule_Liste_Point *el=L.first;    //pointeur sur l'elemnt dans L
  
  while(el!=NULL){
    T.tab[k]=el->data;
    k++;  //incrementer k
    el=el->suiv;   //passer à l'élement suivant dans la liste chainee
  }
  return T;
}

//affichage Liste_Point à l'ecran, si vide affichage message liste vide
void affichage_Liste_Point(Liste_Point L){
  Cellule_Liste_Point *el=L.first;
  
  if(el==NULL){
    printf("liste vide\n");
  }
  else{
  printf("la liste contient les points suivants:\n");
    while(el!=NULL){
      printf("( %lf , %lf )\n", el->data.x, el->data.y);
      el=el->suiv;     
    }
  }
}
