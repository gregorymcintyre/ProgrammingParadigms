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

#define N 2000
#define NUM_THREADS 2

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

int main(){

	struct timeval timecheck;

	intialiseArray(inputArray1);
	intialiseArray(inputArray2);

	//cout << "Input Array"<<endl;
	//printArrays(inputArray1);
	
	//cout << "Input Array"<<endl;
	//printArrays(inputArray2);

	//cout << "Output Array"<<endl;
	//printArrays(outputArray);

	cout<<"Sequential Matrix Multiplication, Time elapsed: ";

	gettimeofday(&timecheck, NULL);

	long timeofday_start = (long)timecheck.tv_sec * 1000 + (long)timecheck.tv_usec /1000;

	SequentialMatrixMultiplication();

	gettimeofday(&timecheck, NULL);
	long timeofday_end = (long)timecheck.tv_sec * 1000 + (long)timecheck.tv_usec /1000;

	double time_elapsed = timeofday_end - timeofday_start;
	cout<<time_elapsed<<"ms"<<endl;

	//cout << "Output Array"<<endl;
	//printArrays(outputArray);

	return 0;
}