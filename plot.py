# plot.py - Génération des graphiques à partir des résultats du simulateur
# Utilisation : python plot.py
# Nécessite : pandas, matplotlib (pip install pandas matplotlib)

import pandas as pd
import matplotlib.pyplot as plt
import os

# Charger le fichier CSV des résultats
fichier_csv = "resultats/resultats.csv"

if not os.path.exists(fichier_csv):
    print("Erreur : le fichier", fichier_csv, "n'existe pas.")
    print("Lancez d'abord le simulateur avec 'make run'.")
    exit(1)

df = pd.read_csv(fichier_csv)

# Supprimer les lignes où le temps est -1 (algorithme ignoré pour ce N)
df = df[df["temps_ms"] >= 0]

# Liste des algorithmes et des cas
algorithmes = ["selection", "bulles", "insertion", "shell", "rapide"]
cas = ["aleatoire", "trie", "inverse"]
titres = {
    "aleatoire": "Tableau aléatoire",
    "trie":      "Tableau déjà trié",
    "inverse":   "Tableau trié en ordre inverse"
}
fichiers_sortie = {
    "aleatoire": "resultats/graphe_aleatoire.png",
    "trie":      "resultats/graphe_trie.png",
    "inverse":   "resultats/graphe_inverse.png"
}

# Couleurs pour chaque algorithme
couleurs = {
    "selection": "blue",
    "bulles":    "red",
    "insertion": "green",
    "shell":     "orange",
    "rapide":    "purple"
}

# Générer un graphique pour chaque cas d'entrée
for c in cas:
    donnees_cas = df[df["cas"] == c]

    plt.figure(figsize=(10, 6))

    for algo in algorithmes:
        donnees_algo = donnees_cas[donnees_cas["algorithme"] == algo]

        if donnees_algo.empty:
            continue

        # Trier par N pour avoir des courbes continues
        donnees_algo = donnees_algo.sort_values("N")

        plt.plot(
            donnees_algo["N"],
            donnees_algo["temps_ms"],
            marker="o",
            label=algo,
            color=couleurs[algo],
            linewidth=2
        )

    plt.xscale("log")
    plt.yscale("log")
    plt.xlabel("Taille du tableau N", fontsize=12)
    plt.ylabel("Temps d'exécution (ms)", fontsize=12)
    plt.title("Comparaison des algorithmes de tri\n" + titres[c], fontsize=14)
    plt.legend(fontsize=11)
    plt.grid(True, which="both", linestyle="--", alpha=0.6)
    plt.tight_layout()

    plt.savefig(fichiers_sortie[c], dpi=150)
    print("Graphique sauvegardé :", fichiers_sortie[c])
    plt.close()

print("Tous les graphiques ont été générés dans le dossier 'resultats/'.")
