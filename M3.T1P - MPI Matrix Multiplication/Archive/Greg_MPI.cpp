/* MPI
 * Greg McIntyre
 * 15/5/19
 * 
 * Compile with 
 * $ mpicc MPI.cpp
 * 
 * Run
 * $ mpirun -np 4 --hostfile ~/Desktop/Slave.list
 * $ mpirun -np 4 ./a.out
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
//void MatrixMultiplication(int np, int rank, int inputArray1[N][N], int inputArray2[N][N], int outputArray[N*N]);

void printOutput(int outputArray[N]){
    for (int i = 0 ; i < N; i++){
        printf(" %d :", outputArray[i]);
    }
    
}


int main(){
    MPI_Init(NULL, NULL);

    int np = 0;
    MPI_Comm_size(MPI_COMM_WORLD, &np);     //number of nodes

    int rank = 0;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    int inputArray1[N][N], inputArray2[N][N];
    int outputArray[N][N];
  
    if (rank==0) {
        intialiseArray(inputArray1);
        intialiseArray(inputArray2);
        printArrays(inputArray1);
        printArrays(inputArray2);

    } 

    MPI_Barrier(MPI_COMM_WORLD);
    MPI_Bcast(&inputArray1, N*N, MPI_INT, 0, MPI_COMM_WORLD);
    MPI_Bcast(&inputArray2, N*N, MPI_INT, 0, MPI_COMM_WORLD);

    MPI_Barrier(MPI_COMM_WORLD);
    MatrixMultiplication(np, rank, inputArray1, inputArray2, outputArray);
    MPI_Barrier(MPI_COMM_WORLD);
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
			array[i][j] = rand() % 10;
		}
	}
	printf("complete\n");
}		//intialises array with random values, uses the N global variable

void printArrays(int array[N][N]){
	for (int i = 0; i < N; i++) {
		printf("[");
		for (int j = 0; j < N; j++) {
			printf("%i", array[i][j]);
			printf(" ");
		}
		printf("]\n");
	}
	printf("\n");
	
}		//prints array to console

void MatrixMultiplication(int np, int rank, int inputArray1[N][N], int inputArray2[N][N], int outputArray[N][N]){
    long value;
    int range = N/np;
	int start = rank * range;
	int end = start + range;
    int buffArray[range][N]={0};
  
    for (int i = start ; i < end ; i++)
	{
		for (int j = 0; j < N; j++)
		{
			value = 0;
			for (int k = 0; k < N; k++)
			{
				value += inputArray1[i][k] * inputArray2[k][j];
			}
            buffArray[i - start][j]=value;
		}
	}
   
    MPI_Barrier(MPI_COMM_WORLD);
    MPI_Gather(buffArray, range * N, MPI_INT, outputArray, range * N, MPI_INT, 0, MPI_COMM_WORLD);
  
  
    
}