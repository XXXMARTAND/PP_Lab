#include <mpi.h>
#include <stdio.h>

int main(int argc, char *argv[])
{
	int rank,size,t[50],x;
	int a[50],buffsize,s1;
	
	MPI_Init(&argc,&argv);

	MPI_Comm_size(MPI_COMM_WORLD,&size);
	MPI_Comm_rank(MPI_COMM_WORLD,&rank);
	MPI_Pack_size(1,MPI_INT,MPI_COMM_WORLD,&s1);
	buffsize = s1*size + 2*MPI_BSEND_OVERHEAD;
    MPI_Buffer_attach(a,buffsize);
	MPI_Status status;
	//printf("Hello world from rank %d with processes %d\n",rank,size );
	if(rank==0){
		printf("Enter array value in master process:");
		for (int i = 1; i < size; ++i)
		{
			scanf("%d",&t[i]);
			
		}
		for (int i = 1; i < size; ++i)
		{
			
			MPI_Bsend(&t[i],1,MPI_INT,i,1,MPI_COMM_WORLD);
			//fprintf(stdout, "I have send %d from process 0\n",t[i] );
			fflush(stdout);
		}
		
	}
	else if(rank%2==0&&rank!=0)
	{
		MPI_Recv(&x,1,MPI_INT,0,1,MPI_COMM_WORLD,&status);
		fprintf(stdout, "Square is %d in process rank %d \n",x*x,rank );
		fflush(stdout);
		
	}
	else
	{
		MPI_Recv(&x,1,MPI_INT,0,1,MPI_COMM_WORLD,&status);
		fprintf(stdout, "Cube is %d in process rank %d \n",x*x*x,rank );
		fflush(stdout);
		
	}

	
	MPI_Buffer_detach(&a,&buffsize);
	MPI_Finalize();


	/* code */
	return 0;
}