#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>
#include <stdlib.h>





double moy(double* vecteur, int nbre_de_lignes)
{
	double moyenne = 0 ;
	for (int i=0; i< nbre_de_lignes;++i)
	{
		moyenne = moyenne + vecteur[i];
	}
	return moyenne/nbre_de_lignes ;
}


double ecty(double* vecteur, int nbre_de_lignes)
{
	double ety = 0;
	double moyenne = moy(vecteur, nbre_de_lignes) ;
	for (int i=0; i< nbre_de_lignes;++i)
	{
		ety=ety + pow(vecteur[i]-moyenne,2) ;
	}
	ety=sqrt(ety/(nbre_de_lignes-1));
	return ety;
}

double* proba(double* magnitude,int nbre_de_lignes, int nbre_de_colonnes)
{
	double* vecteur[nbre_de_colonnes];
	for (int j=1;j<=nbre_de_lignes;++j)
	{
		for (int i=1;i<= nbre_de_colonnes;++i)
		{
			vecteur[i]=magnitude[(i-1)*nbre_de_lignes+(i-1)];
		}
		proba[2*(j-1)+1]=moy(vecteur,nbre_de_colonnes);
		proba[2*(j-1)+2]=ecty(vecteur,nbre_de_colonnes);
	}
}







/*double* probas (double* wave_data, int nbre_de_ligne, int nbre_de_colonne, double* proba)
{
	int count=0;

	//pour toutes les lignes on calcule l'ecart-type et la moyenne a completer dans "proba"
	double* ligne = malloc(sizeof(double)*nbre_de_colonne);
	for (int i = 0; i < nbre_de_colonne; ++i) 
	{
		ligne[i]=wave_data[count];
		count++;
	}

	

	//Moyenne
	count = 0 ;
	int countbis = 0;
	double moy = 0;  // moyenne 
	double ety = 0; //ecart type
	double term = 0; // intermédiaire de calcul
	double carr;
	for (int j = 0; j <nbre_de_ligne ; ++j) 
	{

		for (int i = 0; i <nbre_de_colonne; ++i) 
		{
			moy=moy+wave_data[count];
			count++;
		}

		moy=moy/nbre_de_colonne ;
	proba[2*j]=moy;
	moy = 0 ;
	
		for (int k = 0; k < nbre_de_colonne; ++k) 
		{
			term=term + pow(wave_data[countbis]-proba[2*j],2);
			countbis++ ;
		}
		carr=carr/nbre_de_colonne ; 
		ety=sqrt(term/(nbre_de_colonne-1)) ;
	proba[2*j+1]=ety;
	ety=0 ;
	term = 0 ;
	}

	
	return proba ; 
}*/

/*int main()
{
	int nbre_de_lignes =4 ;
	double vecteur[nbre_de_lignes];
	vecteur[0]=44;
	vecteur[1]=11;
	vecteur[2]=22;
	vecteur[3]=33;
	double moyenne=moy(vecteur,nbre_de_lignes);
	double ety=ecty(vecteur,nbre_de_lignes);
	printf("moy=%f\n",moyenne);
	printf("ecrtatype=%f\n",ety);
	
}*/	

/*
int main() // TEST
{
	int nbre_de_ligne=3 ;
	int nbre_de_colonne=4;
	int nbre_elements = 6; //nombre d'éléments dans probas (=moyenne + ecart-type)
	double wave_data[12];
	wave_data[0]=23 ;
	wave_data[1]=45 ;
	wave_data[2]=67 ;
	wave_data[3]=78 ;
	wave_data[4]=11 ;
	wave_data[5]=54 ;
	wave_data[6]=77 ;
	wave_data[7]=87 ;
	wave_data[8]=20 ;
	wave_data[9]=40 ;
	wave_data[10]=70 ;
	wave_data[11]=75 ;
	double* proba =malloc(sizeof(double)*nbre_elements) ;
	proba = probas(wave_data,nbre_de_ligne,nbre_de_colonne,proba) ;
	for (int i=0;i<nbre_elements;++i){
		printf("element = %.2f\n", proba[i]);
	}	
}


ety = somme((valeur-moyenne)²)/nbre_valeur

*/