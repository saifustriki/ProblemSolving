/* tri.h - Déclarations des algorithmes de tri */

#ifndef TRI_H
#define TRI_H

/* Tri par sélection : O(n²) */
void tri_selection(int *tab, int n);

/* Tri à bulles : O(n²) */
void tri_bulles(int *tab, int n);

/* Tri par insertion : O(n²) */
void tri_insertion(int *tab, int n);

/* Tri Shell : meilleur que O(n²) en pratique */
void tri_shell(int *tab, int n);

/* Tri rapide : O(n log n) en moyenne */
void tri_rapide(int *tab, int gauche, int droite);

#endif
