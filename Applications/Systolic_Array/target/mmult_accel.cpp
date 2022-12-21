
#include <iostream>
#include <stdlib.h>
#include "mmult_accel.h"
#define block 8

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

                systolic1: for(int k = 0; k < block; k++) {
                    #pragma HLS PIPELINE
                        systolic2: for(int ii = 0; ii < block; ii++) {
                            systolic3: for(int jj = 0; jj < block; jj++) {
                                int last = (k==0) ? 0 : outbuf[ii*block+jj];

                                int a_val = (ii < block && k < block)? in1[DATA_SIZE*i + m + ii*DATA_SIZE+k] : 0;
                                int b_val = (k < block && jj < block)? in2[DATA_SIZE*m + j + k*DATA_SIZE+jj] : 0;
                                int result = last + a_val*b_val;

                                outbuf[ii*block+jj] = result;
                            }
                        }
                    }
                for (int t = 0; t < block*block; t++){
                #pragma HLS unroll
                    outsum[t] += outbuf[t];
                }
            }

            for(int  k=0; k < block; k++){
                for(int l=0; l < block; l++){
                    out[DATA_SIZE*i + j + DATA_SIZE*k+l] = outsum[block*k+l];
                }
            }
        }
    }
}


