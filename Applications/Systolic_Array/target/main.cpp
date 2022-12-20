#include <iostream>
#include <stdlib.h>

#include "mmult_accel.h"

#ifndef NUM_TIMES
#define NUM_TIMES 2  
#endif

void mmult_sw( int *in1,   // Input matrix 1
               int *in2,   // Input matrix 2
               int *out,   // Output matrix (out = A x B)
               int dim     // Matrix size of one dimension
             )
{
    //Performs matrix multiplication out = in1 x in2
    for (int i = 0; i < dim; i++){
        for (int j = 0; j < dim; j++){
            for (int k = 0; k < dim; k++){
                out[i * dim + j] += in1[i * dim + k] * in2[k * dim  + j];
            }
        }
    }
}


int main(int argc, char** argv)
{   
    int dim =  DATA_SIZE;

    int in1[DATA_SIZE * DATA_SIZE];
    int in2[DATA_SIZE * DATA_SIZE];
    int hw_result[DATA_SIZE * DATA_SIZE];;
    int sw_result[DATA_SIZE * DATA_SIZE];;

    bool match = true;

    for (int i = 0; i < NUM_TIMES; i++)
    { 
        //Create test data
        for (int i = 0; i < dim * dim; i++) {
            in1[i] = rand() % dim;
            in2[i] = rand() % dim;
            sw_result[i] = 0;
            hw_result[i] = 0;
        }
     

        //Launch the software solution
        mmult_sw( in1, in2, sw_result, dim);

        //Launch the Hardware solution
        mmult_hw( in1, in2, hw_result);


        //Compare the results of hardware to the software 
        for(int i=0; i< dim * dim; i++)
        {
            if( sw_result[i] != hw_result[i] )
            {
                std::cout << "Results Mismatch on " << "Row:" << i/dim << "Col:" << i - (i/dim)*dim << std::endl;
                std::cout << "CPU output:" << sw_result[i] <<"\t Hardware output:" << hw_result[i] << std::endl;
                match = false;
                break;
            }
        }
    }

    std::cout << " TEST " << (match? "PASSED": "FAILED") << std::endl;
    return(match? EXIT_SUCCESS: EXIT_FAILURE);
}



