#include <stdio.h>


#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <iostream>
#include <pthread.h>

#define UP 1
#define DOWN 2
#define LEFT 3
#define RIGHT 4
#define MAXSZ 20
#define NUM_THREAD 16

/*
 
   * 
 
   * se utiliza mutex
   * Universidad del Valle de Guatemala 
 
   * Ana lucia Diaz Leppe #151378
 
*/

using namespace cv;
pthread_mutex_t lock;
int buffer[100];

void *thread_function_rd(void* argument){

   //parametros
   string input;
   input  = *((string*) argument);

   cout<<endl <<"Thread rd "<< input<< endl;

   //lee el buffer
   pthread_mutex_lock(&lock);
   for(int i =0; i<100;i++){
      cout<<buffer[i]<<" ";
   }
   pthread_mutex_unlock(&lock);
   
   cout<<endl;

   //the thread termina con un return
   pthread_exit(0);
}

void *thread_function_wr(void* argument){

   //define los parametros 
   string input;
   input  = *((string*) argument);

   //graba el mensaje con una memoria global
   cout<<endl << "Thread wr "<< input<< endl;

  
   //escribe la data al buffer
   pthread_mutex_lock(&lock);
   for(int i =0; i<100;i++){
      cout<<buffer[i]<<" ";
      buffer[i] = i;
   }
   pthread_mutex_unlock(&lock);

   cout<<endl;

   //el thread termina con un return
   pthread_exit(0);
}


//Imagen a ser modificada
Mat espiral(MAXSZ, MAXSZ, CV_32SC1);
//Tamano de la imagen que se creara
//float mat[MAXSZ][MAXSZ];


int isPrime(int);

int main() {
	pthread_t thread_1;
	pthread_t thread_2;
	
   string msg1 = "le voy a escribir al buffer\n";
   string msg2 = "le voy a leer al buffer\n";

   pthread_mutex_init(&lock, NULL);
   //set buffer elements to 0
   memset(buffer,0,sizeof(buffer));
   
   pthread_create(&thread_1, NULL, thread_function_wr, (void*) &msg1);
   pthread_create(&thread_2, NULL, thread_function_rd, (void*) &msg2);

   pthread_join(thread_1, NULL);
   pthread_join(thread_2, NULL);
   
   pthread_mutex_destroy(&lock);

   cout<<"Main program exit"<<endl;
   return 0;

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
			std::cout<<a[r][c]<<" -> ";
            a[r][c] = isPrime(a[r][c]);
            std::cout<<a[r][c]<<"\n";
            //set de los colores (??)
            if(a[r][c]){
       	        espiral.at<Vec3b>(Point(r,c)) = 0;
			}else{
		        espiral.at<Vec3b>(Point(r,c)) =255;	
			}
         //   std::cout << a[r][c] << " ";
            uchar value = (uchar) a[r][c];
		    espiral.ptr<uchar>(r)[c] = value;
            //printf("%4d ",a[r][c]);
        }
    }   	
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
    return 1;
}
