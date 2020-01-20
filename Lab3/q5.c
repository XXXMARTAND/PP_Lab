#include <mpi.h>
#include <stdio.h>
#include <string.h>
int modify(int a){
	
		if(a%2==0)
			a=1;
		else
			a=0;
return a;
	
}
int main(int argc, char *argv[])
{
	int rank,size,n,m1=0,m2=0,b[10],c;
	int str1[50], a[10],test[20];
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
	MPI_Bcast(&m1,1,MPI_INT,0,MPI_COMM_WORLD);
	MPI_Bcast(&m2,1,MPI_INT,0,MPI_COMM_WORLD);
	MPI_Scatter(a,1,MPI_INT,&c,1,MPI_INT,0,MPI_COMM_WORLD);
	fprintf(stdout, "I have received %d in process %d\n	",c,rank );
	fflush(stdout);
	
	c=modify(c);
	if(c==1)
		m2++;
	else	
		m1++;
	
	//MPI_Alltoall(&m2,1,MPI_INT,&m1,1,MPI_INT,MPI_COMM_WORLD);
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

		fprintf(stdout, " \n Even %d\n",m1 );
			fflush(stdout);

			fprintf(stdout, "Odd %d\n",m2 );
			fflush(stdout);
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