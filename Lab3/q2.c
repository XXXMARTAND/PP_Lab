#include <mpi.h>
#include <stdio.h>
int avg(int c[], int size){
	int pro=0;
	for (int i = 0; i < size; ++i)
	{
		pro = pro+c[i];
	}
	pro = pro/size;
	return pro;
}
int main(int argc, char *argv[])
{
	int rank,size,n,m,a[10],b[10],c[10],test;
	MPI_Init(&argc,&argv);
    
	MPI_Comm_size(MPI_COMM_WORLD,&size);
	MPI_Comm_rank(MPI_COMM_WORLD,&rank);
	MPI_Status status;
	if(rank==0)
	{
		n=size;
		fprintf(stdout, "Enter m \n");
		fflush(stdout);
		scanf("%d",&m);
		fprintf(stdout, "Enter %d values\n",n*m );
		fflush(stdout);
		for (int i = 0; i < n*m; ++i)
		{
			scanf("%d",&a[i]);
		}
	}
	MPI_Bcast(&m,1,MPI_INT,0,MPI_COMM_WORLD);
	MPI_Scatter(a,m,MPI_INT,c,m,MPI_INT,0,MPI_COMM_WORLD);
	fprintf(stdout, "I have received %d in process %d\n	",c[0],rank );
	fflush(stdout);
	test=avg(c,m);
	MPI_Gather(&test,1,MPI_FLOAT,b,1,MPI_FLOAT,0,MPI_COMM_WORLD);
	
	if (rank==0)
	{
		fprintf(stdout, "The result gathered in root\n");
		fflush(stdout);
		for (int i = 0; i < n; ++i)
		{
			fprintf(stdout, "%d\t",b[i] );
			fflush(stdout);
		}
		int x = avg(b,n);
		fprintf(stdout, "\n %d is the overall average\n",x );
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