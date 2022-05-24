#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <fftw3.h>
#include <math.h>
#include "wave.h"
#include "stft.h"
#include "proba.h"
#include "utils.h"

int main(int argc, char *argv[]) {

	if (argc<2)
	{
		printf("Error. Not enough argument.\n");
		exit(1);
	}

// get file path
	char * basePath = "/home/ensta/Documents/debug/src/include/genres";
	char filename[1024];
	snprintf (filename, 1024, "%s/%s", basePath, argv[1]);

// define parameters
    int sample_freq = 22050;
    int windowSize = 512;
    int hop_size = 512;
    int colonnes,lignes,samples;
    long length;
    double* wav_data;

//lecture du .csv cree par python
    int m=10;   //
    int n=513;  //
    double w_csv_py[m][n];  //
    double b_csv_py[m][1];  // auparavant 1 n 
    read_array("./w.csv", m, n, w_csv_py);  //
    read_array("./b.csv", m, 1, b_csv_py);  // same 

//module de prediction
    printf("Prediction pour : %s\n",filename);
    audio_read(filename,&wav_data,&length);

        colonnes = length/(windowSize/2);
        lignes = (windowSize/2)+1;
        samples = colonnes*lignes;

    double* magnitude = (double*)malloc(sizeof(double)*samples); //donnees du spectre du son
        if (magnitude == NULL) {
            printf("Error in malloc\n");
            exit(1);
        }
    double* une_ligne = (double*)malloc(sizeof(double)*colonnes);  //recuperation d'une colonne de magnitude
        if (une_ligne == NULL) {
            printf("Error in malloc\n");
            exit(1);
        }
    double* proba = (double*)malloc(sizeof(double)*(lignes*2+1)); //moyennes et ecart-types
        if (proba == NULL) {
            printf("Error in malloc\n");                        //x
            exit(1);
        }

     //creation of the stft data
            magnitude=stft(wav_data,samples,windowSize,hop_size,magnitude,sample_freq,length);
            
     //calculation of the mean and the std and writting in a .csv
            for (int i = 0; i < lignes; i++)
            {
                for (int j = 0; j < colonnes; j++){
                  une_ligne[j]=magnitude[j*lignes + i]; //get one column
                } 
                    proba[2*i]=moy(une_ligne,colonnes);
                    proba[2*i+1]=ecty(une_ligne,colonnes);
            }

    double resultats[m][1]; //moyennes et ecart-types       // same

    linear_add_vectors(m,n,w_csv_py,proba,b_csv_py,resultats);      //

   double final_score=resultats[0][0];          // chgmt 1ere case auapravant 1 0
    for (int i = 0; i < m; ++i)                 //
    {
    	printf("%.2f\n",resultats[i][0]);      // 1 n 
    	if (resultats[i][0]>final_score)       //
    	{
    		final_score=resultats[i][0];      //
    	}
    }
    printf("Le resultat de la prediction est : %.2f\n",final_score);    //

    int i=floor(final_score);
    if (i==0) printf("This sound is blues.\n");
    else if (i==1)printf("This sound is classical.\n");
    else if (i==2)printf("This sound is country.\n");
    else if (i==3)printf("This sound is disco.\n");
    else if (i==4)printf("This sound is hip hop.\n");
    else if (i==5)printf("This sound is jazz.\n");
    else if (i==6)printf("This sound is metal.\n");
    else if (i==7)printf("This sound is pop.\n");
    else if (i==8)printf("This sound is reggae.\n");
    else printf("This sound is rock.\n");

    free(proba);
    free(une_ligne);
    free(magnitude);
    free(wav_data);



    return 0;
 }