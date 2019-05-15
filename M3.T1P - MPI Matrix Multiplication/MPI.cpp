/* MPI
 * Greg McIntyre
 * 15/5/19
 * 
 * Compile with 
 * $ mpicc MPI.cpp
 * 
 * Run
 * $ mpirun -np 5 --hostfile ~/Desktop/Slave.list
 * $ mpirun -np 5 ./a.out
 * 
 */

#include<mpi.h>
#include<stdlib.h>
#include<unistd.h>
#include<stdio.h>

#define N 4

using namespace std;

void intialiseArray(int array[N][N]);
void printArrays(int array[N][N]);
void MatrixMultiplication(int np, int rank, int inputArray1[N][N], int inputArray2[N][N], int outputArray[N][N]);

int main(){
    MPI_Init(NULL, NULL);

    int np = 0;
    MPI_Comm_size(MPI_COMM_WORLD, &np);     //number of nodes
    //printf("%d\n", np);

    int rank = 0;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    //printf("%d\t", rank);

    int inputArray1[N][N], inputArray2[N][N], outputArray[N][N]={{0}};

    if (rank==0) {
        intialiseArray(inputArray1);
        intialiseArray(inputArray2);

        //printArrays(inputArray1);
        //printArrays(inputArray2);
    }else{
        //printArrays(outputArray);
    }

    MPI_Bcast(&inputArray1, N*N, MPI_INT, 0, MPI_COMM_WORLD);
    MPI_Bcast(&inputArray2, N*N, MPI_INT, 0, MPI_COMM_WORLD);

    //if(rank==0){
    //    //int MPI_Scatter(const void *sendbuf, int sendcount, MPI_Datatype sendtype, void *recvbuf, int recvcount, MPI_Datatype recvtype, int root, MPI_Comm comm)
    //    MPI_Scatter(&inputArray1, N*N/np, MPI_INT, &inputArray1, MPI_INT, 0, MPI_COMM_WORLD)
    //}else{
    //    //int array
    //    MPI_Scatter(&inputArray1, N*N/np, MPI_INT, &inputArray1, MPI_INT, 0, MPI_COMM_WORLD)
    //}

    //multi plic

    //int MPI_Gather(const void *sendbuf, int sendcount, MPI_Datatype sendtype, void *recvbuf, int recvcount, MPI_Datatype recvtype, int root, MPI_Comm comm)

    MatrixMultiplication(np, rank, inputArray1, inputArray2, outputArray);
    //printArrays(outputArray);



    if(rank==0)printArrays(outputArray);


    MPI_Finalize();
    return 0;
}

void intialiseArray(int array[N][N]) {
	printf("intialising array... ");
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			array[i][j] = rand() % ((100 - 1) + 1) + 1;
		}
	}
	printf("complete\n");
}		//intialises array with random values, uses the N global variable

void printArrays(int array[N][N]){
	printf("[");
	for (int i = 0; i < N; i++) {
		printf("[");
		for (int j = 0; j < N; j++) {
			printf("%i", array[i][j]);
			printf(" ");
		}
		printf("]\n");
	}
	printf("]\n\n");
}		//prints array to console

void MatrixMultiplication(int np, int rank, int inputArray1[N][N], int inputArray2[N][N], int outputArray[N][N]){
    long value;

    int range = N/np;
	int start = rank * range;
	int end = start + range;

    //printf("%d:%d-%d\n", rank, start, end);

    for (int i = start ; i < end ; i++)
	{
		for (int j = 0; j < N; j++)
		{
			value = 0;
			for (int k = 0; k < N; k++)
			{
				value += inputArray1[i][k] * inputArray2[k][j];
			}
			outputArray[i][j] = value;
		}
	}
    printArrays(outputArray);

    //int MPI_Gather(const void *sendbuf, int sendcount, MPI_Datatype sendtype, void *recvbuf, int recvcount, MPI_Datatype recvtype, int root, MPI_Comm comm)
    //MPI_Gather(&outputArray, range, MPI_INT, &outputArray, 16, MPI_INT, 0, MPI_COMM_WORLD);
}