#include <mpi.h>
#include <stdio.h>
#include <string.h>

int main (int argc, char *argv[]) {

	int rank, size;
	float x, y, area, pi;

	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	//MPI_Bcast(&size, 1, MPI_INT, 0, MPI_COMM_WORLD);
	
	x = (float)(rank+1)/size;
	y = 4.f/(1+x*x);
	area = (1/(float)size)*y;

	MPI_Reduce(&area, &pi, 1, MPI_FLOAT, MPI_SUM, 0, MPI_COMM_WORLD);

	if (rank == 0) {
		fprintf(stdout, "value of Pi is %f", pi);
		fflush(stdout);
	}
	
	MPI_Finalize();

	return 0;
}