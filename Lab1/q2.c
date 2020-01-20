
#include "mpi.h"
#include <stdio.h>
int main(int argc, char *argv[])
{
	int rank,size;
	MPI_Init(&argc,&argv);
    
	MPI_Comm_size(MPI_COMM_WORLD,&size);
	MPI_Comm_rank(MPI_COMM_WORLD,&rank);
	//printf("Hello world from rank %d with processes %d\n",rank,size );
	if(rank==0){
		printf("Hello...... from rank %d\n",rank );
	}
	else
	{
		printf("World......from rank %d\n",rank);
	}
	MPI_Finalize();

	/* code */
	return 0;
}