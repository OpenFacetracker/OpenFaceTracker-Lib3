/*
 * Facetracker
 * @authors : Team OpenFaceTracker
 *
*/

#include <oft3/recognition/ft_recognise.h>

using namespace cv;
using namespace std;

/*
int detectFaces(IplImage *img, CvHaarClassifierCascade * cascade, CvMemStorage *storage, int *Compteur, char *filename)
{
	srand(time(NULL));
	int  i = 0, j = rand()%5;
	IplImage *imgGrey = NULL;
	// cvHaarDetectObjects(Camera stream, classifier, memory space, 1.1 = scale factor, 3 ???, if you want to add filters,detection Window size)
	CvSeq *faces = cvHaarDetectObjects(img, cascade, storage, 1.1, 3, 0, cvSize(40,40));

	// for loop that reviews all the detected faces in a frame and draw a rectangle around//
	for(i=0; i<(faces?faces->total:0); i++)
	{
		CvRect *r = (CvRect*)cvGetSeqElem(faces, i);
		cvRectangle(img, cvPoint(r->x, r->y), cvPoint(r->x + r->width, r->y + r->height), CV_RGB(0, 255, 0), 3, 5, 0);
		imgGrey = EqualizingPicture(filename, r, img);
		Crop(imgGrey, r, (*Compteur)++);

	}

	cvShowImage("Window-FT", img);

	return 0;
}
*/
void Recognise::SaveImage(char *filename, Mat img, int *Compteur)
{
	char path[255]= {0};
	char str[20];
	char extension[10] = ".jpg";

	strcpy(path, filename);
	strcat(path, str);
	strcat(path, extension);
	printf("%s", path);

	if (!imwrite(path, img))
	{
		printf("!!! cvSaveImage failed for %s\n", path);
		// break or exit()
	}

}

IplImage * Recognise::GoGetPictures(char *filename, int *Compteur)
{
	IplImage *image = 0; // Chargement d'un fichier
	char path[255]= {0};
	char extension[10] = ".jpg";
	char str[10];

	//itoa(*Compteur, str, 10);
	strcpy(path, filename);
	strcat(path, str);
	strcat(path, extension);
	image = cvLoadImage(path, 1);

	if (!image)
		printf("l'image n'exsite pas\n");
	/*// Cr�ation des fen�tres
	cvNamedWindow("File",1);
	// Affichage de l'image1 dans la fen�tre Geometry
	cvShowImage("File", image);
	// Attente infinie que l'utilisateur appuie sur une touche (IMPORTANT !!!)
	cvWaitKey();
	*/

	return image;
}

IplImage * Recognise::EqualizingPicture(CvRect *r,  IplImage *imageSrc)
{
	// Either convert the image to greyscale, or use the existing greyscale image.

	IplImage *imageGrey;
	IplImage *imageProcessed;

	int i =0;
	if (imageSrc->nChannels == 3)
		{
			imageGrey = cvCreateImage(cvGetSize(imageSrc), IPL_DEPTH_8U, 1 );
			cvCvtColor(imageSrc, imageGrey, CV_BGR2GRAY );
		}
		else {
			imageGrey = cvCloneImage(imageSrc);
		}
		// Resize the image to be a consistent size, even if the aspect ratio changes.

		imageProcessed = cvCreateImage(cvGetSize(imageGrey), IPL_DEPTH_8U, 1);
		// Make the image a fixed size.
		// CV_INTER_CUBIC or CV_INTER_LINEAR is good for enlarging, and
		// CV_INTER_AREA is good for shrinking / decimation, but bad at enlarging.
		cvResize(imageGrey, imageProcessed, CV_INTER_LINEAR);

		//Give the image a standard brightness and contrast.
		cvEqualizeHist(imageProcessed, imageProcessed);

		//.....  Use 'imageProcessed' for Face Recognition ....//
		//SaveImage("./VisageRecadres/ScreenShotGris", imageProcessed, &i);


	/*if (imageGrey)
		cvReleaseImage(&imageGrey);
	/*if (imageProcessed)
	cvReleaseImage(&imageProcessed);*/
	return imageProcessed;
}

int Recognise::Crop(IplImage *imageSrc, CvRect *r, int i)
{
	int prediction;
	Mat matImageSrc = cvarrToMat(imageSrc, false);
	Mat matImageCrop;
	cv::Rect rect(r->x, r->y, r->width, r->height);

	matImageCrop = matImageSrc(rect).clone();
	//SaveImage("./VisageRecadres/ScreenShotGris", matImageCrop, &i);

	prediction = this->ftrecognise(matImageCrop);

	return prediction;
}
int Recognise::ftrecognise(Mat face){
	/* test function for recognising a person */
	string fn_csv = string(PATH_DB);
	vector<Mat> images;
  vector<int> labels;
	Mat face_resized;
	int predicted_label = -1;
  int prediction = UNKNOWN;
  double confidence = 0.0;
  double percent = 0.0;

    try {
        	this->parse_csv(fn_csv, images, labels);
    } catch (cv::Exception& e) {
        cout << "Error opening file \"" << fn_csv << "\". Reason: " << e.msg << endl;
        exit(1);
    }
	try{
		int im_width = images[0].cols;
    int im_height = images[0].rows;
		resize(face, face_resized, Size(im_width, im_height), 1.0, 1.0, INTER_CUBIC);
		//Ptr<FaceRecognizer> model = createFisherFaceRecognizer();
		Ptr<face::FaceRecognizer> model = face::createEigenFaceRecognizer();
		//Ptr<FaceRecognizer> model =createLBPHFaceRecognizer(1, 8, 8, 8, 0.0);
		model->train(images, labels);
		predicted_label = model->predict(face_resized);
		//model->predict(face_resized,predicted_label,confidence);
    model->setThreshold(10000.0);
    model->predict(face_resized, predicted_label, confidence);
    prediction = predicted_label;
		string result_message = format("Predicted class = %d | confidence = %f | percent = %0.1f%%", predicted_label, confidence,(confidence/10000)*100);
    cout << result_message << endl;
    percent = (confidence / 10000)*100;
   	if(((confidence/10000)*100) > 54 &&  ((confidence/10000)*100) < 100)
   		return prediction;
		else
			return UNKNOWN;
	}catch(cv::Exception& e){
		cout << "Opencv Error => " << e.msg << endl;
		return -1 ;
	}
}

void Recognise::parse_csv(const string& filename, vector<Mat>& images, vector<int>& labels){
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
            images.push_back(imread(path, CV_LOAD_IMAGE_GRAYSCALE));
            labels.push_back(atoi(classlabel.c_str()));
        }
    }

}
