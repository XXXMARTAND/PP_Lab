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
		fprintf(stdout, "Enter number to find\n");
		fflush(stdout);
		scanf("%d", &fac);
		fprintf(stdout, "Enter the matrix element\n");
		fflush(stdout);
		//scanf_s("%d", &n, 1);
		for (i = 0; i < 3; i++) {
			for (j = 0; j < 3; j++) {
				scanf("%d", &a[i][j]);
			}
		}
	}

	MPI_Bcast(&fac, 1, MPI_INT, 0, MPI_COMM_WORLD);
	MPI_Scatter(a, 100, MPI_INT, b, 100, MPI_INT, 0, MPI_COMM_WORLD);

	int count = 0;
	for (i = 0; i < 3 ; i++) { 
		count += (b[i] == fac);
	}
		

	MPI_Reduce(&count, &k, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);
	if (rank == 0) {
		fprintf(stdout, "Element Found %d times", k);
		fflush(stdout);
	}

	MPI_Finalize();
	return 0;
}