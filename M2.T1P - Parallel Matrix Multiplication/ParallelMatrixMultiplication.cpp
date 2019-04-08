// SequentialMatrixMultiplication.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

//#include "pch.h"

#include <stdio.h>
#include <iostream>
#include <sys/time.h>
#include <time.h>
#include <pthread.h>
#include <omp.h>

using namespace std;

#define N 500
//#define NUM_THREADS 2

//int N;
int NUM_THREADS;

pthread_mutex_t mutx;

int inputArray1[N][N];
int inputArray2[N][N];
int outputArray[N][N];

void intialiseArray(int array[N][N]) {
	cout<<"intialising array... ";
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			array[i][j] = rand() % ((100 - 1) + 1) + 1;
		}
	}
	cout<<"complete"<<endl;
}

void printArrays(int array[N][N]){
	cout <<"[";
	for (int i = 0; i < N; i++) {
		cout << "[";
		for (int j = 0; j < N; j++) {
			cout << array[i][j];
			std::cout << " ";
		}
		std::cout << "]\n";
	}
	std::cout << "]\n\n";
}

void SequentialMatrixMultiplication()
{
	int value;
	for (int i = 0; i < N; i++)
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
}

void *pthreadMatrixMultiplication(void *threadid)
{
	long tid = (long)threadid;
	long value;

	int range = N/NUM_THREADS;
	int start = tid * range;
	int end = start + range;

	for (int i = start ; i < end ; i++)
	{
		for (int j = 0; j < N; j++)
		{
			value = 0;
			for (int k = 0; k < N; k++)
			{
				value += inputArray1[i][k] * inputArray2[k][j];
			}

			pthread_mutex_lock(&mutx);
			outputArray[i][j] = value;
			pthread_mutex_unlock(&mutx);
		}
	}
	pthread_exit(NULL);

}

void OpenmpMatrixMultiplication()
{
	#pragma omp parallel
	{
		int value;
		#pragma omp for
		for (int i = 0; i < N; i++)
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
	}
}

int main(int argc, char *argv[]){

	NUM_THREADS = atoi(argv[1]);
	//N = atoi(argv[2]);

	struct timeval timecheck;
	
	pthread_t threads[NUM_THREADS];
	pthread_mutex_init(&mutx, NULL);

	intialiseArray(inputArray1);
	intialiseArray(inputArray2);

	//cout << "Input Array"<<endl;
	//printArrays(inputArray1);
	
	//cout << "Input Array"<<endl;
	//printArrays(inputArray2);

	//cout << "Output Array"<<endl;
	//printArrays(outputArray);

	cout<<"Sequential Matrix Multiplication.\t\tTime elapsed: ";

	gettimeofday(&timecheck, NULL);

	long timeofday_start = (long)timecheck.tv_sec * 1000 + (long)timecheck.tv_usec /1000;

	SequentialMatrixMultiplication();

	gettimeofday(&timecheck, NULL);
	long timeofday_end = (long)timecheck.tv_sec * 1000 + (long)timecheck.tv_usec /1000;

	double time_elapsed = timeofday_end - timeofday_start;
	cout<<time_elapsed<<"ms"<<endl;

	cout<<"pthread Matrix Multiplication with " << NUM_THREADS << " threads.\tTime elapsed: ";

	gettimeofday(&timecheck, NULL);

	timeofday_start = (long)timecheck.tv_sec * 1000 + (long)timecheck.tv_usec /1000;

	for (long tid = 0 ; tid < NUM_THREADS;tid++){
		pthread_create(&threads[tid], NULL, pthreadMatrixMultiplication, (void *)tid);
	}

	for (long tid = 0 ; tid < NUM_THREADS;tid++){
		pthread_join(threads[tid], NULL);
	}

	gettimeofday(&timecheck, NULL);
	timeofday_end = (long)timecheck.tv_sec * 1000 + (long)timecheck.tv_usec /1000;

	time_elapsed = timeofday_end - timeofday_start;
	cout<<time_elapsed<<"ms"<<endl;

	cout<<"OpenMP Matrix Multiplication with " << NUM_THREADS << " threads.\tTime elapsed: ";

	gettimeofday(&timecheck, NULL);

	timeofday_start = (long)timecheck.tv_sec * 1000 + (long)timecheck.tv_usec /1000;

	OpenmpMatrixMultiplication();

	gettimeofday(&timecheck, NULL);
	timeofday_end = (long)timecheck.tv_sec * 1000 + (long)timecheck.tv_usec /1000;

	time_elapsed = timeofday_end - timeofday_start;
	cout<<time_elapsed<<"ms"<<endl;

	//cout << "Output Array"<<endl;
	//printArrays(outputArray);

	return 0;
}