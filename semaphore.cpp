//Universidad del valle de Guatemala
//semaphore sample code

#include <iostream>
#include <stdio.h>
#include <pthread.h>
#include <string>
#include <semaphore.h>


using namespace std;

//global variable
char buffer[32];

sem_t mySemaphore;

void *thread_function_rd(void* argument){

   //cast the parameter
   string input;
   input  = *((string*) argument);

   cout<< "Thread received "<< input<< endl;


   sem_wait(&mySemaphore);
   //read global variable contents
   cout<<buffer<<endl;
   sem_post(&mySemaphore);

   //the thread terminates with return
   pthread_exit(0);
}

void *thread_function_wr(void* argument){

   //cast the parameter
   string input;
   input  = *((string*) argument);

   //write message to global variable
   cout<< "Thread received "<< input<< endl;

   sem_wait(&mySemaphore);
   sprintf(buffer,"%s","Data in buffer.");
   sem_post(&mySemaphore);

   //the thread terminates with return
   pthread_exit(0);
}



int main(int argc, char *argv[]){

   cout<<"Main program start"<<endl;

   pthread_t thread_1;
   pthread_t thread_2;

   string msg1 = "Thread 1: I will write to buffer";
   string msg2 = "Thread 2: I will read from buffer";

   //init semaphore shared among threads and initial value of 1
   sem_init(&mySemaphore,0,1);

   pthread_create(&thread_1, NULL, thread_function_wr, (void*) &msg1);
   pthread_create(&thread_2, NULL, thread_function_rd, (void*) &msg2);

   //main program continues

   //wait for the thread to terminate and collect exit status
   pthread_join(thread_1, NULL);
   pthread_join(thread_2, NULL);

   //only main code is running now

   //destroy semaphore
   sem_destroy(&mySemaphore);

   cout<<"Main program exit"<<endl;
   return 0;
}
