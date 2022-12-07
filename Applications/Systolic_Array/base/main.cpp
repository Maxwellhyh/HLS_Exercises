#include <iostream>
#include <stdlib.h>
#include "sds_utils.h"
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
    size_t matrix_size_bytes = sizeof(int) * DATA_SIZE * DATA_SIZE;
    //Allocate memory
    //malloc() doesn't guarantee contiguous physical memory allocation, but for
    //the hardware to implement the function using simple DMA, it requires
    //allocation of contiguous physical memory which can be done using sds_alloc().
    int *in1 = (int *) sds_alloc(matrix_size_bytes);
    int *in2 = (int *) sds_alloc(matrix_size_bytes);
    int *hw_result = (int *) sds_alloc(matrix_size_bytes);
    int *sw_result = (int *) malloc(matrix_size_bytes);

    if( (in1 == NULL) || (in2 == NULL) || (sw_result == NULL) || (hw_result == NULL) )
        {
            std::cout << "TEST FAILED : Failed to allocate memory" << std::endl;
            return -1;
        }

    sds_utils::perf_counter hw_ctr, sw_ctr;
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
     
        std::cout << "Software #" << i << " start." << std::endl;
        sw_ctr.start();
        //Launch the software solution
        mmult_sw( in1, in2, sw_result, dim);
        sw_ctr.stop();
        std::cout << "Software #" << i << " done." << std::endl;

        std::cout << "Hardware #" << i << " start." << std::endl;
        hw_ctr.start();
        //Launch the Hardware solution
        mmult_hw( in1, in2, hw_result, dim);
        hw_ctr.stop();
        std::cout << "Hardware #" << i << " done." << std::endl;

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

    uint64_t sw_cycles = sw_ctr.avg_cpu_cycles();
    uint64_t hw_cycles = hw_ctr.avg_cpu_cycles();
    double speedup = (double)sw_cycles/ (double)hw_cycles;

    std::cout << "Number of CPU cycles running application in software:" << sw_cycles << std::endl;
    std::cout << "Number of CPU cycles running application in hardware:" << hw_cycles << std::endl;
    std::cout << "Speed up: " << speedup << std::endl;
    std::cout << "Note: Speed up is meaningful for real hardware execution only, not for emulation." << std::endl;

    //Release Memory
    sds_free(in1);
    sds_free(in2);
    sds_free(hw_result);
    free(sw_result);

    std::cout << " TEST " << (match? "PASSED": "FAILED") << std::endl;
    return(match? EXIT_SUCCESS: EXIT_FAILURE);
}



