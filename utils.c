#include <math.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void read_array(char filename[],  int m, int n, double arr[][n])
{
    FILE* fp = fopen(filename, "r");
    //double arr[10][514];
    if (!fp)
        printf("Can't open file\n");
 
    else {
        char buffer[4096];
 
        int row = 0;
        int column = 0;
 
        while (fgets(buffer, 4096, fp)) {
            column = 0;
            char* value = strtok(buffer, ",");
            while (value) {
                arr[row][column] = atof(value);
                value = strtok(NULL, ",");
                column++;
            }
            row++;
        }
        fclose(fp);
    }
}

double* linear_add_vectors(double**W,double*x,double*b,int n_col,int n_lin,double*result)
{
    for (int i = 0; i < n_lin; ++i) {
        for (int k = 0; k < n_col; ++k) {
            result[i]=result[i]+W[i][k]*x[k];
        }
        result[i]=result[i]+b[i];
    }
    return result;
}