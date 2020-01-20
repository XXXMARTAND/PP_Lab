#include <mpi.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
int main(int argc, char *argv[])
{
	int rank,size;
	char a[50];
	int diff = (int)('a'-'A');
	MPI_Init(&argc,&argv);
    
	MPI_Comm_size(MPI_COMM_WORLD,&size);
	MPI_Comm_rank(MPI_COMM_WORLD,&rank);
	MPI_Status status;
	//printf("Hello world from rank %d with processes %d\n",rank,size );
	if(rank==0){
		printf("Enter value in master process:");
		scanf("%s",a);
		MPI_Ssend(&a,50,MPI_CHAR,1,1,MPI_COMM_WORLD);
		fprintf(stdout, "I have send %s from process 0\n",a );
		MPI_Recv(&a,50,MPI_CHAR,1,1,MPI_COMM_WORLD,&status);
		fprintf(stdout, "I have received %s in process 1\n",a );
		fflush(stdout);
	}
	else
	{
		MPI_Recv(&a,50,MPI_CHAR,0,1,MPI_COMM_WORLD,&status);
		fprintf(stdout, "I have received %s in process 1\n",a );
		
		for (int i = 0; i < strlen(a); ++i)	
		{
			if (a[i]>='a'&&a[i]<='z')	
			{
				a[i] = a[i] - diff;
			}
			else
			{
				a[i] += diff;
			}
		}
		MPI_Ssend(&a,50,MPI_CHAR,0,1,MPI_COMM_WORLD);
		fprintf(stdout, "I have sent %s to process 0\n",a );
		fflush(stdout);
	}
	MPI_Finalize();


	/* code */
	return 0;
}