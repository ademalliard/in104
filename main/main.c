#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <fftw3.h>
#include <math.h>
#include "wave.h"
#include "stft.h"
#include "proba.h"

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

// define parameters
    int sample_freq = 22050;
    int length = 661794;
    int windowSize = 512;
    int hop_size = 512;
    int colonnes = length/(windowSize/2);
    int lignes = (windowSize/2)+1;
    int samples = colonnes*lignes;

//dump sample data of the file
    double* wav_data = malloc(sizeof(double)*length);
        if (wav_data == NULL) {
         printf("Error in malloc\n");
         exit(1);
        }
    wav_data = audio_read(filename);

//creation of the stft data
    double* magnitude = malloc(sizeof(double)*samples);
        if (magnitude == NULL) {
         printf("Error in malloc\n");
         exit(1);
        }
    magnitude = stft(wav_data, samples, windowSize, hop_size, magnitude, sample_freq, length);
    for (int i = 0; i < 10; ++i) printf("%.2f\n", magnitude[i]);

//calculation of the mean and the std
    double* probas = malloc(sizeof(double)*lignes*2);
        if (probas == NULL) {
         printf("Error in malloc\n");
         exit(1);
        }
    probas=proba(magnitude, lignes, colonnes);

 //save result in a .csv
    FILE* fp = fopen("path to feature csv file", "a+"); // ouvre le fichier csv.
    double mean[lignes], std[lignes];
    for (int i = 0; i < lignes; i++) {
        mean[i]=probas[2*i];
        std[i]=probas[2*i+1];
        fprintf(fp, "%.2f, %.2f, ", mean[i], std[i]);
        if (i<3) printf("moy%d = %.2f, std%d = %.2f\n", i+1, mean[i], i+1, std[i]); 
    }
    printf("path to feature csv file written\n");
    fclose(fp); // ferme le fichier csv.

    free(probas);
    free(magnitude);
    free(wav_data);

    return 0;
}