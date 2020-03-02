#include "cuda_runtime.h"
#include "device_launch_parameters.h"
#include <stdio.h>
#include <stdlib.h>

//function definition 

__global__ void Fun1(int *a, int *b, int *c)
{
	int i = blockIdx.x;
	c[i] = a[i] + b[i];
}
__global__ void Fun2(int *a, int *b, int *c)
{
	int i = threadIdx.x;
	c[i] = a[i] + b[i];
}
__global__ void Fun3(int *a, int *b, int *c, int n)
{
	int idx = threadIdx.x;
	int id = blockIdx.x * blockDim.x;
	idx += id;

	if(idx < n)
		c[idx] = a[idx] + b[idx];
}


//program
int main()
{
	int a[20], b[20], c[20], n, i;
	printf("Enter n ");
	scanf("%d", &n);
	printf("\nEnter set 1\n");
	for(i = 0; i < n; i++)
		scanf("%d", &a[i]);
	printf("Enter set 2\n");
	for(i = 0; i < n; i++)
		scanf("%d", &b[i]);

	int *d_a, *d_b, *d_c, *d_d, *d_e;

	int size = sizeof(int) * 20;
	
	cudaMalloc((void**)&d_a, size);
	cudaMalloc((void**)&d_b, size);
	cudaMalloc((void**)&d_c, size);
	cudaMalloc((void**)&d_d, size);
	cudaMalloc((void**)&d_e, size);

	cudaMemcpy(d_a, &a, size, cudaMemcpyHostToDevice);

	cudaMemcpy(d_b, &b, size, cudaMemcpyHostToDevice);
	//func def
	Fun1<<<n, 1>>>(d_a, d_b, d_c);
	
	cudaMemcpy(&c, d_c, size, cudaMemcpyDeviceToHost);
	printf("Res 1\n");
	for(i = 0; i < n; i++)
		printf("%d  \n", c[i]);

	int d[20];
	//func def
	Fun2<<<1, n>>>(d_a, d_b, d_d);
	
	cudaMemcpy(&d, d_d, size, cudaMemcpyDeviceToHost);
	printf("Res 2\n");
	for(i = 0; i < n; i++)
		printf("%d  \n", d[i]);
	//init
	int e[20];

	int thread = 256;

	int xyz = (int)(n / thread);
	//func def
	Fun3<<<xyz, 256>>>(d_a, d_b, d_e, n);
	
	cudaMemcpy(&e, d_e, size, cudaMemcpyDeviceToHost);
	printf("Res 3\n");

	for(i = 0; i < n; i++)
		printf("%d \n", e[i]);
	
	
	cudaFree(d_a);
	cudaFree(d_b);
	cudaFree(d_c);
	cudaFree(d_d);
	
	return 0;
}