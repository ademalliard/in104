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

//treatment of all the files .wav
    char* style[]={"blues","classical","country","disco","hiphop","jazz","metal","pop","reggae","rock"};
    //printf("%s\n",style[4]);

// define parameters
    int sample_freq = 22050;
    int windowSize = 512;
    int hop_size = 512;
    int colonnes,lignes,samples;
    long length;
    double* wav_data;

//__________________________________________Partie encodage base de donnee______________________________________

//save final proba data in a .csv
FILE* fp = fopen("feature.csv", "w"); 
    if (fp==NULL){
        printf("Error oppening file .csv\n");
        exit(1);
    }
printf("Open file feature.csv\n");

char * basePath = "/home/ensta/Documents/debug/src/include/genres";
char filename[1024];

for (int genre = 0; genre <10 ; genre++)
 {
    for (int sons = 0; sons < 100; sons++)
    {
//create filenames
        snprintf (filename, 1024, "%s/%s/%s.000%.2i.wav", basePath, style[genre], style[genre], sons);
            //printf("%s\n", filename);

//dump sample data of the file
        audio_read(filename,&wav_data,&length);

//parameters
        colonnes = length/(windowSize/2);
        lignes = (windowSize/2)+1;
        samples = colonnes*lignes;

//allocations
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
            //if(genre==0 && sons==0) for (int print = 0; print <10 ; print++) printf("magnitude[%d] = %.5f\n",print, magnitude[print]);
   
//calculation of the mean and the std and writting in a .csv
        fprintf(fp, "%i;", genre);
        for (int i = 0; i < lignes; i++)
        {
            for (int j = 0; j < colonnes; j++){
               une_ligne[j]=magnitude[j*lignes + i];   //get one column
             }   
            proba[2*i]=moy(une_ligne,colonnes);
            proba[2*i+1]=ecty(une_ligne,colonnes);
            fprintf(fp, "%.2f;%.2f;", proba[2*i],proba[2*i+1]);
                //if(genre==0 && sons==0 && j<3) printf("moy=%.2f-ecty=%.2f ; ",proba[2*j],proba[2*j+1]);
        }
        fprintf(fp,"\n");

        free(proba);
        free(une_ligne);
        free(magnitude);
        free(wav_data);
    }
 }
    fclose(fp);
    printf("File feature.csv written.\n");
    return 0;
}












//_________________________________________Partie prediction_______________________________________________
/*

//lecture du .csv cree par python
    int m=10;
    int n=514;
    double w_csv_py[m][n];
    double b_csv_py[m][1];
    read_array("./Documents/IN104/src/w.csv", n, m, w_csv_py);
    read_array("./Documents/IN104/src/b.csv", 1, m, b_csv_py);

//module de prediction
    filename=arg[1];
    printf("Prediction pour : %s\n",filename);
    audio_read(filename,&wav_data,&length);

    colonnes = length/(windowSize/2);
    lignes = (windowSize/2)+1;
    samples = colonnes*lignes;

    double* magnitude = (double*)malloc(sizeof(double)*samples); //donnees du spectre du son
        if (magnitude == NULL) {
            printf("Error in malloc\n");
            exit(1);}
    double* une_colonne = (double*)malloc(sizeof(double)*lignes);  //recuperation d'une colonne de magnitude
        if (une_colonne == NULL) {
            printf("Error in malloc\n");
            exit(1);}
    double* stat = (double*)malloc(sizeof(double)*(colonnes*2+1)); //moyennes et ecart-types
        if (stat == NULL) {
            printf("Error in malloc\n");                        //x
            exit(1);}

    magnitude=stft(wav_data,samples,windowSize,hop_size,magnitude,sample_freq,length);
   
    for (int j = 0; j < colonnes; j++){
        for (int i = 0; i < lignes; i++) une_colonne[i]=magnitude[j+i*lignes];   //get one column
        stat[2*j]=moy(une_colonne,colonnes);
        stat[2*j+1]=ecty(une_colonne,colonnes);
    }

    double* resultats = malloc(sizeof(double)*n); //moyennes et ecart-types
         if (resultats == NULL) {
         printf("Error in malloc\n");
         exit(1);
        }

    linear_add_vectors(w_csv_py,stat,b_csv_py,m,n,&resultats);
    //double final_score=argmax(resultats);
    printf("Le resultat de la prediction est : %.2f\n",final_score);

    free(resultats);
    free(proba);
    free(une_colonne);
    free(magnitude);
    free(wav_data);

*/