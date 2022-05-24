# in104

# PRESENTATION DU PROJET 

Création d'une base de données utilisables à l'aide de sons musicaux, avec un échantillonnage des sons, puis une stft, puis des calculs de moyennes 
et d'écarts-types permettant de représenter cette stft (tableau magnitude). 
Puis, on génère avec un classifieur une matrice et un vecteur (W et b) permettant de calculer pour chaque son une distance à chaque genre musical.
La distance la plus grande donne le genre prédit (resultat). 

# TACHES EFFECTUEES 
1) Adapter un “main” en une fonction “double* audioread” 
- Lecture du fichier issu de la base de données sauvegardée
- Création d’un tableau wav_data réunissant les résultats affichés sur le terminal. 

2) Créer un “main.c” permettant de calculer le fichier feature.csv u
- Utilisation de “stft” avec pour entrée la sortie de “audio_read”
- Calculs de la moyenne et de l’écart-type de chaque “colonne” de magnitude issu de stft.
- Ecriture des résultats dans un fichier au format csv

3) Création du fichier probas.c pour construire feature.csv
- Calcul de la moyenne d’un vecteur
- Calcul écart-type d’un vecteur 

 4) Classifieur du son avec le fichier classifier.py
- Lecture d’un fichier test avec “audio_read”
- Création de magnitude (résultat de la stft)
- Calcul du fichier feature.csv (moyennes et écart-type)
- Création des fichiers w.csv et b.csv 

5) Création du fichier utils.c 
- Produit matriciel et ajout de vecteur (Wx + b)

6) rédiction du genre avec le fichier prediction.c 
- Lecture d’un fichier b.csv et w.csv en vecteur (read_array)
- Création de magnitude d’un son à tester (résultat de la stft)
- Calcul du vecteur statistique associé (moyennes et écart-type)
- Récupération du max de Wx + b → prédiction du genre 
 
 # TACHES RESTANTES 

Problème de prédiction : suspicion de dimensions mal comprises sur w, x et b 
