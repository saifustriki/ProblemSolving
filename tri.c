/* tri.c - Implémentation des algorithmes de tri */

#include "tri.h"

/* -------------------------------------------------------
 * Tri par sélection
 * Principe : à chaque passage, on cherche le minimum dans
 * la partie non triée et on le place à sa position finale.
 * Complexité : O(n²) dans tous les cas.
 * ------------------------------------------------------- */
void tri_selection(int *tab, int n) {
    int i, j, indice_min, temp;

    for (i = 0; i < n - 1; i++) {
        /* On suppose que le minimum est à la position i */
        indice_min = i;

        /* On parcourt la partie non triée pour trouver le vrai minimum */
        for (j = i + 1; j < n; j++) {
            if (tab[j] < tab[indice_min]) {
                indice_min = j;
            }
        }

        /* On échange le minimum trouvé avec l'élément en position i */
        if (indice_min != i) {
            temp = tab[i];
            tab[i] = tab[indice_min];
            tab[indice_min] = temp;
        }
    }
}

/* -------------------------------------------------------
 * Tri à bulles
 * Principe : on compare chaque paire d'éléments adjacents
 * et on les échange s'ils sont dans le mauvais ordre.
 * On répète jusqu'à ce qu'aucun échange ne soit nécessaire.
 * Complexité : O(n²) en moyenne et dans le pire cas.
 * ------------------------------------------------------- */
void tri_bulles(int *tab, int n) {
    int i, j, temp;
    int echange; /* indicateur pour optimiser : si pas d'échange, c'est trié */

    for (i = 0; i < n - 1; i++) {
        echange = 0;

        /* On "remonte" les grands éléments vers la fin */
        for (j = 0; j < n - 1 - i; j++) {
            if (tab[j] > tab[j + 1]) {
                /* Échange des deux voisins */
                temp = tab[j];
                tab[j] = tab[j + 1];
                tab[j + 1] = temp;
                echange = 1;
            }
        }

        /* Si aucun échange n'a eu lieu, le tableau est déjà trié */
        if (!echange) break;
    }
}

/* -------------------------------------------------------
 * Tri par insertion
 * Principe : on maintient une partie gauche triée, et on
 * insère chaque nouvel élément à sa bonne place en décalant
 * les éléments plus grands vers la droite.
 * Complexité : O(n²) en moyenne, O(n) si déjà trié.
 * ------------------------------------------------------- */
void tri_insertion(int *tab, int n) {
    int i, j, cle;

    for (i = 1; i < n; i++) {
        /* L'élément à insérer dans la partie triée */
        cle = tab[i];
        j = i - 1;

        /* On décale les éléments plus grands que 'cle' vers la droite */
        while (j >= 0 && tab[j] > cle) {
            tab[j + 1] = tab[j];
            j--;
        }

        /* On place 'cle' à sa position correcte */
        tab[j + 1] = cle;
    }
}

/* -------------------------------------------------------
 * Tri Shell
 * Principe : amélioration du tri par insertion. On trie
 * des sous-séquences d'éléments espacés d'un "gap", puis
 * on réduit progressivement le gap jusqu'à 1.
 * Séquence de gaps : n/2, n/4, ..., 1
 * Complexité : dépend de la séquence, meilleure que O(n²).
 * ------------------------------------------------------- */
void tri_shell(int *tab, int n) {
    int gap, i, j, temp;

    /* On commence avec un grand écart et on le réduit de moitié à chaque fois */
    for (gap = n / 2; gap > 0; gap /= 2) {

        /* Tri par insertion avec le gap courant */
        for (i = gap; i < n; i++) {
            temp = tab[i];
            j = i;

            /* Décalage des éléments pour insérer tab[i] au bon endroit */
            while (j >= gap && tab[j - gap] > temp) {
                tab[j] = tab[j - gap];
                j -= gap;
            }

            tab[j] = temp;
        }
    }
}

/* -------------------------------------------------------
 * Tri rapide - fonction d'échange (utilitaire interne)
 * ------------------------------------------------------- */
static void echanger(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

/* -------------------------------------------------------
 * Tri rapide - partition
 * On choisit le dernier élément comme pivot.
 * On place les éléments < pivot à gauche, > pivot à droite.
 * Retourne l'indice final du pivot.
 * ------------------------------------------------------- */
static int partition(int *tab, int gauche, int droite) {
    int pivot = tab[droite]; /* on prend le dernier élément comme pivot */
    int i = gauche - 1;     /* indice du plus grand élément de la partie gauche */
    int j;

    for (j = gauche; j < droite; j++) {
        /* Si l'élément courant est plus petit que le pivot, on l'envoie à gauche */
        if (tab[j] <= pivot) {
            i++;
            echanger(&tab[i], &tab[j]);
        }
    }

    /* On place le pivot à sa position finale */
    echanger(&tab[i + 1], &tab[droite]);
    return i + 1;
}

/* -------------------------------------------------------
 * Tri rapide
 * Principe : on choisit un pivot, on partitionne le tableau
 * en deux parties, puis on trie récursivement chaque partie.
 * Complexité : O(n log n) en moyenne, O(n²) dans le pire cas.
 * ------------------------------------------------------- */
void tri_rapide(int *tab, int gauche, int droite) {
    if (gauche < droite) {
        /* Position finale du pivot après la partition */
        int indice_pivot = partition(tab, gauche, droite);

        /* Tri récursif de la partie gauche (avant le pivot) */
        tri_rapide(tab, gauche, indice_pivot - 1);

        /* Tri récursif de la partie droite (après le pivot) */
        tri_rapide(tab, indice_pivot + 1, droite);
    }
}
