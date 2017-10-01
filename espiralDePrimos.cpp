/*Universidad del Valle de Guatemala
Autora: Andrea Maria Cordon Mayen
Carne: 16076
Fecha: 06/09/2016
Implementacion paralela del set de Mandelbrot
mandelbrot_parallel_AndreaCordon.cpp*/


//Librerias a utilizar en el programa
#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <pthread.h>

//Se declaran los nombres std y cv para evitar escribirlos cada vez que se utilice..
//...una funcion de las mismas
using namespace std;
using namespace cv;

#define size_y 1000
#define size_x size_y*1.125

/*Se define la cantidad de threads a utilizar en el programa. Se define global...
...para asi tener la posibilidad de usar mas threads cambiando solo una variable*/
#define NUM_THREADS 4

//Variables globales a utilizar:

const complex <float> z0;

//Imagen a ser modificada
Mat mandelbrotImg(size_y, size_x, CV_8U);
//Tamano de la imagen que se creara
complex<float> mat[1000][1125];


/*Funcion que creara los thread a utilizar en el programa...
...en este caso, se unieron las funciones "mandelbrotSet" y "mandelbrotIterations"...
...en una sola funcion que identifica de que color se debe pintar cada pixel de la imagen.*/
void *create_image(void* numero){ 
	/*Se declaran e inicializan las variables que se utilizaran dentro de la funcion*/
	//max es una variable que define el numero maximo de iteraciones que pueden haber
    const int max = 500;
    //retornado es el nombre que se le asigno a la variable que contendra el resultado 
    //del color a utilizar para el punto especifico de la matriz
    int retornado;
    /*iterations es la variable que guardara el valor de la cantidad de iteraciones*/
    int iterations;

    /*Se declara que mientras el puntero i sea menor a la cantidad de filas de la imagen...
    ...entonces se pasara a revisar lo mismo para las columnas y se le sumara la cantidad de...
    ...threads definidos (variable global NUM_THREADS) al puntero*/
    for (int i = 0; i<mandelbrotImg.rows; i++){

        for(int j = 0; j <mandelbrotImg.cols; j++){

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
		    mandelbrotImg.ptr<uchar>(i)[j] = value;
		}
	}
	/*Se cierra la funcion del thread y se devuelve el valor que tendra el pixel en el que se esta...
	...trabajando y que definira el color con el que se pintara*/
    pthread_exit((void*) retornado);

}

/*Funcion que recorre la imagen y devuelve el color que debe tener cada pixel de la misma*/
void mandelbrot_serial(Mat &img, const float x1, const float y1, const float scaleX, const float scaleY){

    for (int i = 0; i < img.rows; i++){

        for (int j = 0; j < img.cols; j++){

            float x0 = j / scaleX + x1;
            float y0 = i / scaleY + y1;

            complex<float> z0(x0, y0);
            mat[i][j] = z0;
        }
    }
}


/*Funcion principal del programa*/
int main(int argc, char *argv[]){

    /*Se preparan las variables a utilizar*/
    float x1 = -2.1f;
    float x2 =  0.6f;
    float y1 = -1.2f;
    float y2 =  1.2f;

    float scaleX = mandelbrotImg.cols / (x2 - x1);
    float scaleY = mandelbrotImg.rows / (y2 - y1);

    /*Se declaran algunas otras variables a utilizar, asi como se llama a la funcion...
    ...mandelbrot_Serial para que cumpla su funcion*/
    double tiempo = (double) getTickCount();
    mandelbrot_serial(mandelbrotImg, x1, y1, scaleX, scaleY);
    //Se incializa el thread como un array de la cantidad que especifica NUM_THREADS
    pthread_t threads[NUM_THREADS];
    //Se define la variable que contendra el valor que retorne el thread
    void* return_status;
    int t = 0;
    /*Se establece que mientras la cantidad de threads que van siendo creados sea menor...
    ...a la cantidad de threads establecidos, entonces se seguiran creando y ejecutando...
    ...threads*/
    for (t = 0; t <= NUM_THREADS; t++){
            pthread_create(&threads[t], NULL, create_image, (void *) t);
        }
        //Se espera a que cada thread termine de ejecutarse
        for (t = 0; t <= NUM_THREADS; t++){
            pthread_join(threads[t], &return_status);
        }

    /*Se calcula el tiempo que le tarda al programa fabricar la imagen*/    
    tiempo = ((double) getTickCount() - tiempo) / getTickFrequency();

    //Se imprime el tiempo de ejecucion del programa
    cout << "Execution time: " << tiempo << " segundos" << endl;

    //Se guarda la imagen en la carpeta que contiene al programa como: Mandelbrot_parallel_AndreaCordon.png
    imwrite("Mandelbrot_parallel_AndreaCordon.png", mandelbrotImg);

    return(0);
}

