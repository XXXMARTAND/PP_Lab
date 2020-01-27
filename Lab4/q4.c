#include <mpi.h>
#include <stdio.h>
#include <string.h>

int main (int argc, char* argv[]) {

	int rank, size;
	int i = 0, j;
	int k = 0, fac = 1, ans[1000], sum = 0;
	int n, a[100][100], b[100];
	
	MPI_Init(&argc, &argv);

	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);

	if (rank == 0) {


		fprintf(stdout, "Enter 4X4 Matrix \n");
		for (i = 0; i < 4; i++) {
			for (j = 0; j < 4; j++) {
				scanf("%d", &a[i][j]);
			}
		}
	}
	//MPI_Bcast(&fac, 1, MPI_INT, 0, MPI_COMM_WORLD);
	MPI_Scatter(a, 100, MPI_INT, b, 100, MPI_INT, 0, MPI_COMM_WORLD);
	MPI_Scan(b, ans, 4, MPI_INT, MPI_SUM, MPI_COMM_WORLD);
	MPI_Gather(ans,4,MPI_INT,b,4,MPI_INT,0,MPI_COMM_WORLD);
	//int count = 0;
	if(rank==0){
		for (i = 0; i < 16; i++) { 
		
		
		if(i%4==0)
			printf("\n");
		
			printf("%d ", b[i]);	
	}
	}	
		//fprintf(stdout, "%d ", ans[i]);
		
	
	//fflush(stdout);
	
	MPI_Finalize();

	return 0;
}