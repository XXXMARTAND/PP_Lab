#include <mpi.h>
#include <stdio.h>


int main(int argc, char *argv[])
{
	int rank,size;
	int x;
	int i = 0;
	MPI_Init(&argc,&argv);
    
	MPI_Comm_size(MPI_COMM_WORLD,&size);
	MPI_Comm_rank(MPI_COMM_WORLD,&rank);
	MPI_Status status;
	//printf("Hello world from  rank %d with processes %d\n",rank,size );
	if(rank==0){
		printf("Enter value in master process:");
		scanf("%d",&x);
		MPI_Send(&x,1,MPI_INT,rank+1,rank,MPI_COMM_WORLD);
		fprintf(stdout, "I have send %d from process 0\n",x );
		MPI_Recv(&x,1,MPI_INT,size-1,size-1,MPI_COMM_WORLD,&status);
		fprintf(stdout, "I have received %d in process 0\n",x );
		fflush(stdout);
	}
	else
	{
		MPI_Recv(&x,1,MPI_INT,rank-1,rank-1,MPI_COMM_WORLD,&status);
		fprintf(stdout, "I have received %d in process %d\n",x,rank );
		
		x++;
		MPI_Send(&x,1,MPI_INT,(rank+1)%size,rank,MPI_COMM_WORLD);
		fprintf(stdout, "I have sent %d from process %d\n",x,rank);
		fflush(stdout);
	}
	MPI_Finalize();


	/* code */
	return 0;
}