/*
g++
g++ -fopenmp ComplexThreading.cpp qSort.o


*/

//#include <stdio.h>

#include "qSort.h"
#include <iostream>
#include <random>
#include <sys/time.h>
#include <omp.h>
#include <pthread.h> 

using namespace std;

#define LENGTH 250000
int Array[LENGTH];
int NUM_THREADS = 2;
int P;

void initArray(int array[LENGTH]){
	cout<<"Using Array of size: "<<LENGTH<<endl;
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
        //#pragma omp parallel sections
        //{
        //	#pragma omp section
        	quickSort(array, first, pivotElement-1);
        	//cout<<"1"<<endl;

        	//#pragma omp section
        	quickSort(array, pivotElement+1, last);
        	//cout<<"2"<<endl;
    	//}
    }
}

void* pthread_QuickSort(void *threadid){

	int pivotElement;

	long tid = (long)threadid;
 	int range = LENGTH/NUM_THREADS;
	
 	int first = tid * range;;
 	int last = first + range - 1;

 	if(tid == 0){

		last = P - 1 ;

	    if(first < last)
	    {
	        pivotElement = pivot(Array, first, last);
	        quickSort(Array, first, pivotElement-1);
	        quickSort(Array, pivotElement+1, last);
	    }
	}else{

		first = P;

	    if(first < last)
	    {
	        pivotElement = pivot(Array, first, last);
	        quickSort(Array, first, pivotElement-1);
	        quickSort(Array, pivotElement+1, last);
	    }
	}
}


void pthreadQuickSort(){

	pthread_t threads[NUM_THREADS];

	int pivotElement;
	int first = 0;
	int last = LENGTH-1;

    if(first < last)
    {
    	P = pivot(Array, first, last);			//global P

		for (long tid = 0; tid < NUM_THREADS; tid++) 
			pthread_create(&threads[tid], NULL, pthread_QuickSort, (void *)tid);

		for (long tid = 0; tid < NUM_THREADS; tid++) 
			pthread_join(threads[tid], NULL); 
	}
}

int main(int argc, char *argv[]){

	struct timeval timecheck;
	//NUM_THREADS = atoi(argv[1]);

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
	cout<<"pthread QuickSort.\t\t\t\tTime elapsed: ";

	gettimeofday(&timecheck, NULL);

	timeofday_start = (long)timecheck.tv_sec * 1000 + (long)timecheck.tv_usec /1000;

	//pthread_QuickSort((void*)NULL);
	pthreadQuickSort();
	//printArray(Array);

	gettimeofday(&timecheck, NULL);
	timeofday_end = (long)timecheck.tv_sec * 1000 + (long)timecheck.tv_usec /1000;

	time_elapsed = timeofday_end - timeofday_start;
	cout<<time_elapsed<<"ms"<<endl;

	return 0;
}