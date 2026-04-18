/* main.c - Programme principal du simulateur de tri
 * Ce programme mesure le temps d'exécution de 5 algorithmes de tri
 * pour différentes tailles de tableau et différents types de données.
 * Les résultats sont affichés à l'écran et enregistrés dans un fichier CSV.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "tri.h"

/* Seuil à partir duquel on ne teste plus les algorithmes en O(n²)
 * car ils deviennent trop lents (plusieurs minutes d'attente). */
#define SEUIL_LENT 100000

/* Seuil spécifique pour le tri rapide sur tableaux triés/inverses.
 * Avec pivot = dernier élément, le tri rapide dégénère en O(n²) sur ces cas,
 * ce qui provoque un débordement de pile (stack overflow) dès ~10 000 appels récursifs. */
#define SEUIL_RAPIDE_DEGENERE 5000

/* Remplir le tableau avec des valeurs aléatoires */
void remplir_aleatoire(int *tab, int n) {
    int i;
    for (i = 0; i < n; i++) {
        tab[i] = rand() % (n * 10);
    }
}

/* Remplir le tableau dans l'ordre croissant (déjà trié) */
void remplir_trie(int *tab, int n) {
    int i;
    for (i = 0; i < n; i++) {
        tab[i] = i;
    }
}

/* Remplir le tableau dans l'ordre décroissant (trié à l'envers) */
void remplir_inverse(int *tab, int n) {
    int i;
    for (i = 0; i < n; i++) {
        tab[i] = n - 1 - i;
    }
}

/* Mesurer le temps d'exécution d'un algorithme de tri en millisecondes.
 * On passe une copie du tableau de base pour ne pas modifier l'original.
 * Retourne -1.0 si l'algorithme est ignoré pour ce N. */
double mesurer_temps(void (*fonction_tri)(int *, int), int *base, int n) {
    int *copie;
    clock_t debut, fin;
    double duree_ms;

    /* Allouer une copie du tableau */
    copie = (int *) malloc(n * sizeof(int));
    if (copie == NULL) {
        fprintf(stderr, "Erreur : allocation mémoire impossible pour n=%d\n", n);
        return -1.0;
    }

    memcpy(copie, base, n * sizeof(int));

    /* Chronométrage */
    debut = clock();
    fonction_tri(copie, n);
    fin = clock();

    duree_ms = (double)(fin - debut) / CLOCKS_PER_SEC * 1000.0;

    free(copie);
    return duree_ms;
}

/* Version spéciale pour le tri rapide (signature différente : gauche, droite) */
double mesurer_temps_rapide(int *base, int n) {
    int *copie;
    clock_t debut, fin;
    double duree_ms;

    copie = (int *) malloc(n * sizeof(int));
    if (copie == NULL) {
        fprintf(stderr, "Erreur : allocation mémoire impossible pour n=%d\n", n);
        return -1.0;
    }

    memcpy(copie, base, n * sizeof(int));

    debut = clock();
    tri_rapide(copie, 0, n - 1);
    fin = clock();

    duree_ms = (double)(fin - debut) / CLOCKS_PER_SEC * 1000.0;

    free(copie);
    return duree_ms;
}

int main() {
    /* Les différentes tailles de tableau à tester */
    int valeurs_N[] = {1000, 5000, 10000, 50000, 100000,
                       500000, 1000000, 5000000, 10000000};
    int nb_valeurs = sizeof(valeurs_N) / sizeof(valeurs_N[0]);

    int *tab_base;
    double t;
    int i, n;
    FILE *fichier_csv;

    /* Initialiser le générateur de nombres aléatoires */
    srand(42); /* graine fixe pour reproduire les mêmes résultats */

    /* Créer le fichier CSV pour sauvegarder les résultats */
    fichier_csv = fopen("resultats/resultats.csv", "w");
    if (fichier_csv == NULL) {
        fprintf(stderr, "Erreur : impossible de créer le fichier CSV.\n");
        fprintf(stderr, "Vérifiez que le dossier 'resultats' existe.\n");
        return 1;
    }

    /* En-tête du CSV */
    fprintf(fichier_csv, "N,algorithme,cas,temps_ms\n");

    printf("========================================================\n");
    printf("    Simulateur de comparaison d'algorithmes de tri\n");
    printf("========================================================\n");
    printf("%-10s | %-10s | %-10s | %s\n", "N", "Algorithme", "Cas", "Temps (ms)");
    printf("--------------------------------------------------------\n");

    /* Boucle principale sur toutes les tailles N */
    for (i = 0; i < nb_valeurs; i++) {
        n = valeurs_N[i];

        /* Allouer le tableau de base */
        tab_base = (int *) malloc(n * sizeof(int));
        if (tab_base == NULL) {
            fprintf(stderr, "Erreur : impossible d'allouer %d entiers.\n", n);
            fclose(fichier_csv);
            return 1;
        }

        /* --- CAS 1 : tableau aléatoire --- */
        remplir_aleatoire(tab_base, n);

        /* Tri sélection */
        if (n <= SEUIL_LENT) {
            t = mesurer_temps(tri_selection, tab_base, n);
        } else {
            t = -1.0; /* trop lent, on ignore */
        }
        printf("%-10d | %-10s | %-10s | %.2f ms\n", n, "selection", "aleatoire", t);
        fprintf(fichier_csv, "%d,selection,aleatoire,%.2f\n", n, t);

        /* Tri à bulles */
        if (n <= SEUIL_LENT) {
            t = mesurer_temps(tri_bulles, tab_base, n);
        } else {
            t = -1.0;
        }
        printf("%-10d | %-10s | %-10s | %.2f ms\n", n, "bulles", "aleatoire", t);
        fprintf(fichier_csv, "%d,bulles,aleatoire,%.2f\n", n, t);

        /* Tri par insertion */
        if (n <= SEUIL_LENT) {
            t = mesurer_temps(tri_insertion, tab_base, n);
        } else {
            t = -1.0;
        }
        printf("%-10d | %-10s | %-10s | %.2f ms\n", n, "insertion", "aleatoire", t);
        fprintf(fichier_csv, "%d,insertion,aleatoire,%.2f\n", n, t);

        /* Tri Shell */
        t = mesurer_temps(tri_shell, tab_base, n);
        printf("%-10d | %-10s | %-10s | %.2f ms\n", n, "shell", "aleatoire", t);
        fprintf(fichier_csv, "%d,shell,aleatoire,%.2f\n", n, t);

        /* Tri rapide */
        t = mesurer_temps_rapide(tab_base, n);
        printf("%-10d | %-10s | %-10s | %.2f ms\n", n, "rapide", "aleatoire", t);
        fprintf(fichier_csv, "%d,rapide,aleatoire,%.2f\n", n, t);

        /* --- CAS 2 : tableau déjà trié --- */
        remplir_trie(tab_base, n);

        if (n <= SEUIL_LENT) {
            t = mesurer_temps(tri_selection, tab_base, n);
        } else { t = -1.0; }
        printf("%-10d | %-10s | %-10s | %.2f ms\n", n, "selection", "trie", t);
        fprintf(fichier_csv, "%d,selection,trie,%.2f\n", n, t);

        if (n <= SEUIL_LENT) {
            t = mesurer_temps(tri_bulles, tab_base, n);
        } else { t = -1.0; }
        printf("%-10d | %-10s | %-10s | %.2f ms\n", n, "bulles", "trie", t);
        fprintf(fichier_csv, "%d,bulles,trie,%.2f\n", n, t);

        if (n <= SEUIL_LENT) {
            t = mesurer_temps(tri_insertion, tab_base, n);
        } else { t = -1.0; }
        printf("%-10d | %-10s | %-10s | %.2f ms\n", n, "insertion", "trie", t);
        fprintf(fichier_csv, "%d,insertion,trie,%.2f\n", n, t);

        t = mesurer_temps(tri_shell, tab_base, n);
        printf("%-10d | %-10s | %-10s | %.2f ms\n", n, "shell", "trie", t);
        fprintf(fichier_csv, "%d,shell,trie,%.2f\n", n, t);

        /* Le tri rapide dégénère en O(n²) sur tableau trié (pivot = dernier élément),
         * ce qui cause un débordement de pile pour les grands N. Seuil plus bas. */
        if (n <= SEUIL_RAPIDE_DEGENERE) {
            t = mesurer_temps_rapide(tab_base, n);
        } else { t = -1.0; }
        printf("%-10d | %-10s | %-10s | %.2f ms\n", n, "rapide", "trie", t);
        fprintf(fichier_csv, "%d,rapide,trie,%.2f\n", n, t);

        /* --- CAS 3 : tableau trié en ordre inverse --- */
        remplir_inverse(tab_base, n);

        if (n <= SEUIL_LENT) {
            t = mesurer_temps(tri_selection, tab_base, n);
        } else { t = -1.0; }
        printf("%-10d | %-10s | %-10s | %.2f ms\n", n, "selection", "inverse", t);
        fprintf(fichier_csv, "%d,selection,inverse,%.2f\n", n, t);

        if (n <= SEUIL_LENT) {
            t = mesurer_temps(tri_bulles, tab_base, n);
        } else { t = -1.0; }
        printf("%-10d | %-10s | %-10s | %.2f ms\n", n, "bulles", "inverse", t);
        fprintf(fichier_csv, "%d,bulles,inverse,%.2f\n", n, t);

        if (n <= SEUIL_LENT) {
            t = mesurer_temps(tri_insertion, tab_base, n);
        } else { t = -1.0; }
        printf("%-10d | %-10s | %-10s | %.2f ms\n", n, "insertion", "inverse", t);
        fprintf(fichier_csv, "%d,insertion,inverse,%.2f\n", n, t);

        t = mesurer_temps(tri_shell, tab_base, n);
        printf("%-10d | %-10s | %-10s | %.2f ms\n", n, "shell", "inverse", t);
        fprintf(fichier_csv, "%d,shell,inverse,%.2f\n", n, t);

        /* Même problème que pour le cas trié : dégénère en O(n²), seuil plus bas. */
        if (n <= SEUIL_RAPIDE_DEGENERE) {
            t = mesurer_temps_rapide(tab_base, n);
        } else { t = -1.0; }
        printf("%-10d | %-10s | %-10s | %.2f ms\n", n, "rapide", "inverse", t);
        fprintf(fichier_csv, "%d,rapide,inverse,%.2f\n", n, t);

        printf("--------------------------------------------------------\n");

        free(tab_base);
    }

    fclose(fichier_csv);

    printf("\nRésultats sauvegardés dans resultats/resultats.csv\n");
    printf("Lancez 'python plot.py' pour générer les graphiques.\n");

    return 0;
}
