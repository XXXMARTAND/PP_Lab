#include <mpi.h>
#include <stdio.h>
#include <string.h>
void concat(char b[], char c[], int size,char a[]){
	;
	int x=0,y=0;
	for (int i = 0; i < 2*size; ++i)
	{
		if(i%2==0)
			a[i]=b[x++];
		else
			a[i]=c[y++];
			
	}
	a[2*size]='\0';
	
	
}
int main(int argc, char *argv[])
{
	int rank,size,n,m,b[10];
	char str1[50], str2[50], a[10],c1[10],c2[10],test[20],b1[20],b2[20];
	MPI_Init(&argc,&argv);
    
	MPI_Comm_size(MPI_COMM_WORLD,&size);
	MPI_Comm_rank(MPI_COMM_WORLD,&rank);
	MPI_Status status;
	if(rank==0)
	{
		n=size;
		fprintf(stdout, "Enter string\n" );
		fflush(stdout);
		scanf("%s",str1);
		fprintf(stdout, "Enter string\n" );
		fflush(stdout);
		scanf("%s",str2);
		m=strlen(str1)/n;
	}
	MPI_Bcast(&m,1,MPI_INT,0,MPI_COMM_WORLD);
	MPI_Scatter(str1,m,MPI_CHAR,c1,m,MPI_CHAR,0,MPI_COMM_WORLD);
	MPI_Scatter(str2,m,MPI_CHAR,c2,m,MPI_CHAR,0,MPI_COMM_WORLD);
	fprintf(stdout, "I have received %c in process %d\n	",c1[0],rank );
	fprintf(stdout, "I have received %c in process %d\n	",c2[0],rank );
	fflush(stdout);
	concat(c1,c2,m,test);
	MPI_Gather(test,2*m,MPI_CHAR,b1,2*m,MPI_CHAR,0,MPI_COMM_WORLD);

	if (rank==0)
	{
		b1[m*n*2]='\0';
		fprintf(stdout, "%s\n",b1 );
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