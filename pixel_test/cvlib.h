//prototypes for cvlib.cpp

#include <opencv2/core.hpp>
#include <opencv2/core/utility.hpp>
#include "opencv2/imgcodecs.hpp"
#include <opencv2/highgui.hpp>
#include <iostream>
#include <sstream>
#include <string>


using namespace std;
using namespace cv;

// prototypes
//--------------------------------------------------


int imgShowLab(const string&, Mat&, int, int, int);

int imageStats(Mat&, uint*, int);
