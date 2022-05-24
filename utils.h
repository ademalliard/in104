#ifndef __UTILS_H__
#define __UTILS_H__

void read_array(char filename[],  int m, int n, double arr[][n]);

void linear_add_vectors(int m, int n,double W[m][n], double*x, double b[m][1], double result[m][1]);

#endif