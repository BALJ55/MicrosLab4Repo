#include <stdio.h>


#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <iostream>

#define UP 1
#define DOWN 2
#define LEFT 3
#define RIGHT 4
#define MAXSZ 19


/*
 
   * Code to generate spiral matrix for n elements where n >= 1
 
   * To generate spiral matrix for n elements just
   * change the value of MAXSZ to whatever u want :)
 
   * Author : Raza (rzs23@yahoo.com)
 
*/

using namespace cv;

//Imagen a ser modificada
Mat espiral(MAXSZ, MAXSZ, CV_8U);
//Tamano de la imagen que se creara
//float mat[MAXSZ][MAXSZ];


int isPrime(&int);

int main() {

    int initial_direction = UP, n = MAXSZ, p = 1, num =
            MAXSZ * MAXSZ + 1;    /*direccion inicial para que se mueva a la derecha*/

    int r, c, a[MAXSZ][MAXSZ];

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
    int color;
    for (r = 0; r < MAXSZ; r++) {
        for (c = 0; c < MAXSZ; c++) {


			Vec3b color = espiral.at<Vec3b>(Point(r,c));
            a[r][c] = isPrime(&a[r][c]);
            //set de los colores (??)
            if(a[r][c]){
       	        espiral.at<Vec3b>(Point(r,c)) = 0;
			}else{
		        espiral.at<Vec3b>(Point(r,c)) = 255;	
			}
         //   std::cout << a[r][c] << " ";
            uchar value = (uchar) a[r][c];
		    espiral.ptr<uchar>(r)[c] = value;
            //printf("%4d ",a[r][c]);
        }
    }
    	
        imwrite("espiralPrimos.png", espiral);

    return 0;

}

//funcion dada para un numero primo
int isPrime(int &number) {
    for (unsigned int i = 2; i < number; i++) {
        if (number % i == 0) {
            return 0;
        }
    }
    //number is prime	
    return 1;
}

