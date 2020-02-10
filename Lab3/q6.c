#include <stdio.h>
#include <mpi.h>


int main(int argc, char* argv[])
{
	int rank,size,N,M;
	int A[20],B[20],c[10],temp[10],i,sum=0,len;


	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD,&size);
	MPI_Status status;

	if(rank == 0)
	{
		N=size;

		fprintf(stdout,"Enter size \n");
		fflush(stdout);
		scanf("%d",&len);
		printf("Enter %d values\n",len);
		for(i=0;i<len;i++)
			scanf("%d",&A[i]);
		M=len/N;
	}


	MPI_Bcast(&M,1,MPI_INT,0,MPI_COMM_WORLD);

	MPI_Scatter(A,M,MPI_INT,c,M,MPI_INT,0,MPI_COMM_WORLD);
	temp[0]=c[0];
	for(i=1;i<M;i++)
	{
		temp[i]=temp[i-1]+c[i];
	}
	
	MPI_Gather(temp,M,MPI_INT,B,M,MPI_INT,0,MPI_COMM_WORLD);

	if(rank == 0)
	{
	printf("In root\n");
	for(i=0;i<len;i++)
		printf("%d \t",B[i]);	
	}
	




	MPI_Finalize();
	return 0;
}