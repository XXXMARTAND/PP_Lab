#include "cuda_runtime.h"
#include "device_launch_parameters.h"
#include <stdio.h>
#include <stdlib.h>

__global__ void cal(int *a, int *b, int x1)
{
	int i = blockIdx.x;
	b[i] = x1 * a[i] + b[i];
}

int main()
{
	int a[20], b[20];
	int n, i;

	printf("Enter size");
	scanf("%d",&n);
	
	printf("\nEnter set 1 \n");
	for(i = 0; i < n; i++)
		scanf("%d", &a[i]);
	printf("Enter set 2 \n");
	for(i = 0; i < n; i++)
		scanf("%d", &b[i]);

	int alpha;
	printf("Enter AA ");
	scanf("%d", &alpha);

	int *d_a, *d_b, *d_c, *d_d, *d_e;
	int size = sizeof(int) * 20;
	
	cudaMalloc((void**)&d_a, size);
	cudaMalloc((void**)&d_b, size);
	cudaMalloc((void**)&d_c, size);
	cudaMalloc((void**)&d_d, size);
	cudaMalloc((void**)&d_e, size);
	
	cudaMemcpy(d_a, &a, size, cudaMemcpyHostToDevice);
	cudaMemcpy(d_b, &b, size, cudaMemcpyHostToDevice);
	
	cal<<<n, 1>>>(d_a, d_b, alpha);
	
	cudaMemcpy(&b, d_b, size, cudaMemcpyDeviceToHost);
	printf("\nExpansion res \n");
		for(i = 0; i < n; i++)
			printf("%d  ", b[i]);
	printf("\n");

	cudaFree(d_a);
	cudaFree(d_b);

	return 0;
}