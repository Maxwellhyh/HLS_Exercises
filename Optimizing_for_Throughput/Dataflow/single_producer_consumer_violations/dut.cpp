

void output(int tmp1[128], int tmp2[128], int tmp3[128])
{

	for(int i=0;i<128;i++)
	{
		tmp3[i] = tmp1[i] +tmp2[i];
	}

}

void consumer1(int tmp2[128], int tmp1[128], int tmp4[128])
{

	for(int i=0;i<128;i++)
	{

		tmp4[i] = tmp1[i] + tmp2[i];

    }

}

void consumer2(int tmp2[128], int tmp1[128], int tmp5[128])
{

	for(int i=0;i<128;i++)
	{

		tmp5[i] = tmp1[i] - tmp2[i];

    }

}

void producer(int a[128], int b[128], int tmp1[128], int tmp2[128])
{
	for(int i=0;i<128;i++)
	{

		tmp1[i]= a[i];
		tmp2[i] = b[i];
	}

}

void producer_sol(int a[128], int b[128], int tmp1[128], int tmp2[128], int tmp1copy[128], int tmp2copy[128])
{
	for(int i=0;i<128;i++)
	{

		tmp1[i]= a[i];
		tmp2[i] = b[i];
		tmp1copy[i]= a[i];
		tmp2copy[i] = b[i];
	}

}

void dut(int a[128], int b[128], int tmp3[128])
{
#pragma HLS DATAFLOW

int tmp1[128],tmp2[128], tmp4[128], tmp5[128];
//int tmp1copy[128],tmp2copy[128];

	producer(a,b,tmp1,tmp2);
	//producer_sol(a,b,tmp1,tmp2,tmp1copy,tmp2copy);
	consumer1(tmp2, tmp1, tmp4);
	consumer2(tmp2copy, tmp1copy, tmp5);
	output(tmp5,tmp4,tmp3);
}
