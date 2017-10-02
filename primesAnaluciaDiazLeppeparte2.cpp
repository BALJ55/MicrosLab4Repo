// Universidad del Valle de Guatemala
// Christian Medina Armas
//moficiado: Ana lucia Diaz Leppe
// ---------------------------------------
//librerias
#include <iostream>
#include <time.h>
#include <unistd.h>
#include <new>
#include <stdlib.h> //atoi
#include <pthread.h>
#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#define N 100000
#define MAX 9   // Cambia el valor del MAX para imprimir Spirals de diferentes tamaños.

//Se declaran los nombres std y cv para evitar escribirlos cada vez que se utilice..
using namespace std;
using namespace cv;
int mat[MAX][MAX],count=1;
int i=1,j=0;


#define size_y 1000
#define size_x size_y*1.125
//define la cantidad de threads que se van a utilizar
#define NUM_THREADS 4
const complex <float> z0;
Mat prime(size_y, size_x, CV_8U);
complex<float> mat[1000][1125];

void *create_image(void* numero){ 
    	const int max= 500;
    	int retornado;
    	int iterations;
    	
    for (int i = 0; i<primes.rows; i++){

        for(int j = 0; j <primes.cols; j++){

        	/*Se declara una matriz (z) que tendra las posiciones x, y de la imagen que...
        	...se esta modificando.*/
        	complex <float> z = mat[i][j];
        	/*Se declara una copia exacta de la matriz creada arriba para evitar que se...
        	modifique la original cuando se realicen los calculos*/
		    complex <float> z0 = z;
		    /*Se declara que mientras el puntero p sea menor a la cantidad maxima de iteraciones...
		    ...y si la multiplicacion de la matriz z por si misma es menor a 4.0, entonces...
		    la cantidad de iteraciones sera igual al numero que tenga el puntero en ese momento...
		    de lo contrario, sera igual a la cantidad maxima de iteraciones max.*/
        	for (int p = 0; p < max; p++){
		    	if ((z.real() * z.real() + z.imag() * z.imag()) > 4.0f){
		    		iterations = p;
		    		break;
		    	}
		    	else{
		    	z = z * z + z0;
		    	iterations = max;
		    	}
		    }
		    /*Si el valor de max es igual al de las iteraciones, entonces el valor sera cero, de lo contrario...
		    ...retornado va a ser la raiz cuadrada de las iteraciones/la cantidad maxima * 255. Esto definira...
		    ...el color que tendra el pixel indicado de la imagen*/
		    if (max - iterations == 0){
		    	retornado = 0;
		    }
		    else {
		    	retornado = cvRound(sqrt(iterations /(float) max) * 255);
		    }
		    /*El valor que se le aplicara a la imagen sera el valor sin signo del valor encontrado...
		    ...que anteriormente se denomino retornado*/
		    uchar value = (uchar) retornado;
		    primeImg.ptr<uchar>(i)[j] = value;
		}
	}
	/*Se cierra la funcion del thread y se devuelve el valor que tendra el pixel en el que se esta...
	...trabajando y que definira el color con el que se pintara*/
    pthread_exit((void*) retornado);
	
// Prototype for IsPrime function.
int isPrime(int);
int diff(timespec start, timespec end, timespec &diff);
void fill(int ring)
{
   int m;
   if((2*ring-1)<= MAX)
   {
       if(ring==1)
       {
          mat[MAX/2][MAX/2]=count;
          count++;
       }
       else
       {
          j--;
          m=0;
          while(m < 2*(ring-1))
          {
             i--;
             mat[(MAX/2)-i][(MAX/2)-j]=count;
             count++;
             m++;
          }
          m=0;
          while(m<2*(ring-1))
          {
             j++;
             mat[(MAX/2)-i][(MAX/2)-j]=count;
             count++;
             m++;
          }
          m=0;
          while(m<2*(ring-1))
          {
             i++;
             mat[(MAX/2)-i][(MAX/2)-j]=count;
             count++;
             m++;
          }
          m=0;
          while(m < 2*(ring-1))
          {
             j--;
             mat[(MAX/2)-i][(MAX/2)-j]=count;
             count++;
             m++;
          }
          i++;
       }
       fill(ring+1);
   }
}
int main(int argc, char *argv[]){
	//espiral 
	int x,y;
    fill(1);
    cout<<"\n";
    for(x=0;x<MAX;x++)
    {
        for(y=0;y<MAX;y++)
        {
            cout<<"\t"<<mat[x][y];
        }
        cout<<"\n\n";
    }
	

    //define variables
    timespec t1, t2, diff_t;
    int print = 0;
    //funcion que define el maximo de iteraciones
    

    //allocate memory
    unsigned int* primes = new unsigned int[N];

    //get t1
    clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &t1);

    //find primes
    for( unsigned int i=2; i<N; i++){
        primes[i] = isPrime(i);
    }
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
