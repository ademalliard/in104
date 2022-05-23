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

int main(int argc, char const *argv[]) {

// get filename from command line
    if (argc < 2) {
        printf("Error : No wave file specified\n");
        return 0;
    }

// get file path
    char *filename = (char*) malloc(sizeof(char) * 1024);
        if (filename == NULL) {
          printf("Error in malloc\n");
          exit(1);
        }
    char cwd[1024];
    if (getcwd(cwd, sizeof(cwd)) != NULL) {
        strcpy(filename, cwd);        
        strcat(filename, "/");
        strcat(filename, argv[1]);
        printf("%s\n", filename);
    }

/*
FILE* fp = fopen("path to feature csv file", "a+"); 
if (fp==NULL){
    printf("Error in malloc\n");
    exit(1);
}
while((c=fgetc(f))!=NULL){
    
}
    */

    //char*audios="../genres/blues/blues.00000.wav";
    int nbre_audio=1;
    //while(audios[nbre_audio]!='\0') nbre_audio++;
    printf("NOMBRE AUDIO : %d\n",nbre_audio );

// define parameters
    int sample_freq = 22050;
    int length = 661794;
    int windowSize = 512;
    int hop_size = 512;
    int colonnes = length/(windowSize/2);
    int lignes = (windowSize/2)+1;
    int samples = colonnes*lignes;

    double* wav_data = malloc(sizeof(double)*length); //donnees du son
        if (wav_data == NULL) {
            printf("Error in malloc\n");
            exit(1);
        }
    double* magnitude = malloc(sizeof(double)*samples); //donnees du spectre du son
        if (magnitude == NULL) {
            printf("Error in malloc\n");
            exit(1);
        }
    double* une_colonne = malloc(sizeof(double)*lignes);  //recuperation d'une colonne de magnitude
        if (une_colonne == NULL) {
            printf("Error in malloc\n");
            exit(1);
        }
    double* proba = malloc(sizeof(double)*(colonnes*2+1)); //moyennes et ecart-types
         if (proba == NULL) {
         printf("Error in malloc\n");                        //x
         exit(1);
        }

//save final proba data in a .csv
FILE* fp = fopen("path_to_feature_csv_file.csv", "a+"); 
    if (fp==NULL){
        printf("Error in malloc\n");
        exit(1);
    }
fprintf(fp,"\n");

for (int sons = 0; sons < nbre_audio; ++sons)
{
   wav_data=audio_read(filename);
   magnitude=stft(wav_data,samples,windowSize,hop_size,magnitude,sample_freq,length);
   for (int j = 0; j < colonnes; j++)
   {
       for (int i = 0; i < lignes; i++)
       {
           proba[2*j]=moy(une_colonne,lignes);
           proba[2*j+1]=ecty(une_colonne,lignes);
           fprintf(fp, "%.2f; %.2f\n", proba[2*j],proba[2*j+1]);
       }
   }
   fprintf(fp, "%.2f; %d; ", magnitude[sons], sons);
   printf("%d\n",sons );
}
/*
for (int sons = 0; sons < nbre_audio; ++sons)
{
    //dump sample data of the file
        wav_data = audio_read(filename);

    //creation of the stft data
        magnitude = stft(wav_data, samples, windowSize, hop_size, magnitude, sample_freq, length);
        for (int i = 0; i < 10; ++i) printf("%.2f\n", magnitude[i]);

    //calculation of the mean and the std and writting in the .csv
        for (int j = 0; j < colonnes; ++j) {
            for (int i = 0; i < lignes; ++i) une_colonne[i]=magnitude[j+i*lignes];
            proba[2*j]=moy(une_colonne,lignes);
            proba[2*j+1]=ecty(une_colonne,lignes);
            //if (j<3) printf("moy%d = %.2f, std%d = %.2f\n", j+1, proba[2*j], j+1, proba[2*j+1]);
            fprintf(fp, "%.2f; %.2f; ", proba[2*j], proba[2*j+1]);
        }
        printf("Path to feature csv file written\n");
        fprintf(fp,"\n");
}
fclose(fp); // ferme le fichier csv.


//lecture du .csv cree par python
    int n=514;
    int m=10;
    double csv_py[m][n];
    read_array("path to w", n, m, csv_py);

//module de prediction
    double* resultats = malloc(sizeof(double)*n); //moyennes et ecart-types
         if (resultats == NULL) {
         printf("Error in malloc\n");                        //x
         exit(1);
        }
    resultats=linear_add_vectors(W,x,b,m,n,resultats);
    double resultat=argmax(resultats);
    printf("Le resultat de la prediction est : %.2f\n",resultat);
 
    free(resultats);
    free(proba);
    free(une_colonne);
    free(magnitude);
    free(wav_data);
*/

    return 0;
 }