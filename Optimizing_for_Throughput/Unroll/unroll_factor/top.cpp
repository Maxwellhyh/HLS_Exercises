
#define N 10

void top(int a[N], int b[N], int dout[N])
{
#pragma HLS ARRAY_PARTITION dim=1 factor=5 type=cyclic variable=dout
#pragma HLS ARRAY_PARTITION dim=1 factor=5 type=cyclic variable=b
#pragma HLS ARRAY_PARTITION dim=1 factor=5 type=cyclic variable=a
	int a_reg, b_reg;

	for(int i=0; i<N; i++)
	{
		#pragma HLS UNROLL factor=5

		a_reg  = a[i];
		b_reg  = b[i];
		dout[i] = a_reg + b_reg;
	}

}
