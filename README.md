# Comparaison d'algorithmes de tri en C

**Module :** Problem Solving — Licence en Sciences Informatiques 2ème année  
**Auteurs :** Salmen Zekri & Saifeddine Triki

## Sujet

Simulateur en C comparant 5 algorithmes de tri (sélection, bulles, insertion, Shell, rapide) en mesurant leur temps d'exécution pour des tableaux de taille N croissante (jusqu'à 10 millions d'éléments), sur trois cas : aléatoire, trié, et trié en ordre inverse.

## Compilation

```bash
gcc -O2 -Wall -o simulateur.exe main.c tri.c
```

## Exécution

```bash
mkdir resultats
./simulateur.exe
```

Les résultats s'affichent dans le terminal et sont sauvegardés dans `resultats/resultats.csv`.

## Générer les graphiques

```bash
pip install pandas matplotlib
py plot.py
```

Les courbes sont enregistrées dans `resultats/` (`graphe_aleatoire.png`, `graphe_trie.png`, `graphe_inverse.png`).

## Structure du projet

```
├── tri.h / tri.c       # Implémentations des 5 algorithmes
├── main.c              # Benchmark et export CSV
├── plot.py             # Génération des courbes
├── rapport.md          # Rapport descriptif
└── resultats/          # CSV + graphiques (générés)
```
