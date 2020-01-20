#include <mpi.h>
#include <stdio.h>
#include <string.h>
int vowcount(char c[], int size){
	int pro=0;
	for (int i = 0; i < size; ++i)
	{
		if(c[i]!='a'&&c[i]!='e'&&c[i]!='o'&&c[i]!='i'&&c[i]!='u' )
			pro++;
	}
	
	return pro;
}
int main(int argc, char *argv[])
{
	int rank,size,n,m,test,b[10];
	char str[50],a[10],c[10];
	MPI_Init(&argc,&argv);
    
	MPI_Comm_size(MPI_COMM_WORLD,&size);
	MPI_Comm_rank(MPI_COMM_WORLD,&rank);
	MPI_Status status;
	if(rank==0)
	{
		n=size;
		
		fprintf(stdout, "Enter string\n" );
		fflush(stdout);
		scanf("%s",str);
		m=strlen(str)/n;
	}
	MPI_Bcast(&m,1,MPI_INT,0,MPI_COMM_WORLD);
	MPI_Scatter(str,m,MPI_CHAR,c,m,MPI_CHAR,0,MPI_COMM_WORLD);
	fprintf(stdout, "I have received %c in process %d\n	",c[0],rank );
	fflush(stdout);
	test=vowcount(c,m);
	MPI_Gather(&test,1,MPI_FLOAT,b,1,MPI_FLOAT,0,MPI_COMM_WORLD);
	
	if (rank==0)
	{
		fprintf(stdout, "The result gathered in root\n");
		fflush(stdout);
		int total;
		for (int i = 0; i < n; ++i)
		{
			fprintf(stdout, "Non vowels in process %d is %d\n",i,b[i] );
			fflush(stdout);
			total+=b[i];
		}
		
		fprintf(stdout, "\n %d is the total count\n",total);
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