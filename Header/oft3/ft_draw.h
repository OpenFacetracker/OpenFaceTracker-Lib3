/*
 * Facetracker
 * @authors : Hamza & Godeleine & Quentin
 *
*/
#ifndef HFT_DRAW
#define HFT_DRAW
#include <math.h>
#include <ctime>
#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <opencv/cv.h>
#include <opencv/highgui.h>
#include <time.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>
#ifdef linux
	#include <unistd.h>
#endif

using namespace cv;

#define CAM0 0
#define CAM1 1
#define CAM2 2

#define FT_LOGO 				FT_ABS_PATH "img/logo.png"
#define FT_YEL_BORDER 	FT_ABS_PATH "img/yellow.png"
#define FT_WH_BORDER		FT_ABS_PATH "img/white.png"
#define FT_GR_BORDER		FT_ABS_PATH "img/green.png"
#define FT_CIRCLE				FT_ABS_PATH "img/circle.png"
#define FT_BACK 				FT_ABS_PATH "img/ft_background.jpg"
#define FT_NO_SIG				FT_ABS_PATH "img/nosig.png"

/* ui text color */

#define DEF 			7
#define RED				3
#define GREEN			4
#define BLUE			5
#define YELLOW 		6

#define FT_NO_UI	1

/* form drawing debug */

#ifdef FT_FORM
	#define FACE 		"[\033[35m@\033[0m] "
	#define UPPERBODY 	"[\033[33m/\033[0m] "
#endif

#ifdef FT_OPTIMISATION
	#define FTOPT1 		1
#endif

enum { XY_SHIFT = 16, XY_ONE = 1 << XY_SHIFT, DRAWING_STORAGE_BLOCK = (1<<12) - 256 };

/* CU => Camera utils (Draw and other things ..) */

namespace cu{
	class Draw{
		public:
			void drawText(Mat img, const char * text, double x, double y);
			void drawCameraName(Mat img, int idcamera);
			void ftRectangle(Mat& img, Point pt1, Point pt2,const Scalar& color, int thickness, int lineType, int shift);
			void ftpolylines( Mat& img, const Point* const* pts, const int* npts, int ncontours, bool isClosed,
                				const Scalar& color, int thickness, int line_type, int shift );
			void ftPolyLine( Mat& img, const Point* v, int count, bool is_closed,
          						const void* color, int thickness,
          						int line_type, int shift);
			void drawDotted(Mat img,Point start, Point end);
			Mat drawImage(IplImage *img, const char * path, double x, double y, double width, double height);
			Mat drawBorder(IplImage *img, const char * path, double x, double y, double width, double height);
			void overlayImage(Mat &background, Mat &foreground,
  								Mat &output, Point2i location);
			void ftDrawManyImages(char* title, int nArgs, ...);
			int ftCheck(IplImage *img);
			void drawColor(IplImage *img,char * text, int color, double x, double y);
			void drawError(IplImage *img,char * text,double x, double y);
			void drawAction(IplImage *img,char * text, double x, double y);
			void drawOk(IplImage *img,char * text, double x, double y);
			void drawWarnning(IplImage *img,char * text, double x, double y);
	};
	class Timer{
		public:
			Timer();
			~Timer();
			void drawTimer(Mat img, double x, double y);
			void initTimer();
			void drawDate(Mat img, double x, double y);
		private:
			clock_t start;
			double duration;
	};
	class Utils{
		public:
			int cmd(IplImage *img, char cmd[100]);
	};
};


#endif
