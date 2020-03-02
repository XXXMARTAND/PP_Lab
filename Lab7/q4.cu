#include "cuda_runtime.h"
#include "device_launch_parameters.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

__global__ void sin(float *a, float *b)
{
	int i = blockIdx.x;
	b[i] = sinf(a[i]);
}

int main()
{
	float a[20], b[20];
	int n, i;
	printf("Enter size");
	scanf("%d", &n);
	printf("\nEnter rad array \n");

	for(i = 0; i < n; i++)
		scanf("%f", &a[i]);

	float *d_a, *d_b;
	int size = sizeof(float) * 20;
	cudaMalloc((void**)&d_a, size);
	cudaMalloc((void**)&d_b, size);

	cudaMemcpy(d_a, &a, size, cudaMemcpyHostToDevice);

	sin<<<n,1>>>(d_a, d_b);
	cudaMemcpy(&b, d_b, size, cudaMemcpyDeviceToHost);
	
	printf("\nResultant arr \n");
		for(i = 0; i < n; i++)
			printf("%f   ", b[i]);
	printf("\n");

	cudaFree(d_a);
	cudaFree(d_b);

	return 0;
}
