#include <stdio.h>
#include <string.h>
#include <stbool.h>
#include <math.h>

double* proba (double* wave_data, int nbre_de_ligne, int nbre_de_colonne, double* proba){
	int count=0;

	//pour toutes les lignes on calcule l'ecart-type et la moyenne a completer dans "proba"
	double* ligne = malloc(sizeof(double)*nbre_de_colonne);
	for (int i = 0; i < nbre_de_colonne; ++i) {
		ligne[i]=wave_data[count];
		count++;
	}
	//Moyenne
	double moy = 0;
	double ety = 0;
	for (int j = 0; j <nbre_de_ligne ; j=j+2) {
		for (int i = 0; i <nbre_de_colonne; ++i) {
			moy=moy+wave_data[count];
			count++;
		}
		moy=moy/2;
	proba[j]=moy;
		for (int i = 0; i < nbre_de_colonne; ++i) {
			ety=
		}
	}
	
	proba[]
}




/*

ety = somme((valeur-moyenne)²)/nbre_valeur

*/