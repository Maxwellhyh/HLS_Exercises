#include "mmult_accel.h"
#define block 8
void mmult(const int* A, const int* B, int* C);

void mmult_hw(int* in1, int* in2, int* out, int dim)
{
    for (int i = 0; i < dim; i++){
        for (int j = 0; j < dim; j++){
            for (int k = 0; k < dim; k++){
                out[i * dim + j] += in1[i * dim + k] * in2[k * dim  + j];
            }
        }
    }
}

