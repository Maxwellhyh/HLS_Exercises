#include "mmult_accel.h"
#define block 8

void mmult_hw(int* in1, int* in2, int* out)
{
    for (int i = 0; i < DATA_SIZE; i++){
        for (int j = 0; j < DATA_SIZE; j++){
            for (int k = 0; k < DATA_SIZE; k++){
                out[i * DATA_SIZE + j] += in1[i * DATA_SIZE + k] * in2[k * DATA_SIZE + j];
            }
        }
    }
}

