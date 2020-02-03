__kernel void vector_add(__global int *A1,__global int *B1,__global int *C1)
{
	int i = get_global_id(0);
	; int x = A[i];
	; int j = 0;
	; mul=1;
	; int temp;
	; while(x!=0){
		
	; 	j=j+(x%8)*mul;
	; 	mul = mul*10;
	; 	x=x/8;

	; }
	C1[i]=A1[i];
}