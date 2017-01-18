/*
 * Facetracker
 * @authors : Team OpenFaceTracker
 *
*/
#ifndef HFT_RECOGNISE
#define HFT_RECOGNISE
#include <math.h>
#include <ctime>
#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <opencv/cv.h>
#include <opencv/highgui.h>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/face.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/objdetect.hpp>
#include <fstream>
#include <string>

#ifdef _WIN32
    #define PATH_DB             "/home/naper/code/facetracker/ftLib/DB/images_win.ext"
    #define FT_TEST_RECOGNISE   1
#endif

#ifdef linux
    #define PATH_DB             "/home/naper/Projects/OpenFaceTracker/facetracker/ftLib/DB/images.ext"
#endif

#define UNKNOWN			-1
#define MATCHING		-2
#define RECOGNIZED	 1

using namespace cv;
using namespace std;

class Recognise{
	public:
		IplImage *EqualizingPicture(CvRect *r,  IplImage *imageSrc);
		int Crop(IplImage *imageSrc, CvRect *r, int i);
		int ftrecognise(Mat face);
	private:
		void SaveImage(char *filename, Mat img, int *Compteur);
		IplImage *GoGetPictures(char *filename, int *Compteur);
		void parse_csv(const string& filename, vector<Mat>& images, vector<int>& labels);

};


#endif
