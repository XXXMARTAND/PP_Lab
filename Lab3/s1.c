#include <mpi.h>
#include <stdio.h>
int main(int argc, char *argv[])
{
	int rank,size,n,a[10],b[10],c;
	MPI_Init(&argc,&argv);
    
	MPI_Comm_size(MPI_COMM_WORLD,&size);
	MPI_Comm_rank(MPI_COMM_WORLD,&rank);
	MPI_Status status;
	if(rank==0)
	{
		n=size;
		fprintf(stdout, "Enter %d values\n",n );
		fflush(stdout);
		for (int i = 0; i < n; ++i)
		{
			scanf("%d",&a[i]);
		}
	}
	MPI_Scatter(a,1,MPI_INT,&c,1,MPI_INT,0,MPI_COMM_WORLD);
	fprintf(stdout, "I have received %d in process %d\n	",c,rank );
	fflush(stdout);
	c=c*c;
	MPI_Gather(&c,1,MPI_INT,b,1,MPI_INT,0,MPI_COMM_WORLD);
	
	if (rank==0)
	{
		fprintf(stdout, "The result gathered in root\n");
		fflush(stdout);
		for (int i = 0; i < n; ++i)
		{
			fprintf(stdout, "%d\t",b[i] );
			fflush(stdout);
		}
	}
	// else
	// {
	// 	MPI_Recv(&x,1,MPI_INT,0,1,MPI_COMM_WORLD,&status);
	// 	fprintf(stdout, "I have received %d in process 1\n",x );
	// 	fflush(stdout);
	// }
	MPI_Finalize();


	return 0;
} 