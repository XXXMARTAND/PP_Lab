__kernel void rptstr(__global char *A,__global char *B,int n,int len)
{
	int id = get_global_id(0);
	int i;
	for(i=id;i<(n*len);i+=len){
		B[i]=A[id];
	}

}