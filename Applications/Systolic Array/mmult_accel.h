#include "ap_int.h"

#ifndef MMULT_ACC_H
#define MMULT_ACC_H

//Array size to access
#define DATA_SIZE 1024
#define BLOCK_SIZE 512
#define PACK_BITS 512
// #define INT_BITS (sizeof(int) * 8)
#define INT_BITS (4 * 8)
#define PACK_SIZE (PACK_BITS / INT_BITS) 		// 16
#define BLK_PACK (BLOCK_SIZE / PACK_SIZE)       // 32
#define DATA_PACK (DATA_SIZE / PACK_SIZE)       // 64

//Declaring the hardware function
void mmult_hw(const ap_uint<PACK_BITS>* A, const int* B, ap_uint<PACK_BITS>* C);

#endif
