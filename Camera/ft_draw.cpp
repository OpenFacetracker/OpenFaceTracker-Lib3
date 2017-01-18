/*
 * Facetracker
 * @authors : Hamza & Godeleine & Quentin
 *
*/
#include <opencv/cv.h>
#include <opencv/highgui.h>
#include <stdio.h>
#include <oft3/core.h>
#include <oft3/ft_draw.h>
#include <iostream>
#ifdef _WIN32
	#include <windows.h>
#endif
#include <time.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>
#include <ctime>

using namespace cv;
using namespace std;
using namespace ft;
using namespace cu;

/* Variable for cmd */
char cmd[100] = {0};
int cincr = 0;

void Draw::drawText(Mat img, const char * text, double x, double y){
  Point org(x,y);
	CvFont * font = new CvFont;
	cvInitFont(font, CV_FONT_HERSHEY_COMPLEX_SMALL, 1.0f, 1.0f, 0, 1, 8);

	putText(img, text, org, FONT_HERSHEY_COMPLEX_SMALL, 1,CV_RGB(255, 255, 255),1,8 ,false);

	return ;
}
void Draw::drawCameraName(Mat img, int idcamera){

	switch(idcamera){
		case CAM0:
			this->drawText(img,"Cam0",530, 450);
			break;
		case CAM1:
			this->drawText(img,"Cam01",530, 450);
			break;
		default:

			break;
	}

	return ;
}
/*
	deprecated function , only works for opencv2
*/
void Draw::ftRectangle(Mat& img, Point pt1, Point pt2,const Scalar& color, int thickness,int lineType, int shift){
	if( lineType == CV_AA && img.depth() != CV_8U )
        lineType = 8;

    CV_Assert( thickness <= 255 );
    CV_Assert( 0 <= shift && shift <= XY_SHIFT );

    double buf[4];
  	//scalarToRawData(color, buf, img.type(), 0);

    Point pt[4];

    pt[0] = pt1;
    pt[1].x = pt2.x;
    pt[1].y = pt1.y;
    pt[2] = pt2;
    pt[3].x = pt1.x;
    pt[3].y = pt2.y;

    if( thickness >= 0 )
       	///this->ftpolylines(img, pt, 4, true, buf, thickness, lineType, shift );
        cout << "test" << endl;
    else
        //cvFillConvexPoly(img, pt, 4, buf, lineType, shift );
        cout << "test" << endl;
}
/*
	deprecated function , only works for opencv2
*/
void Draw::ftpolylines( Mat& img, const Point* const* pts, const int* npts, int ncontours, bool isClosed,
                				const Scalar& color, int thickness, int line_type, int shift ){

	if( line_type == CV_AA && img.depth() != CV_8U )
        line_type = 8;

    CV_Assert( pts && npts && ncontours >= 0 &&
               0 <= thickness && thickness <= 255 &&
               0 <= shift && shift <= XY_SHIFT );

    double buf[4];
    //scalarToRawData( color, buf, img.type(), 0 );

    for( int i = 0; i < ncontours; i++ )
        this->ftPolyLine( img, pts[i], npts[i], isClosed, buf, thickness, line_type, shift );
}
void Draw::ftPolyLine( Mat& img, const Point* v, int count, bool is_closed,
          const void* color, int thickness,
          int line_type, int shift){

	if( !v || count <= 0 )
        return;

    int i = is_closed ? count - 1 : 0;
    int flags = 2 + !is_closed;
    Point p0;
    CV_Assert( 0 <= shift && shift <= XY_SHIFT && thickness >= 0 );

    p0 = v[i];
    for( i = !is_closed; i < count; i++ )
    {
        Point p = v[i];
       // cv::ThickLine( img, p0, p, color, thickness, line_type, flags, shift );
        p0 = p;
        flags = 2;
    }
}
void Draw::ftDrawManyImages(char* title, int nArgs, ...){

  return ;
}
void Draw::overlayImage(Mat &background, Mat &foreground,
  								Mat &output, Point2i location){

	background.copyTo(output);
  // start at the row indicated by location, or at row 0 if location.y is negative.
  for(int y = max(location.y , 0); y < background.rows; ++y)
  {
    int fY = y - location.y; // because of the translation

    // we are done of we have processed all rows of the foreground image.
    if(fY >= foreground.rows)
      break;

    // start at the column indicated by location,

    // or at column 0 if location.x is negative.
    for(int x = max(location.x, 0); x < background.cols; ++x)
    {
      int fX = x - location.x; // because of the translation.

      // we are done with this row if the column is outside of the foreground image.
      if(fX >= foreground.cols)
        break;

      // determine the opacity of the foregrond pixel, using its fourth (alpha) channel.
      double opacity =
        ((double)foreground.data[fY * foreground.step + fX * foreground.channels() + 3])

        / 255.;


      // and now combine the background and foreground pixel, using the opacity,

      // but only if opacity > 0.
      for(int c = 0; opacity > 0 && c < output.channels(); ++c)
      {
        unsigned char foregroundPx =
          foreground.data[fY * foreground.step + fX * foreground.channels() + c];
        unsigned char backgroundPx =
          background.data[y * background.step + x * background.channels() + c];
        output.data[y*output.step + output.channels()*x + c] =
          backgroundPx * (1.-opacity) + foregroundPx * opacity;
      }
    }
  }
}
void Draw::drawDotted(Mat img, Point start, Point end){
	LineIterator it(img, start, end, 8);            // get a line iterator
	for(int i = 0; i < it.count; i++,it++)
    	if ( i%3!=0 ) {(*it)[0] = 50;}         // every 5'th pixel gets dropped, blue stipple line
}
Mat Draw::drawImage(IplImage *img,const char * path, double x, double y, double width, double height){
	Mat form = imread(path,-1);
  Mat test = cvarrToMat(img, false);
  Mat result;

  overlayImage(test, form, result, Point(x,y));
  imshow("Facetracker", result);
	return result;
}
Mat Draw::drawBorder(IplImage *img,const char * path, double x, double y, double width, double height){
  Mat form = imread(path,-1);
  Mat sized_form;
  Mat test = cvarrToMat(img, false);
  Mat result;

  /* resize image */
  Size size(width,height);
  resize(form,sized_form,size);

  overlayImage(test, sized_form, result, Point(x,y));
  imshow("Facetracker", result);
  return result;
}
int Draw::ftCheck(IplImage *img){
  /* do some checking stuff */
  int i = 0 , stat = 0;
  double x = 20 , y = 20, xcmd = 60;
  double incr = 30, xincr = 10;
  char key;
  Utils * utils = new Utils;

  this->drawAction(img,(char *)"Starting ft interface..",x,y);
  y += incr;
  this->drawOk(img,(char *)"ft interface initialised",x,y);
  y += incr;
  /* check camera stream */
  this->drawAction(img,(char *)"Check files..",x,y);
  y += incr;
  this->drawWarnning(img,(char *)"can't found some files",x,y);
  y +=incr;
  this->drawWarnning(img,(char *)"Please provide a valid cmd",x,y);
  y +=incr;
  this->drawColor(img,(char *)"$ > ",DEF,x,y);
  key = cvWaitKey(10);
  /*  handle delete and enter */
  if((int)key == 10){
    /* enter, call function to handle cmd */
    stat = utils->cmd(img, cmd);
  }
  if((int)key == 8){
    /* remove last char , TODO : improve function*/
    cmd[cincr-1] = '\0';
  }
  x +=xincr;
  if((int)key != -1 && (int)key > 31){
    cmd[cincr] = key;
    cincr++;
  }
  this->drawColor(img,cmd,DEF,xcmd,y);
  if(stat == 1){
    return 1;
  }
  if(key == 'q'){
    return 2;
  }

  delete utils;
}
void Draw::drawColor(IplImage *img,char * text, int color, double x, double y){
  CvFont * font = new CvFont;
  cvInitFont(font, CV_FONT_HERSHEY_COMPLEX_SMALL, 1.0f, 1.0f, 0, 1, 8);
  switch(color){
    case RED:
      cvPutText(img, text, cvPoint(x, y), font, CV_RGB(230, 9, 9));
      break;
    case GREEN:
      cvPutText(img, text, cvPoint(x, y), font, CV_RGB(25, 125, 6));
      break;
    case BLUE:
      cvPutText(img, text, cvPoint(x, y), font, CV_RGB(0, 102, 204));
      break;
    case YELLOW:
      cvPutText(img, text, cvPoint(x, y), font, CV_RGB(204, 204, 0));
      break;
    case DEF:
      cvPutText(img, text, cvPoint(x, y), font, CV_RGB(255, 255, 255));
      break;
    default:

      break;
  }

}
void Draw::drawAction(IplImage *img,char * text, double x, double y){
  /* Draw action  */
  CvFont * font = new CvFont;
  cvInitFont(font, CV_FONT_HERSHEY_COMPLEX_SMALL, 1.0f, 1.0f, 0, 1, 8);
  cvPutText(img, (char *)"[", cvPoint(x, y), font, CV_RGB(255, 255, 255));
  this->drawColor(img,(char *)"+",BLUE,(x+10),y);
  cvPutText(img, (char *)"] ", cvPoint(x+27, y), font, CV_RGB(255, 255, 255));
  cvPutText(img, text, cvPoint(x+40, y), font, CV_RGB(255, 255, 255));

}
void Draw::drawError(IplImage *img,char * text, double x, double y){
  /* draw error */
  CvFont * font = new CvFont;
  cvInitFont(font, CV_FONT_HERSHEY_COMPLEX_SMALL, 1.0f, 1.0f, 0, 1, 8);
  cvPutText(img, (char *)"[", cvPoint(x, y), font, CV_RGB(255, 255, 255));
  this->drawColor(img,(char *)"!",RED,(x+10),y);
  cvPutText(img, (char *)"] ", cvPoint(x+20, y), font, CV_RGB(255, 255, 255));
  cvPutText(img, text, cvPoint(x+40, y), font, CV_RGB(255, 255, 255));

}
void Draw::drawOk(IplImage *img,char * text, double x, double y){
  /* draw ok */
  CvFont * font = new CvFont;
  cvInitFont(font, CV_FONT_HERSHEY_COMPLEX_SMALL, 1.0f, 1.0f, 0, 1, 8);
  cvPutText(img, (char *)"[", cvPoint(x, y), font, CV_RGB(255, 255, 255));
  this->drawColor(img,(char *)"o",GREEN,(x+10),y);
  cvPutText(img, (char *)"] ", cvPoint(x+27, y), font, CV_RGB(255, 255, 255));
  cvPutText(img, text, cvPoint(x+40, y), font, CV_RGB(255, 255, 255));

}
void Draw::drawWarnning(IplImage *img,char * text, double x, double y){
   /* draw ok */
  CvFont * font = new CvFont;
  cvInitFont(font, CV_FONT_HERSHEY_COMPLEX_SMALL, 1.0f, 1.0f, 0, 1, 8);
  cvPutText(img, (char *)"[", cvPoint(x, y), font, CV_RGB(255, 255, 255));
  this->drawColor(img,(char *)"#",YELLOW,(x+10),y);
  cvPutText(img, (char *)"] ", cvPoint(x+27, y), font, CV_RGB(255, 255, 255));
  cvPutText(img, text, cvPoint(x+40, y), font, CV_RGB(255, 255, 255));

}
int Utils::cmd(IplImage *img, char cmd[100]){
  /* parse cmd */
  int i =0;
  Draw * draw = new Draw;
  double x = 30 , y = 200;
  int found = 0;
  if(strcmp(cmd,"start") == 0){
    found ++;
    draw->drawAction(img,(char *)"Starting stream..",x,y);
    return 1;
  }

  if(!found){
    /* empty the cmd */
    if(cmd != ""){
      for(i = 0;i<strlen(cmd);i++){
        cmd[i] = '\0';
      }
    }
    draw->drawError(img,(char *)"can't found your cmd , please use `help`",x,y);
  }

  delete draw;
}
Timer::Timer(){
	//start = clock(); /* init the clock */
}
Timer::~Timer(){
	/* destructor */
}
void Timer::initTimer(){
	start = clock(); /* init the clock */
}
void Timer::drawTimer(Mat img, double x, double y){
	Draw * draw = new Draw();
	char drawt[100];
	/* update the duration */
	duration = (clock() - start)/(double) CLOCKS_PER_SEC;
	//cout << duration << endl;
	sprintf(drawt,"Time %0.1f Sec",duration);
	draw->drawText(img, drawt, x, y);

	return ;
}
void Timer::drawDate(Mat img, double x, double y){
  Draw * draw = new Draw();
  time_t now = time(0);

  char* dt = ctime(&now);

  draw->drawText(img, dt, x, y);

  return ;
}
