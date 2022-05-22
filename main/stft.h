#ifndef __STFT_H__
#define __STFT_H__

double hamming(int windowLength, double *buffer);

double* stft(double *wav_data, int samples, int windowSize, int hop_size,\
             double *magnitude, int sample_freq, int length);

#endif