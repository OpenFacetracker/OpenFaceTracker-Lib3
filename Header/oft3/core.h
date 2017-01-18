/*
 * Facetracker
 * OFT 3
 * @authors : Team OpenFaceTracker
 *
*/
#ifndef HCORE
#define HCORE
#include <math.h>
#include <ctime>
#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <vector>
#include <opencv/cv.h>
#include <opencv/highgui.h>
#include <oft3/ft_draw.h>
#include <oft3/ft_person.h>

/* add some facetracker options
============================== */

#define FT_TEST_RECOGNISE 1
#ifndef FT_LIB
  #define FT_ABS_PATH   ""
#endif
/*
============================== */

#ifdef FT_LIB
  /* optimising facetracker for lib dev */
  #define FT_NO_PRINT   1
  #define FT_NO_TEST    1
  #define FT_ABS_PATH   "/home/naper/code/facetracker/ftLib/"
  #define FT_OPTIMISATION 1
#endif

/* all detection */

#define FT_DETECT_EYES  1
#define FT_DETECT_NOZE  1

#ifdef FT_ALLOW_EXCEPT
 	#include <stdexcept>
#endif

#ifdef FT_GUI_QT
    #define FT_USE_COLOR        1
    #define FT_DEBUG_ENABLED    1
    #define FT_FORM             1
    #define FT_TEST_RECOGNISE   1
    #define FT_OPTIMISATION     1
#endif

#ifdef _WIN32
	#include <windows.h>
	#include <dshow.h>
	#pragma comment(lib, "strmiids")
	#define FT_DEBUG_ENABLED	0
	#define FT_USE_COLOR		1
	#define FT_NO_UI		1
#endif

#ifdef FT_USE_COLOR				/* if we wanna use color.h */
	#include <oft3/color.h>
#endif

/* DEBUG OPTION */
#ifdef FT_DEBUG_ENABLED
	#ifdef __GNUG__					/* g++ and gcc are using __FUNCTION__ macro */
 		#define DEBUGP(X) printf(FT_DEBUG "ft:%s:%d:%s() %s \n", __FILE__, __LINE__, __FUNCTION__, X)
	#endif
 	#ifdef _WIN32
 		/* VC use __func__ */
 		#define DEBUGP(X) printf(FT_DEBUG "ft:%s() %s \n", __FILE__, X)
 	#endif
#endif

#define VERSION 	"2.4.1"
#define CONFIG 		"Config/ft.conf"

/* OPTION FOR WRITE FUNCTION */

#define INLINE 		1
#define FORMAT 		2
#define WITHOUT 	3

/* config struct */

typedef struct s_Config{
	char * val;
}conf;
/* getopt */
#ifdef _WIN32
extern int optind, opterr;
extern char *optarg;
#endif

/*  struct for log */

typedef struct sLog{
	char * string;
	struct sLog * pNext;
}llog;

namespace ft{

	class Console{
		public:
			/* fix deprecated conversion */
			void writeError(const char * msg, int option);
			void testFunction_result();
			void function_result(int Error, const char *NomFonction);
			void writeDone(const char * msg, int option);
			void writeAction(const char * msg, int option);
			void header();
			void help();
			void init_color();
		private:
			void color(int font_color, int back_color);

	};
	class Config{
		public:
			char * getElem(const char * elem);
		private:
			void parseConfig(char line[100], const char *elem, char * result);
			char * convert(char * result);
	};
	class Log{
		public:
			Log(const char * name);			/* constructor */
			~Log();							/* destructor  */
			void addLog(char * text);
			void writeLog();
			void  freeLog();
		private:
			const char * logname;
			llog * log;
	};
	class Database{
		public:
			Database(const char * file);
			~Database();
			void write();
			void read();
	};
	class Parser{
		public:
			void parse(int argc, char ** argv);
			void xmltest(char * path);			/* function for tesing xml */
		private:
			void win32parse(int argc, char **argv);
			int win32getopt(int argc, char *argv[], char *optstring);
	};
	class Camera{
		public:
			int cOpen(char * stream);
			void listCamera();
      int id_predicted;
      int nbperson;
      CvRect *rdetect;
      void cClose();
      int flag_stop;
			void SaveImage(char *filename, IplImage *img, int *Compteur);
      std::vector<Person*> detectFaces(IplImage *img, IplImage *newframe, CvHaarClassifierCascade * cascade, CvMemStorage *storage, int *Compteur);
      int detectEyes(IplImage *img, IplImage *newframe, CvHaarClassifierCascade * cascade, CvMemStorage *storage);
      int detectMouth(IplImage *img, CvHaarClassifierCascade * cascade, CvMemStorage *storage);
      int detectNoze(IplImage *img,IplImage *newframe, CvHaarClassifierCascade * cascade, CvMemStorage *storage);
      int detectSmile(IplImage *img, CvHaarClassifierCascade * cascade, CvMemStorage *storage);
			void ViolaJones(CvHaarClassifierCascade * cascade, CvMemStorage *storage, char KeyStop, char * stream);
			CvCapture * getStream(char * stream);
    private:
			void testRecognise();
			void parse_csv(const string& filename, vector<Mat>& images, vector<int>& labels);
		#ifdef _WIN32
			void DisplayDeviceInformation(IEnumMoniker *pEnum);
			HRESULT EnumerateDevices(REFGUID category, IEnumMoniker **ppEnum);
		#endif
			int testPerformance(char * stream);
			Mat detectFace(Mat image);
	};
	class FtUtils{
		public:
			void cmdParser(char * cmd);
      const char * version();
			int checkEnv();
	};
}
#endif
