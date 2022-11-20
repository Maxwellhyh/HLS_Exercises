## Introduction

Convolutional neural network(CNN) is a very popular algorithm for implementing artificial intelligence in recent years. You can learn about convolutional neural networks through this course <http://cs231n.stanford.edu>. The convolution operation occupies the main computational load of CNN and can be given by the following equation:


$$
\operatorname {OFM} [ m ] \left[ or \right] \left[ oc \right] = \sum _ { n = 0 } ^ { N } \sum _ { kr = 0 } ^ { K } \sum _ { kc = 0 } ^ { K } \operatorname {W} [ m ] [ n ] [ kr ] [ kc ] \times \operatorname {IFM}[n][S \times or + kr - P][S \times oc + kc - P]
$$


where `OFM` stands for output feature map, `IFM` stands for input feature map, `W` stands for weight, `N` stands for the number of input feature maps, `m` and `n` stands for the index of input feature map and output feature map, `S` stands for stride, `r` and `c` stands for row and column and `P` stands for Padding.  An illustration of 2D CNN.

![image](pic/T7/cnn_illustration.gif)

The C code of convolution is shown below

```c
void convolution(float *ifm, float *ofm, float *weight)
{
    for (int r = 0; r < OR; r++)
    {
        for (int c = 0; c < OC; c++)
        {
            for (int m = 0; m < M; m++)
            {
                float odata = 0;
                int ofm_index = m*OR*OC + r*OC + c;
                for (int n = 0; n < N; n++)
                {
                    for(int kr = 0; kr < K; kr++)
                    {
                        for (int kc = 0; kc < K; kc++)
                        {
                            float ret;
                            int ic = c*S - P + kc;
                            int ir = r*S - P + kr;

							if( (ic<0) || (ir<0) || (ic>(IC-1)) || (ir>(IR-1)))
                                ret=0;
                            else
                                ret = ifm[n*IR*IC + ir*IC + ic];
                            ret *= weight[m*N*K*K + n*K*K + kr*K + kc];
                            odata += ret;
                        }
                    }
                }
                ofm[ofm_index] = odata;
            }
        }
    }
}
```

In the above code, IR stands for input feature map's row, IC stands for input feature map's columm, OR stands for output feature map's row, OC stands for output feature map's columm.

## Requirement

In this tutorial, all the hyper parameters are fixed value, that is, M=16, OR=56, OC=56, N=16, IR=56, IC=56, K=3, S=1, P=1. Under the premise of ensuring the correct results, you can arbitrarily modify the given code as well as add the appropriate HLS and SDS pragmas to it. This project takes the time to complete the convolution of the `56*56*16` feature map as the key evaluation metrics. Also, try to reduce the resource consumption as much as possible.

