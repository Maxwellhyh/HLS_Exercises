
#include <iostream>
#include <stdlib.h>
#include "mmult_accel.h"
#define block 8
void mmult(int* A, int* B, int* C);

void mmult_hw(int* in1, int* in2, int* out)
{

    int outbuf[block*block];
    #pragma HLS ARRAY_PARTITION variable=outbuf dim=0 complete
    int outsum[block*block];
    #pragma HLS ARRAY_PARTITION variable=outsum dim=0 complete
    for (int i=0; i< DATA_SIZE; i +=block){
        for (int j=0; j< DATA_SIZE; j +=block){
            for (int  k=0; k < block*block; k++){
            #pragma HLS unroll    
                outsum[k]=0;
            }
            for (int m=0; m< DATA_SIZE; m +=block){
                int *in1block = in1 + DATA_SIZE*i + m;
                int *in2block = in2 + DATA_SIZE*m + j;
                mmult(in1block, in2block, outbuf);
                for (int t = 0; t < block*block; t++){
                #pragma HLS unroll
                    outsum[t] += outbuf[t];
                }
            }
            int* outblock = out + DATA_SIZE*i +j;

            for(int  k=0; k < block; k++){
                for(int l=0; l < block; l++){
                    outblock[DATA_SIZE*k+l] = outsum[block*k+l];
                }
            }
        }
    }
}



void mmult(int* A, int* B, int* C)
{

    systolic1: for(int k = 0; k < block; k++) {
    #pragma HLS PIPELINE
        systolic2: for(int i = 0; i < block; i++) {
            systolic3: for(int j = 0; j < block; j++) {
                int last = (k==0) ? 0 : C[i*block+j];

                int a_val = (i < block && k < block)? A[i*DATA_SIZE+k] : 0;
                int b_val = (k < block && j < block)? B[k*DATA_SIZE+j] : 0;
                int result = last + a_val*b_val;

                C[i*block+j] = result;
            }
        }
    }
}


