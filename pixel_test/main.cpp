//Universidad del Valle de Guatemala
//Christian Medina Armas
//-----------------------------------
//Sample code to test imageStats() from cvlib.h


#include <opencv2/core.hpp>
#include <opencv2/core/utility.hpp>
#include "opencv2/imgcodecs.hpp"
#include <opencv2/highgui.hpp>
#include <iostream>
#include <sstream>
#include <string>

#include "cvlib.h"

#define INFO 1
#define N 30
#define DISPLAY 0

using namespace std;
using namespace cv;

int main( int argc, char *argv[]){

    //verify enough arguments
    if (argc < 2){
        cout<< "Not enough arguments"<< endl;
        return -1;
    }

    //declare conainers
    Mat source_bw, source_c, result;
    
    //load
    source_bw = imread(argv[1], IMREAD_GRAYSCALE);
    source_c  = imread(argv[1], IMREAD_COLOR);
    int img_size = source_bw.rows * source_bw.cols;

    if(INFO) { 
        cout<<endl<<"Image:\t"<<argv[1]<<endl;
        cout<<"Rows:\t"<< source_bw.rows<< endl;
        cout<<"Cols:\t"<< source_bw.cols<< endl;
        cout<<"Size:\t"<< img_size<< endl;
    }

    //test image contents
    if(source_bw.empty()){
	cout << "The image " << argv[1] << " could not be loaded." << endl;
	return -1;
    }

    if(DISPLAY){
      //load and display source image
      int scale = 30;

      const string win1 = "Source Image";
      int shift = imgShowLab(win1, source_bw, scale, 0, 0);

      const string win2 = "Result Image";
      imgShowLab(win2, source_c, scale, shift, 0);

      waitKey(0);
    }

    double t;
    uint stats[9];


    //analyze grayscale image
    //-----------------------

    //start time measure
    t = (double)getTickCount();

    //get stats
    for(int i = 0; i < N; i++){
        imageStats(source_bw, stats, 0);
    }

    //compute exec-time
    t = 1000*((double)getTickCount() - t)/getTickFrequency();


    if(INFO){
    cout<<endl<<"Min\tMax\tAVG"<<endl;
    for(int i=0;i<3; i++){
        cout<<stats[i]<<"\t";
    }
    cout<<endl;

    cout<< "Time\t" << t/N << " ms."<< endl;
    cout<< "pixels/ms.\t"<< (img_size * N) / t<< endl<< endl;
    }


    //analyze color image
    //-------------------

    //start time measure
    t = (double)getTickCount();

    for(int i = 0; i < N; i++){
        imageStats(source_c, stats, 0);
    }

    //compute exec-time
    t = 1000*((double)getTickCount() - t)/getTickFrequency();


    if(INFO){
    cout<<"B\tG\tR"<< endl;
    for(int i = 0; i < 9; i++){
	if( (i%3==0)&(i>0) ) cout<< endl;
        cout<< stats[i]<< "\t";
    }
    cout<<endl;

    cout<< "Time\t" << t/N << " ms."<< endl;
    cout<< "pixels/ms.\t"<< (img_size * N) / t<< endl<< endl;
    }

  return 0;
}
