#include <mpi.h>
#include <stdio.h>
int isPrime(int c){
	for (int i = 2; i < c; ++i)
	{
		if(c%i==0){
			return 0;

		}
	}
	return 1;
}

int main(int argc, char *argv[])
{
	int rank,size;

	MPI_Init(&argc,&argv);
    
	MPI_Comm_size(MPI_COMM_WORLD,&size);
	MPI_Comm_rank(MPI_COMM_WORLD,&rank);
	//printf("Hello world from rank %d with processes %d\n",rank,size );
	if(rank==0){
		for (int i = 1; i < 50; ++i)
		{
			if(isPrime(i)==1){
				printf("%d, ", i);
			}
		}
	}
	else if(rank==1)
	{
		for (int j = 50; j < 100; ++j)
		{
			if(isPrime(j)==1){
				printf("%d, ", j);
			}
		}

	}
	

	MPI_Finalize();

	/* code */
	return 0;
}