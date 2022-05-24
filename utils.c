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

void linear_add_vectors(int m, int n,double W[m][n], double*x, double b[m][1], double result[m][1])  //
{
    for (int i = 0; i < m; ++i) result[i][0]=0;

    for (int i = 0; i < m; ++i) {
        for (int k = 0; k < n; ++k) {
            result[i][0]=result[i][0]+W[i][k]*x[k];
        }
        result[i][0]=result[i][0]+b[i][0];
    }
}