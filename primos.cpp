// Universidad del Valle de Guatemala
// CC3056
// Christian Medina Armas
// ---------------------------------------

#include <iostream>
#include <time.h>
#include <unistd.h>
#include <new>
#include <stdlib.h> //atoi

#define N 100000

using namespace std;

// Prototype for IsPrime function.
int isPrime(int);
int diff(timespec start, timespec end, timespec &diff);

int main(int argc, char *argv[]){
	cout<<"holis";

    //define variables
    timespec t1, t2, diff_t;
    int print = 0;

    //allocate memory
    unsigned int* primes = new unsigned int[N];

    //get t1
    clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &t1);

    //find primes
    for( unsigned int i=2; i<N; i++){
        primes[i] = isPrime(i);
    }
    cout<<"hola"<<primes;
    //t2
    clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &t2);

    //exit and print time
    diff(t1, t2, diff_t);
    int sec = diff_t.tv_sec;
    int ns  = diff_t.tv_nsec;
    cout<<"EXEC\t"<<sec<<"."<<ns/1000<<endl;

    delete[] primes;;
    return 0;
}

//find time difference
int diff(timespec start, timespec end, timespec &diff){

	if ((end.tv_nsec-start.tv_nsec)<0) {
		diff.tv_sec = end.tv_sec-start.tv_sec-1;
		diff.tv_nsec = 1000000000+end.tv_nsec-start.tv_nsec;
	}
  else {
		diff.tv_sec = end.tv_sec-start.tv_sec;
		diff.tv_nsec = end.tv_nsec-start.tv_nsec;
	}
	return 0;
}

//find primes
int isPrime(int number){
    for (unsigned int i=2; i<number; i++){
        if (number % i == 0){
            return 0;
        }
    }
    //number is prime
    return 1;
}
