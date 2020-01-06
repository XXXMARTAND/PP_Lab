
#include <mpi.h>
#include <stdio.h>
int main(int argc, char *argv[])
{
	int rank,size;
	int a=5;
	int b=3;
	MPI_Init(&argc,&argv);
    
	MPI_Comm_size(MPI_COMM_WORLD,&size);
	MPI_Comm_rank(MPI_COMM_WORLD,&rank);
	//printf("Hello world from rank %d with processes %d\n",rank,size );
	if(rank==0){
		printf("Addition - %d\n",a+b);
	}
	else if(rank==1)
	{
		printf("Subtraction - %d\n",a-b);
	}
	else if(rank==2)
	{
		printf("Multiplication - %d\n",a*b);
	}
	else if (rank==3)
	{
		printf("Division - %d\n",a/b);
	}

	MPI_Finalize();

	/* code */
	return 0;
}