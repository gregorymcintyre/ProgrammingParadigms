//#include <stdio.h>

#include "qSort.h"
#include <iostream>
#include <random>
#include <sys/time.h>
#include <omp.h>

using namespace std;

#define LENGTH 500000

int NUM_THREADS = 2;

void initArray(int array[LENGTH]){
	cout<<"Initialising Array with random values...\t";
	for (int i = 0 ; i < LENGTH ; i++){
		array[i] = rand() % ((100 - 1) + 1) + 1;
	}
	cout<<"Done."<<endl;

}

void printArray(int array[LENGTH]){
	cout<<"[";
	for (int i = 0 ; i < LENGTH ; i++){
		cout<<array[i]<<", ";
	}
	cout<<"]\n";
}

void openmpQuickSort( int array[], int first, int last ) 
{
    int pivotElement;
 
    if(first < last)
    {
        pivotElement = pivot(array, first, last);
        //#pragma omp parallel
        //{
        	quickSort(array, first, pivotElement-1);
        	quickSort(array, pivotElement+1, last);
    	//}
    }
}

int main(int argc, char *argv[]){

	int Array[LENGTH];
	struct timeval timecheck;
	NUM_THREADS = atoi(argv[1]);

	initArray(Array);
	//printArray(Array);

	cout<<"Sequential QuickSort.\t\t\t\tTime elapsed: ";

	gettimeofday(&timecheck, NULL);

	long timeofday_start = (long)timecheck.tv_sec * 1000 + (long)timecheck.tv_usec /1000;

	quickSort(Array, 0, LENGTH-1);
	//printArray(Array);

	gettimeofday(&timecheck, NULL);
	long timeofday_end = (long)timecheck.tv_sec * 1000 + (long)timecheck.tv_usec /1000;

	double time_elapsed = timeofday_end - timeofday_start;
	cout<<time_elapsed<<"ms"<<endl;

	
	initArray(Array);
	//printArray(Array);
	cout<<"OpenMP QuickSort.\t\t\t\tTime elapsed: ";

	gettimeofday(&timecheck, NULL);

	timeofday_start = (long)timecheck.tv_sec * 1000 + (long)timecheck.tv_usec /1000;

	openmpQuickSort(Array, 0, LENGTH-1);
	//printArray(Array);

	gettimeofday(&timecheck, NULL);
	timeofday_end = (long)timecheck.tv_sec * 1000 + (long)timecheck.tv_usec /1000;

	time_elapsed = timeofday_end - timeofday_start;
	cout<<time_elapsed<<"ms"<<endl;

	return 0;
}