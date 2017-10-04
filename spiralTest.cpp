#include <stdio.h>


#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <iostream>

#define UP 1
#define DOWN 2
#define LEFT 3
#define RIGHT 4
#define MAXSZ 200
#define NUMTHREADS 16

/*

*/

using namespace cv;

//Imagen a ser modificada
Mat espiral(MAXSZ, MAXSZ, CV_8UC1 );
//Tamano de la imagen que se creara
//float mat[MAXSZ][MAXSZ];


int isPrime(int);
int a[MAXSZ][MAXSZ];

int main() {

    int initial_direction = UP, n = MAXSZ, p = 1, num =
            MAXSZ * MAXSZ + 1;    /*direccion inicial para que se mueva a la derecha*/

    int r, c ;

    int row_right = 0, column_down = n - 1, row_left = n - 1, column_up = 0, colorVal = 0;
    //MATRIZ a 0
    for (r = 0; r < MAXSZ; r++) {
        for (c = 0; c < MAXSZ; c++)
            a[r][c] = 0;
    }
    //Generar espiral
    while (p != n * n + 1) {
        if (initial_direction == UP) {
            //Mover a la derecha
            r = row_right++;
            for (c = 0; c < n; c++) {
                if (a[r][c] == 0)
                    a[r][c] = num - p++;
            }
            initial_direction = RIGHT;
        } else if (initial_direction == RIGHT) {
            //Mover hacia abajo
            c = column_down--;
            for (r = 0; r < n; r++) {
                if (a[r][c] == 0)
                    a[r][c] = num - p++;
            }
            initial_direction = DOWN;
        } else if (initial_direction == DOWN) {
            //Mover hacia la izqueirda
            r = row_left--;
            for (c = n - 1; c >= 0; c--) {
                if (a[r][c] == 0)
                    a[r][c] = num - p++;
            }
            initial_direction = LEFT;
        } else if (initial_direction == LEFT) {
            //Mover hacia arriba
            c = column_up++;
            for (r = n - 1; r >= 0; r--) {
                if (a[r][c] == 0)
                    a[r][c] = num - p++;
            }
            initial_direction = UP;
        }
    }
    //Imprimir la Matriz
    printf("\n\n");
    
    pthread_t threads[NUM_THREADS];
    //Se define la variable que contendra el valor que retorne el thread
    void* return_status;
    
    for (t = 0; t <= NUMTHREADS; t++){
        pthread_create(&threads[t], NULL, build_image, (void *) t);
    }
    for (t = 0; t <= NUM_THREADS; t++){
        pthread_join(threads[t], &return_status);
    }
//		----- VERSI�N SERIAL -----
//    
//    for (r = 0; r < MAXSZ; r++) {
//        for (c = 0; c < MAXSZ; c++) {
//
//
//			std::cout<<a[r][c]<<" -> ";
//            a[r][c] = isPrime(a[r][c]);
//            std::cout<<a[r][c]<<"\n";
//            uchar value = (uchar) a[r][c];
//		    espiral.ptr<uchar>(r)[c] = value;
//        }
//    }   	
//		----- ! VERSI�N SERIAL -----
        imwrite("espiralPrimos.png", espiral);
std::cout<<"Imagen guardada con exito";
    return 0;

}

//funcion dada para un numero primo
int isPrime(int number) {
    for (unsigned int i = 2; i < number; i++) {
        if (number % i == 0) {
            return 0;
        }
    }
    //number is prime	
    return 255;
}

//thread function
void *create_image(void* numero){ 
	/*Se declaran e inicializan las variables que se utilizaran dentro de la funcion*/
	//max es una variable que define el numero maximo de iteraciones que pueden haber
    const int max = 125 * numero;
    int retornado;
    int iterations;

    for(int i =125*(numero-1); i<max;i++){
    	for( int j=0; j<MAXSZ;j++){
    		std::cout<<a[i][j]<<" -> ";
            a[i][j] = isPrime(a[i][j]);
            std::cout<<a[i][j]<<"\n";
            uchar value = (uchar) a[i][j];
		    espiral.ptr<uchar>(i)[j] = value;
		}
	}
    pthread_exit((void*) retornado);

}
