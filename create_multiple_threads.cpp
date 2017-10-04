#include <pthread.h>
#include <iostream>
#define NUM_THREADS 20

using namespace std;


void *printHello(void *threadid){
   long tid;
   tid = (long)threadid;
   cout<<"Hello World! It's me, thread "<<tid<<endl;

   pthread_exit((void*) 0);
}




int main(int argc, char *argv[]){

   cout<<"main program start"<<endl;

   pthread_t threads[NUM_THREADS];
   void* return_status;

   int rc;
   long t;
   
   //launch threads
   for(t=0; t<NUM_THREADS; t++){
     cout<<"In main: creating thread "<< t<< endl;
     rc = pthread_create(&threads[t], NULL, printHello, (void *)t);
     
     if (rc){
       cout<<"ERROR: return code from pthread_create() <<"<< rc<< endl;
       return(-1);
       }
   }

   //main program continues to execute

   //wait for all threads to end
   for(t=0; t<NUM_THREADS; t++){
      pthread_join(threads[t], &return_status);
   }

   cout<<"main program exit"<<endl;
   return(0);
}
