#include<stdio.h>
#include<stdlib.h>
#include "geom2D.h"


Point set_point(double x, double y){
  Point p;
  /*p=(Point *)malloc(2*sizeof(double));
  if(p==(Point *)NULL){
    printf(stderr,"erreur:alocation memoire pour un point dans geom2D");
    exit 1;
  }*/
  p.x=x;
  p.y=y;
  return p;
}


Point add_point(Point P1,Point P2){
  double x,y;
  Point p;
  x=(P1.x)+(P2.x);
  y=(P1.y)+(P2.y);
  p=set_point(x,y);
  return p;
}

Point minus_point(Point p){
  Point mp;
  mp.x=-(p.x);
  mp.y=-(p.y);
  return mp;
}


/*distance entre deux points*/
double dist(Point p1, Point p2){
  Point p22=minus_point(p2);                       //p22 = {-(p2.x),-(p2.y)}
  Point pf=add_point(p1,p22);
  return sqrt((pf.x)*(pf.x) + (pf.y)*(pf.y));
  
}

Vecteur vect_bipoint(Point p1, Point p2){
  Vecteur v;
  double x,y;
  x=(p2.x) - (p1.x);
  y=(p2.y) - (p1.y);
  v.x=x;
  v.y=y;
  return v;
}

Vecteur add_vecteur(Vecteur v1, Vecteur v2){
  Vecteur v={v1.x + v2.x , v1.y + v2.y};
  return v;
}

/*sustraction de vecteur, resultat v1-v2*/
Vecteur sub_vecteur(Vecteur v1, Vecteur v2){
  Vecteur v={v1.x - v2.x , v1.y - v2.y};
  return v;
}


Vecteur scalar_vecteur(double a, Vecteur v){
  Vecteur ve={a*(v.x) , a*(v.y)};
  return ve;
}

/*produit scalaire entre deux vecteurs*/
double  prod_vecteur(Vecteur v1, Vecteur v2){
  double s=(v1.x)*(v2.x) + (v1.y)*(v2.y);
  return s;
}

/*norme d'un vecteur*/
double norm(Vecteur v){
  return sqrt(prod_vecteur(v,v));
}

/*fct qui calcul la distance entre le point P et le segment [AB],
et renvoie la cette distance*/
double distance_point_segment(Point P, Point A, Point B){
  Point Q; // Q etant  le point le plus proche de P et appartenant à la droite (AB)
  Vecteur AP,AB; // deux vecteurs
  double lambda; // vec(OQ) = vec(OA)+ lambda*vec(AB)
  
  if(A.x==B.x && A.y==B.y){   // si A=B alors distance=PA=PB
    return dist(P, A);
  }
  else{         // si A!=B 
    AP=vect_bipoint(A, P);     // calcul vec(AP)
    AB=vect_bipoint(A, B);      // calcul vec(AB)
    lambda=prod_vecteur(AP, AB) / prod_vecteur(AB, AB);
    if(lambda<0){          //si lambda <0
      return dist(A, P);   //alors distance=AP
    }
    else if(lambda>1){     //si lambda>1
      return dist(B, P);   // alors distance=BP
    }
    else{                   // si 0<=lambda<=1
      Q=add_vecteur(A, scalar_vecteur(lambda, sub_vecteur(B, A)));    //   alors le point Q=A+lambda*(B-A)
      return dist(Q, P);      // et la distance=QP
    }
  }
}

/*
fct qui prend en argument une courbe de bezier 2 et un parametre t 
et calcul le point de la courbe C(t) et le renvoie*/
Point bezier2(Bezier2 B, double t){
  Point Ct;  // point de la courbe de bezier B avec le parametre t
  Ct= scalar_vecteur((1-t)*(1-t), B.C0); // Ct <- (1-t)^2  *  C0
  Ct=add_point(Ct, scalar_vecteur(2*t*(1-t), B.C1));  //Ct <- [(1-t)^2 * C0] +  [2t(1-t)*C1] 
  Ct=add_point(Ct, scalar_vecteur(t*t, B.C2));  //Ct <- [(1-t)^2 * C0] +  [2t(1-t)*C1] + [t^2 * C2]
  return Ct;
}

/*fct qui prend on argument un point P, une courbe de bezier B, et un parametre ti,
calcul et renvoie la distance entre le point P et le point de la courbe B ayant comme paramètre ti*/
double distance_point_bezier2(Point P, Bezier2 B, double t){
  Point Ct;  // point de la courbe de bezier B avec le parametre t
  
  Ct=bezier2(B, t);
  
  return dist(P, Ct); // retourner la distance entre le point P et Cti  
}

/*
fct prend en argument une courbe de bezier de degré 2, 
et renvoie la meme courbe eleve au degré 3*/
Bezier3 elevation_degre(Bezier2 B2){
  Bezier3 B3;
  Point deuxC1;
  B3.C0=B2.C0;  //B3.C0 <- C0
  deuxC1=scalar_vecteur(2, B2.C1); // calcul de 2*C1
  B3.C1=scalar_vecteur( 1.0/3.0 , add_point(deuxC1,B2.C0));   //B3.C1 <- (2*C1 +C0)/3
  B3.C2=scalar_vecteur( 1.0/3.0 , add_point(deuxC1,B2.C2));   //B3.C2 <- (2*C1 +C2)/3
  B3.C3=B2.C2;  //B3.C3 <- C2
  
  return B3;
}

/*
fct qui prend en argument une courbe de bezier 3 et un parametre t 
et calcul le point de la courbe C(t) et le renvoie*/
Point bezier3(Bezier3 B, double t){
  Point Ct; // point de la courbe de bezier B avec le parametre t
  Ct=scalar_vecteur((1-t)*(1-t)*(1-t), B.C0);
  Ct=add_point(Ct,scalar_vecteur(3*t*(1-t)*(1-t), B.C1));
  Ct=add_point(Ct, scalar_vecteur(3*t*t*(1-t), B.C2));
  Ct=add_point(Ct, scalar_vecteur(t*t*t, B.C3));
  return Ct;
}




/*fct qui prend on argument un point P, une courbe de bezier 3 B, et un parametre t,
calcul et renvoie la distance entre le point P et le point de la courbe B ayant comme paramètre t*/
double distance_point_bezier3(Point P, Bezier3 B, double t){
  Point Ct;  // point de la courbe de bezier3 B avec le parametre t
  
  Ct=bezier3(B, t);
  
  return dist(P, Ct); // retourner la distance entre le point P et Ct  
}




