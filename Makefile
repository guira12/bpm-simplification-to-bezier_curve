#############################################################################
# Fichier Makefile 
# UE MAP401 - DLST - UGA - 2020/2021
#############################################################################
# utilisation des variables internes $@ $< $^ $*
# $@ : correspond au nom de la cible
# $< : correspond au nom de la premiere dependance
# $^ : correspond à toutes les dépendances
# $* : correspond au nom du fichier sans extension 
#       (dans les regles generiques uniquement)
#############################################################################
# information sur la regle executee avec la commande @echo
# (une commande commancant par @ n'est pas affichee a l'ecran)
#############################################################################


#############################################################################
# definition des variables locales
#############################################################################

# compilateur C
CC = clang

# chemin d'acces aux librairies (interfaces)
INCDIR = .

# chemin d'acces aux librairies (binaires)
LIBDIR = .

# options pour l'édition des liens
LDOPTS = -L$(LIBDIR) -lm

# options pour la recherche des fichiers .o et .h
INCLUDEOPTS = -I$(INCDIR)

# options de compilation
COMPILOPTS = -g -Wall $(INCLUDEOPTS)

# liste des executables
EXECUTABLES = test_simp_contours_to_EPS_bezier3_t7 test_p2_t7 test_simp_contours_to_EPS_bezier2_t7 test_c_t7 test_b_1_t7 test_a_n_1_t7        test_simp_PBM_to_EPS_t6 test_distance_point_segment test_contours_to_EPS_t5 test_cal_contours test_eps_t4 test_contour_ecran test_image test_t3_p2    test_geom2D 


#############################################################################
# definition des regles
#############################################################################

########################################################
# la règle par défaut
all : $(EXECUTABLES)

########################################################
# regle generique : 
#  remplace les regles de compilation separee de la forme
#	module.o : module.c module.h
#		$(CC) -c $(COMPILOPTS) module.c
%.o : %.c %.h
	@echo ""
	@echo "---------------------------------------------"
	@echo "Compilation du module "$*
	@echo "---------------------------------------------"
	$(CC) -c $(COMPILOPTS) $<

########################################################
# regles explicites de compilation separee de modules
# n'ayant pas de fichier .h ET/OU dependant d'autres modules
image.o : image.c image.h types_macros.h
	@echo ""
	@echo "---------------------------------------------"
	@echo "Compilation du module image"
	@echo "---------------------------------------------"
	$(CC) -c $(COMPILOPTS) $<

test_image.o : test_image.c image.h 
	@echo ""
	@echo "---------------------------------------------"
	@echo "Compilation du module test_image"
	@echo "---------------------------------------------"
	$(CC) -c $(COMPILOPTS) $<
 
geom2D.o : geom2D.c geom2D.h

test_geom2D.o : test_geom2D.c geom2D.h

contour.o : contour.c contour.h image.h geom2D.h list.h

list.o : list.c list.h geom2D.h

test_contour_ecran.o : test_contour_ecran.c contour.h image.h types_macros.h geom2D.h list.h

test_t3_p2.o : test_t3_p2.c contour.h image.h types_macros.h geom2D.h list.h

test_eps_t4.o : test_eps_t4.c contour.h image.h types_macros.h geom2D.h list.h

test_cal_contours.o : test_cal_contours.c contour.h image.h types_macros.h geom2D.h list.h

test_contours_to_EPS_t5.o : test_contours_to_EPS_t5.c contour.h image.h types_macros.h geom2D.h list.h

test_distance_point_segment.o : test_distance_point_segment.c geom2D.h

test_simp_PBM_to_EPS_t6.o : test_simp_PBM_to_EPS_t6.c simplification.h contour.h image.h types_macros.h geom2D.h list.h

test_a_n_1_t7.o : test_a_n_1_t7.c simplification.h contour.h image.h types_macros.h geom2D.h list.h

test_b_1_t7.o : test_b_1_t7.c simplification.h contour.h image.h types_macros.h geom2D.h list.h

test_c_t7.o : test_c_t7.c simplification.h contour.h image.h types_macros.h geom2D.h list.h

test_simp_contours_to_EPS_bezier2_t7.o : test_simp_contours_to_EPS_bezier2_t7.c simplification.h contour.h image.h types_macros.h geom2D.h list.h

test_p2_t7.o : test_p2_t7.c simplification.h contour.h image.h types_macros.h geom2D.h list.h

test_simp_contours_to_EPS_bezier3_t7.o : test_simp_contours_to_EPS_bezier3_t7.c simplification.h contour.h image.h types_macros.h geom2D.h list.h

########################################################
# regles explicites de creation des executables

test_image : test_image.o image.o 
	@echo ""
	@echo "---------------------------------------------"
	@echo "Creation de l'executable "$@
	@echo "---------------------------------------------"
	$(CC) $^ $(LDOPTS) -o $@

test_geom2D : test_geom2D.o geom2D.o
	@echo ""
	@echo "---------------------------------------------"
	@echo "Creation de l'executable "$@
	@echo "---------------------------------------------"
	$(CC) $^ $(LDOPTS) -o $@

test_contour_ecran : test_contour_ecran.o contour.o image.o geom2D.o list.o
	@echo ""
	@echo "---------------------------------------------"
	@echo "Creation de l'executable "$@
	@echo "---------------------------------------------"
	$(CC) $^ $(LDOPTS) -o $@

test_t3_p2 : test_t3_p2.o contour.o image.o geom2D.o list.o
	@echo ""
	@echo "---------------------------------------------"
	@echo "Creation de l'executable "$@
	@echo "---------------------------------------------"
	$(CC) $^ $(LDOPTS) -o $@

test_eps_t4 : test_eps_t4.o contour.o image.o geom2D.o list.o
	@echo ""
	@echo "---------------------------------------------"
	@echo "Creation de l'executable "$@
	@echo "---------------------------------------------"
	$(CC) $^ $(LDOPTS) -o $@

test_cal_contours : test_cal_contours.o contour.o image.o geom2D.o list.o
	@echo ""
	@echo "---------------------------------------------"
	@echo "Creation de l'executable "$@
	@echo "---------------------------------------------"
	$(CC) $^ $(LDOPTS) -o $@

test_contours_to_EPS_t5 : test_contours_to_EPS_t5.o contour.o image.o geom2D.o list.o
	@echo ""
	@echo "---------------------------------------------"
	@echo "Creation de l'executable "$@
	@echo "---------------------------------------------"
	$(CC) $^ $(LDOPTS) -o $@

test_distance_point_segment : test_distance_point_segment.o geom2D.o
	@echo ""
	@echo "---------------------------------------------"
	@echo "Creation de l'executable "$@
	@echo "---------------------------------------------"
	$(CC) $^ $(LDOPTS) -o $@

test_simp_PBM_to_EPS_t6 : test_simp_PBM_to_EPS_t6.o simplification.o contour.o image.o geom2D.o list.o
	@echo ""
	@echo "---------------------------------------------"
	@echo "Creation de l'executable "$@
	@echo "---------------------------------------------"
	$(CC) $^ $(LDOPTS) -o $@

test_a_n_1_t7 : test_a_n_1_t7.o simplification.o contour.o image.o geom2D.o list.o
	@echo ""
	@echo "---------------------------------------------"
	@echo "Creation de l'executable "$@
	@echo "---------------------------------------------"
	$(CC) $^ $(LDOPTS) -o $@

test_b_1_t7 : test_b_1_t7.o simplification.o contour.o image.o geom2D.o list.o
	@echo ""
	@echo "---------------------------------------------"
	@echo "Creation de l'executable "$@
	@echo "---------------------------------------------"
	$(CC) $^ $(LDOPTS) -o $@

test_c_t7 : test_c_t7.o simplification.o contour.o image.o geom2D.o list.o
	@echo ""
	@echo "---------------------------------------------"
	@echo "Creation de l'executable "$@
	@echo "---------------------------------------------"
	$(CC) $^ $(LDOPTS) -o $@

test_simp_contours_to_EPS_bezier2_t7 : test_simp_contours_to_EPS_bezier2_t7.o simplification.o contour.o image.o geom2D.o list.o
	@echo ""
	@echo "---------------------------------------------"
	@echo "Creation de l'executable "$@
	@echo "---------------------------------------------"
	$(CC) $^ $(LDOPTS) -o $@

test_p2_t7 : test_p2_t7.o simplification.o contour.o image.o geom2D.o list.o
	@echo ""
	@echo "---------------------------------------------"
	@echo "Creation de l'executable "$@
	@echo "---------------------------------------------"
	$(CC) $^ $(LDOPTS) -o $@

test_simp_contours_to_EPS_bezier3_t7 : test_simp_contours_to_EPS_bezier3_t7.o simplification.o contour.o image.o geom2D.o list.o
	@echo ""
	@echo "---------------------------------------------"
	@echo "Creation de l'executable "$@
	@echo "---------------------------------------------"
	$(CC) $^ $(LDOPTS) -o $@

# regle pour "nettoyer" le répertoire
clean:
	rm -fR $(EXECUTABLES) *.o 
