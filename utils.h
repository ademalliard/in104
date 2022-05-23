#ifndef __UTILS_H__
#define __UTILS_H__

void read_array(char filename[],  int m, int n, double arr[][n]);

double* linear_add_vectors(double**W,double*x,double*b,int n_col,int n_lin,double*result);


#endif