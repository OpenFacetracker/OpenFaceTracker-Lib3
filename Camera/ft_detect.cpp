/*
 * Facetracker
 * @authors : Team OpenFaceTracker
 *
*/
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/face.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/objdetect.hpp>
#include <oft3/core.h>
#include <oft3/ft_draw.h>
#include <oft3/recognition/ft_recognise.h>
#include <oft3/ft_person.h>
#include <iostream>
#include <time.h>
#include <string.h>
#include <fstream>

using namespace cv;
using namespace std;
using namespace ft;
using namespace cu;

void Camera::listCamera(){
	/* list all camera
		if we use linux , we sould list /dev/video*
		output will be on the tmp folder
	*/
	ifstream output;
	char s[100];
	int id;

#ifdef linux

	output.open("/tmp/ftcamera.txt");
	if(!output.good()){
		cout << FT_ERROR << "can't open tmp file" << endl;
		return ;
	}else{
		output.getline(s,100);
		cout << "OS : linux" << endl;
		cout << "ID\t" << "Name\t" << "Dev" << endl;
		cout << "------------------------" << endl;
		/* loop every camera */
		id = atoi(s);
		cout << id << "\t" << "CAM" << id << "\t" << s << endl;
	}
	/* remove tmp file */
	system("rm /tmp/ftcamera.txt");
#endif
#ifdef _WIN32
	cout << "OS : Windows" << endl;
	cout << "ID\t" << "Name\t" << "Dev" << endl;
	cout << "------------------------" << endl;
#ifdef FT_WINCAM_LIST
	HRESULT hr = CoInitializeEx(NULL, COINIT_MULTITHREADED);
    if (SUCCEEDED(hr))
    {
        IEnumMoniker *pEnum;

        hr = this->EnumerateDevices(CLSID_VideoInputDeviceCategory, &pEnum);
        if (SUCCEEDED(hr))
        {
            this->DisplayDeviceInformation(pEnum);
            pEnum->Release();
        }
        hr = this->EnumerateDevices(CLSID_AudioInputDeviceCategory, &pEnum);
		if (SUCCEEDED(hr))
        {
	char s[100];
	int id;

	if(FAILED(hr)){
		cout << FT_ERROR << "no device " << endl;
	}
#endif

#endif

	return ;
}
#ifdef FT_TEST_PERFORMANCE
int Camera::testPerformance(char * stream){
	if(strstr(stream,"CAM")){
    		VideoCapture cap((int)(stream[strlen(stream)-1] - '0')); // open the default camera
    	}
	VideoCapture cap(stream);
	if(!cap.isOpened())  // check if we succeeded
	char s[100];
	int id;

    	for(;;)
    	{
        	Mat frame;
        	cap >> frame; // get a new frame from camera
        	cvtColor(frame, edges, CV_BGR2GRAY);
        	//GaussianBlur(edges, edges, Size(7,7), 1.5, 1.5);
        	//Canny(edges, edges, 0, 30, 3)
					frame = this->detectFace(frame);
        	imshow("Facetracker", edges);
        	if(waitKey(30) >= 0) break;
    	}
    	return 0;

}
Mat Camera::detectFace(Mat image)
{
	double min_face_size=20;
	double max_face_size=200;
 	// Load Face cascade (.xml file)
	 CascadeClassifier face_cascade( "Classifiers
	char s[100];
	int id;
/haarcascade_frontalface_alt.xml" );

 	// Detect faces
	char s[100];
	int id;

 	std::vector<Rect> faces;

 	face_cascade.detectMultiScale( image, faces, 1.2, 2, 0|CV_HAAR_SCALE_IMAGE, Size(min_face_size, min_face_size),Size(min_face_size, max_face_size) );

	 // Draw circles on the detected faces
 	for( int i = 0; i < faces.size(); i++ )
 	{
 		min_face_size = faces[0].width*0.8;
  		max_face_size = faces[0].width*1.2;
  		Point center( faces[i].x + faces[i].width*0.5, faces[i].y + faces[i].height*0.5 );
  		ellipse( image, center, Size( faces[i].width*0.5, faces[i].height*0.5), 0, 0, 360, Scalar( 255, 0, 255 ), 4, 8, 0 );
 	}
 	return image;
}
	char s[100];
	int id;

#endif
int Camera::cOpen(char * stream)
{
	Console *console = new Console;
	FtUtils *utils 	 = new FtUtils;

	/* call ft -c for checking env */

#ifdef linux
#ifndef FT_LIB
	 //system("xterm -e ./facetracker -c");
#endif
#endif

	this->flag_stop = 0;
	console->init_color();
	cout << FT_ACTION << "opening camera " << endl;
	char KeyStop = 0; // if we press "Q", the program will stop
	CvHaarClassifierCascade * cascade = NULL;
	CvMemStorage *storage = NULL; // To define the memory space used during the treatment
	srand(time(NULL));
#ifdef FT_TEST_PERFORMANCE
	this->testPerformance(stream);
#else
	this->ViolaJones(cascade, storage, KeyStop, stream);
#endif

	delete console;
	delete utils;
	return 0;
}
CvCapture * Camera::getStream(char * stream){
	/* return stream */
	CvCapture *capture;
	char out[200];
	char result[200];
	ifstream gLink;

	if(strstr(stream,"http://youtube")){
		/* resolve youtube link , using youtube-dl */
		cout << FT_ACTION << "resolving youtube stream .." << endl;
	#ifdef linux
		sprintf(out,"youtube-dl -g %s > /tmp/ftyoutube.log",stream);
		system(out);
		/* open tmp file to get the google link */
		gLink.open("/tmp/ftyoutube.log");
		if(gLink.good()){
			gLink.getline(result,200);
			try{
				//capture = cvCreateFileCapture(result);
				capture = cvCaptureFromFile(result);
				return capture;
			}catch(cv::Exception& e){
				cout << FT_ERROR << "can't resolve youtube link" << endl;
				return NULL;
			}
		}else{
			cout << FT_ERROR << "error while reading tmp file" << endl;
		}
	#endif
	}
	if(strstr(stream,"CAM")){
		/* Camera opening */
		try{
			capture = cvCreateCameraCapture((int)(stream[strlen(stream)-1] - '0'));
			return capture;
		}catch(cv::Exception& e){
			cout << FT_ERROR << "can't connect to camera => " << e.msg << endl;
			return NULL;
		}
	}else{
		/* rtsp */
		try{
			cout << FT_ACTION << "resolving stream .." << endl;
			//capture = cvCreateFileCapture(stream);
			capture = cvCaptureFromFile(stream);
			return capture;
		}catch(cv::Exception& e){
			cout << FT_ERROR << "can't resolve stream => " << e.msg << endl;
			return NULL;
		}

	}

}
void Camera::ViolaJones(CvHaarClassifierCascade * cascade, CvMemStorage *storage, char KeyStop, char * stream)
{
	unsigned int ready = 0;
	Timer * timer   = new Timer(); /* init ft timer */
	Draw  * draw	= new Draw();
	CvCapture *capture;  //video stream recovered by the webcam //
	IplImage *img;
	Mat new_work;
	const char *filename 	= FT_ABS_PATH "Classifiers/haarcascade_frontalface_alt.xml";// we get the classifier
	const char *eyefile 	= FT_ABS_PATH "Classifiers/haarcascade_eye.xml";
	const char *mouthfile = FT_ABS_PATH "Classifiers/haarcascade_mcs_mouth.xml";
	const char *nozefile	= FT_ABS_PATH "Classifiers/haarcascade_mcs_nose.xml";
	const char *smilefile = FT_ABS_PATH "Classifiers/haarcascade_smile.xml";
	int Compteur = 0, nbnoze = 0, nbeyes = 0, etat = 0;
	double fps = 0;
	ifstream fstrm;
	char devPath[100];

	CvHaarClassifierCascade * eyecascad 	= NULL;
	CvHaarClassifierCascade * mouthcascad 	= NULL;
	CvHaarClassifierCascade * nozecascad 	= NULL;
	CvHaarClassifierCascade * smilecascad   = NULL;

	timer->initTimer();

	/* Classifier loading
	cvLoadHaarClassifierCascade(filename which contains .xml file, window detection (px, px))*/
	/*
	cascade 	= (CvHaarClassifierCascade*)cvLoadHaarClassifierCascade( filename, cvSize(24, 24) );
	eyecascad 	= (CvHaarClassifierCascade*)cvLoadHaarClassifierCascade( eyefile, cvSize(24, 24) );
	mouthcascad = (CvHaarClassifierCascade*)cvLoadHaarClassifierCascade( mouthfile, cvSize(24, 24) );
	nozecascad	= (CvHaarClassifierCascade*)cvLoadHaarClassifierCascade( nozefile, cvSize(24, 24) );
	*/
	cascade 	= (CvHaarClassifierCascade*)cvLoad( filename, 0, 0, 0  );
	eyecascad 	= (CvHaarClassifierCascade*)cvLoad( eyefile, 0, 0, 0  );
	mouthcascad     = (CvHaarClassifierCascade*)cvLoad( mouthfile, 0, 0, 0 );
	nozecascad	= (CvHaarClassifierCascade*)cvLoad( nozefile, 0, 0, 0 );
	smilecascad     = (CvHaarClassifierCascade*)cvLoad( smilefile,0,0,0);


	capture = this->getStream(stream);

	if(capture == NULL){
		/* draw no signal */
		cout << FT_ERROR << "ft : No signal" << endl;
		while(KeyStop != 'q'){
			cout << FT_ACTION << "seeking for signal .." << endl;
			img = cvLoadImage(FT_NO_SIG,-1);
			capture = this->getStream(stream);
			if(capture != NULL){
				cout << FT_OK << "signal found " << endl;
				break;
			}
			cvShowImage("Facetracker", img);
			KeyStop = cvWaitKey(10);
		}
	}

	/* Initialisation de l’espace memoire */
	storage = cvCreateMemStorage(0);

	/* Window creation */
	//cvNamedWindow("Window-FT", 1);
#ifndef FT_LIB
	cvNamedWindow( "Facetracker", CV_WINDOW_AUTOSIZE );
#endif

	/* init graphic check */
	cout << FT_ACTION << "init Graphic check.." << endl;
	cout << FT_OK	  << "waiting for cmd"		<< endl;

	/* treatment loop */
	while(KeyStop != 'q')
	{

	#ifdef FT_NO_UI
		ready = 1;
	#endif

	/* check if stop */
	if(this->flag_stop == 1)
		return ;

	//capture = this->getStream(stream);


		if(ready == 1){
			img = cvQueryFrame(capture);
			new_work = cvarrToMat(img).clone();
			IplImage * newframe = new IplImage(new_work);
			/* grabing frame */
			etat = cvGrabFrame(capture);
			/* getting fps informations */
			//fps = cvGetCaptureProperty(capture,CV_CAP_PROP_FPS);
			/* draw Date and camera name  */
			timer->drawDate(new_work, (double)20, (double)20);
			//draw->drawCameraName(img, CAM0);
			/* detect smile  */
		#ifdef FT_DETECT_SMILE
			this->detectSmile(img, smilecascad, storage);
		#endif
			/* detect mouth */
		#ifdef FT_DETECT_MOUTH
			this->detectMouth(img, mouthcascad, storage);
		#endif
			/* detect noze */
		#ifdef FT_DETECT_NOZE
			nbnoze = this->detectNoze(img, newframe, nozecascad, storage);
		#endif
			/* detect eyes */
		#ifdef FT_DETECT_EYES
			nbeyes = this->detectEyes(img, newframe, eyecascad, storage);
		#endif
			/* if no eyes and no noze in the picture , then no face drawing */
			this->detectFaces(img, newframe, cascade, storage, &Compteur);
			if(!nbnoze && !nbeyes){
				/* detect faces */
				//this->detectFaces(img, cascade, storage, &Compteur);
			}
		}else{
			img = cvLoadImage(FT_BACK,-1);
			ready = draw->ftCheck(img);
			if(ready == 2){

				capture = this->getStream(stream);

				break;
			}
		#ifndef FT_LIB
			cvShowImage("Facetracker", img);
		#endif
			/* call ft check */
		}
		KeyStop = cvWaitKey(10);
	}

	cout << FT_ERROR << "closing.." << endl;

	/* Free memory */
	delete timer;
	delete draw;
	cvReleaseCapture(&capture);
	cvDestroyWindow("Facetracker");
	cvReleaseHaarClassifierCascade(&cascade);
	cvReleaseMemStorage(&storage);
}
vector<Person*> Camera::detectFaces(IplImage *img,  IplImage *newframe, CvHaarClassifierCascade * cascade, CvMemStorage *storage, int *Compteur)
{
	Draw * draw = new Draw(); /* init drawing class */
	Timer * timer = new Timer();
	Recognise * recognise = new Recognise();
	double width = 0;
	double height = 0;
	double x = -150 , y = -150;
	int detected = 0 , prediction = MATCHING , found = UNKNOWN;
	int  i = 0, j = rand()%5;
	Mat image = Mat::zeros( 400, 400, CV_8UC3 );
	Mat clone = cvarrToMat(img).clone();
	Mat logo;
	IplImage *imgGrey = NULL;
	vector<Person*> persons;
	double coef = 2.0f;

	// cvHaarDetectObjects(Camera stream, classifier, memory space, 1.1 = scale factor, 3 ???, if you want to add filters,detection Window size)
	CvSeq *faces = cvHaarDetectObjects(img, cascade, storage, 1.1, 3, 0, cvSize(40,40));

	this->nbperson = faces->total;
	// for loop that reviews all the detected faces in a frame and draw a rectangle around//
	for(i=0; i<(faces?faces->total:0); i++)
	{
		CvRect *r = (CvRect*)cvGetSeqElem(faces, i);
		this->rdetect = r;
		Person * per = new Person();
	#ifdef FT_OPTIMISATION
		cvRectangle(img, cvPoint(r->x, r->y), cvPoint(r->x + r->width, r->y + r->height), CV_RGB(236, 221, 10), 3, 5, 0);
	#endif
		/* table for all faces so as to draw them */
	#ifdef FT_FORM
	#ifndef FT_LIB
		cout << FACE << "face number " << i << " : rendering image" << endl;
	#endif
	#endif
		/* Draw persone name . admin for test */
		//draw->drawText(img, "Admin",r->x,r->y -10);
	#ifdef FT_FORM
	#ifndef FT_LIB
		cout << FACE << "face number " << i << " : rendering name" << endl;
	#endif
	#endif
	#ifdef FT_TEST_RECOGNISE
	/* if FT_TEST_RECOGNITION is enabled , then use it */
	imgGrey = recognise->EqualizingPicture(r, newframe);
	prediction = recognise->Crop(imgGrey, r, (*Compteur)++);
	this->id_predicted = prediction;
	cout << FT_OK << "face prediction = " << prediction << endl;
	switch(prediction){
		case 0:
			draw->drawText(clone, "None",r->x,r->y - 10);
			found = 0;
			break;
		case 2:
			draw->drawText(clone, "Obama",r->x,r->y - 10);
			found = RECOGNIZED;
			break;
		case 3:
			draw->drawText(clone, "Neymar",r->x,r->y - 10);
			break;
		case 4:
			draw->drawText(clone, "Pique",r->x,r->y - 10);
			found = RECOGNIZED;
			break;
		case 5:
			draw->drawText(clone, "Messi",r->x,r->y - 10);
			//found = RECOGNIZED;
			break;
		case 6:
			draw->drawText(clone, "Hamza",r->x,r->y - 10);
			found = RECOGNIZED;
			break;
		case 7:
			draw->drawText(clone, "Godeleine",r->x,r->y - 10);
			found = RECOGNIZED;
			break;
		case 8:
			draw->drawText(clone, "Quentin",r->x,r->y - 10);
			found = RECOGNIZED;
			break;
		case 9:
			draw->drawText(clone, "Worphy",r->x,r->y - 10);
			found = RECOGNIZED;
			break;
		case UNKNOWN:
			draw->drawText(clone, "Unknown",r->x,r->y - 10);
			found = UNKNOWN;
			break;
		default:
			draw->drawText(clone, "matching..",r->x,r->y - 10);
			break;
	}
	#endif
	#ifdef FT_OPTIMISATION
			if (found == UNKNOWN)
					cvRectangle(img, cvPoint(r->x, r->y), cvPoint(r->x + r->width, r->y + r->height), CV_RGB(255, 255, 255), 1, 8, 0);
			if (found == RECOGNIZED)
					cvRectangle(img, cvPoint(r->x, r->y), cvPoint(r->x + r->width, r->y + r->height), CV_RGB(0, 255, 0), 1, 8, 0);
	#endif
		/* get width and height of rect every time
			r->width & r->height
		 */
		x = r->x;
		y = r->y;
		width = r->width;
		height = r->height;
		/* add person to vector */
		per->setRect(r);
		per->setName("");
		per->setId(i);
		persons.push_back(per);
		detected ++;
	}
	if (faces->total != 0 && j == 1)
	{
		/*A chaque incrémentation de ta variable (à chaque prise de photo) on regarde si le fichier
		screenshoti.bmp existes et tu continues d’incrémenter afin d’être sûr de ne pas écraser de fichier.*/
		#ifndef FT_LIB
		cout << FT_ACTION << "taking picture " << endl;
		#endif
		//this->SaveImage("ScreenShot", img, Compteur);
		(*Compteur)++;
		#ifndef FT_LIB
		DEBUGP ("face detected");
		#endif
		/* try to detect if male or female , and also detect emotion */
	}
	#ifndef FT_LIB
	cvShowImage("Facetracker", img);
	#endif
	/* Draw facetracker logo */
	//draw->drawImage(img , FT_LOGO, 20,420, width,height);
	/* Draw test */
#ifndef FT_OPTIMISATION
	if(x && y && detected){
		if (found == UNKNOWN)
			logo = draw->drawBorder(img , FT_CIRCLE, x-(width*( (coef - 1)/2 )),y - (height*( (coef - 1)/2 )), width*coef,height*coef);
		if (found == RECOGNIZED)
			logo = draw->drawBorder(img , FT_CIRCLE, x-(width*( (coef - 1)/2 )),y -(height*( (coef - 1)/2 )), width*coef,height*coef);
	}
#endif
	delete draw;
	delete timer;
	delete recognise;
	return persons;
}
int Camera::detectEyes(IplImage *img, IplImage *newframe, CvHaarClassifierCascade * cascade, CvMemStorage *storage){
	double width = 0;
	double height = 0;
	double x = -150 , y = -150;
	int detected = 0;
	int  i = 0, j = rand()%5;
	int nbeyes = 0;
	Mat image = Mat::zeros( 400, 400, CV_8UC3 );

	CvSeq *eyes = cvHaarDetectObjects(newframe, cascade, storage, 1.1, 3, 0, cvSize(40,40));

	for(i=0; i<(eyes?eyes->total:0); i++)
	{
		CvRect *r = (CvRect*)cvGetSeqElem(eyes, i);
		//cvRectangle(img, cvPoint(r->x, r->y), cvPoint(r->x + r->width, r->y + r->height), CV_RGB(236, 221, 10), 3, 5, 0);
		cvCircle(img, cvPoint(r->x + r->width*0.5 , r->y + r->height*0.5),2,CV_RGB(255, 255, 255), 3, 5, 0);
		nbeyes = i;
	}
	if (eyes->total != 0 && j == 1)
	{
		DEBUGP ("eyes detected");
	}
	#ifndef FT_LIB
	cvShowImage("Facetracker", img);
	#endif
	return eyes->total;

}
int Camera::detectMouth(IplImage *img, CvHaarClassifierCascade * cascade, CvMemStorage *storage){
	double width = 0;
	double height = 0;
	double x = -150 , y = -150;
	int detected = 0;
	int  i = 0, j = rand()%5;
	Mat image = Mat::zeros( 400, 400, CV_8UC3 );

	CvSeq *mouth = cvHaarDetectObjects(img, cascade, storage, 1.1, 3, 0, cvSize(40,40));

	for(i=0; i<(mouth?mouth->total:0); i++)
	{
		CvRect *r = (CvRect*)cvGetSeqElem(mouth, i);
		cvRectangle(img, cvPoint(r->x, r->y), cvPoint(r->x + r->width, r->y + r->height), CV_RGB(236, 221, 10), 2, 8, 0);
		//cvCircle(img, cvPoint(r->x + r->width*0.5 , r->y + r->height*0.5),2,CV_RGB(255, 255, 255), 3, 5, 0);
	}
	if (mouth->total != 0 && j == 1)
	{
		DEBUGP ("mouth detected");
	}
	#ifndef FT_LIB
	cvShowImage("Facetracker", img);
	#endif
	return 0;

}
int Camera::detectNoze(IplImage *img, IplImage *newframe, CvHaarClassifierCascade * cascade, CvMemStorage *storage){
	double width = 0;
	double height = 0;
	double x = -150 , y = -150;
	int detected = 0;
	int  i = 0, j = rand()%5;
	int nbnoze = 0;

	Mat image = Mat::zeros( 400, 400, CV_8UC3 );

	CvSeq *noze = cvHaarDetectObjects(newframe, cascade, storage, 1.1, 3, 0, cvSize(40,40));

	for(i=0; i<(noze?noze->total:0); i++)
	{
		CvRect *r = (CvRect*)cvGetSeqElem(noze, i);
		//cvRectangle(img, cvPoint(r->x, r->y), cvPoint(r->x + r->width, r->y + r->height), CV_RGB(236, 221, 10), 2, 8, 0);
		cvCircle(img, cvPoint(r->x + r->width*0.5 , r->y + r->height*0.5),2,CV_RGB(255, 255, 255), 3, 5, 0);
		nbnoze = i;
	}
	if (noze->total != 0 && j == 1)
	{
		DEBUGP ("noze detected");
		/* if we found noze , we call face detection */
		///this->detectFaces(img, cascade, storage, &Compteur);
	}
	#ifndef FT_LIB
	cvShowImage("Facetracker", img);
	#endif
	return noze->total;
}
int Camera::detectSmile(IplImage *img, CvHaarClassifierCascade * cascade, CvMemStorage *storage){
        double width = 0;
        double height = 0;
        double x = -150 , y = -150;
        int detected = 0;
        int  i = 0, j = rand()%5;
        Mat image = Mat::zeros( 400, 400, CV_8UC3 );

        CvSeq *smile = cvHaarDetectObjects(img, cascade, storage, 1.1, 3, 0, cvSize(40,40));

        for(i=0; i<(smile?smile->total:0); i++)
        {
                CvRect *r = (CvRect*)cvGetSeqElem(smile, i);
                //cvRectangle(img, cvPoint(r->x, r->y), cvPoint(r->x + r-$
                cout << FACE << "smiling :D" << endl;
		//cvCircle(img, cvPoint(r->x + r->width*0.5 , r->y + r-$
        }
        if (smile->total != 0 && j == 1)
        {
                DEBUGP ("Smile detected");
        }

        cvShowImage("Facetracker", img);
        return 0;

}

#ifdef FT_TEST_RECOGNISE
void Camera::testRecognise(){
	/* test function for recognising a person */
	string fn_csv = string(PATH_DB);
	vector<Mat> images;
    	vector<int> labels;
    	Mat face = imread("faces/hamza.jpg",-1);
			Mat face_resized;
    	int prediction;

    	try {
        	this->parse_csv(fn_csv, images, labels);
    	} catch (cv::Exception& e) {
        	cout << FT_ERROR << "Error opening file \"" << fn_csv << "\". Reason: " << e.msg << endl;
        	exit(1);
    	}
	try{
		resize(face, face_resized, Size(100, 100), 1.0, 1.0, INTER_CUBIC);
		Ptr<face::FaceRecognizer> model = face::createFisherFaceRecognizer();
		model->train(images, labels);
		prediction = model->predict(face_resized);
		cout <<FT_DEBUG << "Face Prediction = " << prediction << endl;
	}catch(cv::Exception& e){
		cout << FT_ERROR << "Opencv Error => " << e.msg << endl;
		return ;
	}
}

void Camera::parse_csv(const string& filename, vector<Mat>& images, vector<int>& labels){
	char separator = ';';
	ifstream file(filename.c_str(), ifstream::in);
    if (!file) {
        string error_message = "No valid input file was given, please check the given filename.";
        CV_Error(CV_StsBadArg, error_message);
    }
    string line, path, classlabel;
    while (getline(file, line)) {
        stringstream liness(line);
        getline(liness, path, separator);
        getline(liness, classlabel);
        if(!path.empty() && !classlabel.empty()) {
            images.push_back(imread(path, 0));
            labels.push_back(atoi(classlabel.c_str()));
        }
    }

}
#endif
void Camera::SaveImage(char *filename, IplImage *img, int *Compteur)
{
	char path[255]= {0};
	char str[20];
	char extension[10] = ".jpg";
	cout << FT_ACTION << "saving picture" << endl;
#ifdef _WIN32
	itoa(*Compteur, str, 10);
#endif
#ifdef linux
	*Compteur = atoi(str);
#endif
	strcpy(path, filename);
	strcat(path, str);
	strcat(path, extension);
	printf("%s", path);

	if (!cvSaveImage(path, img))
	{
		cout << FT_ERROR <<"cvSaveImage failed for " << endl;
    // break or exit()
	}

}
/*
#ifdef linux
char *strrev(char *str)
{
      char *p1, *p2;

      if (! str || ! *str)
            return str;
      for (p1 = str, p2 = str + strlen(str) - 1; p2 > p1; ++p1, --p2)
      {
            *p1 ^= *p2;
            *p2 ^= *p1;
            *p1 ^= *p2;
      }
      return str;
}
int itoa(int num, unsigned char* str, int len, int base)
{
	int sum = num;
	int i = 0;
	int digit;
	if (len == 0)
		return -1;
	do
	{
		digit = sum % base;
		if (digit < 0xA)
			str[i++] = '0' + digit;
		else
			str[i++] = 'A' + digit - 0xA;
		sum /= base;
	}while (sum && (i < (len - 1)));
	if (i == (len - 1) && sum)
		return -1;
	str[i] = '\0';
	strrev(str);
	return 0;
}
#endif
*/

/*
	Windows
	to list available cameras
*/
#ifdef FT_WINCAM_LIST
HRESULT Camera::EnumerateDevices(REFGUID category, IEnumMoniker **ppEnum){
    // Create the System Device Enumerator.
    ICreateDevEnum *pDevEnum;
    HRESULT hr = CoCreateInstance(CLSID_SystemDeviceEnum, NULL,
        CLSCTX_INPROC_SERVER, IID_PPV_ARGS(&pDevEnum));

    if (SUCCEEDED(hr))
    {
        // Create an enumerator for the category.
        hr = pDevEnum->CreateClassEnumerator(category, ppEnum, 0);
        if (hr == S_FALSE)
        {
            hr = VFW_E_NOT_FOUND;  // The category is empty. Treat as an error.
        }
        pDevEnum->Release();
    }
    return hr;
}


void Camera::DisplayDeviceInformation(IEnumMoniker *pEnum){
    IMoniker *pMoniker = NULL;

    while (pEnum->Next(1, &pMoniker, NULL) == S_OK)
    {
        IPropertyBag *pPropBag;
        HRESULT hr = pMoniker->BindToStorage(0, 0, IID_PPV_ARGS(&pPropBag));
        if (FAILED(hr))
        {
            pMoniker->Release();
            continue;
        }

        VARIANT var;
        VariantInit(&var);

        // Get description or friendly name.
        hr = pPropBag->Read(L"Description", &var, 0);
        if (FAILED(hr))
        {
            hr = pPropBag->Read(L"FriendlyName", &var, 0);
        }
        if (SUCCEEDED(hr))
        {
            cout << var.bstrVal << endl;
            VariantClear(&var);
        }

        hr = pPropBag->Write(L"FriendlyName", &var);

        // WaveInID applies only to audio capture devices.
        hr = pPropBag->Read(L"WaveInID", &var, 0);
        if (SUCCEEDED(hr))
        {
            cout << "WaveIn ID: " << var.lVal << endl;
            VariantClear(&var);
        }

        hr = pPropBag->Read(L"DevicePath", &var, 0);
        if (SUCCEEDED(hr))
        {
            // The device path is not intended for display.
            cout << "Device path:" << var.bstrVal << endl;
            VariantClear(&var);
        }

        pPropBag->Release();
        pMoniker->Release();
    }
}
#endif

void Camera::cClose(){
		/* do some check and then close  */
		this->flag_stop = 1;
}
