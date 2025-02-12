
#include "mem_bottleneck.h"
 
dout_t mem_bottleneck(din_t mem[N]) {
#pragma HLS ARRAY_PARTITION dim=1 type=complete variable=mem


  dout_t sum=0;
  int i;
  
  SUM_LOOP:for(i=2;i<N;++i)
    
#pragma HLS PIPELINE
sum += mem[i] + mem[i-1] + mem[i-2];

  return sum;
}

