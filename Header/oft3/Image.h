/*
 * Facetracker
 * @authors : Team OpenFaceTracker
 *
*/
#ifndef _IMAGE_H_
#define _IMAGE_H_

#define LENGTH_MAX_NAME_PICTURE 100
#define DATE_LENGHT_PICTURE 11

class Image
{
public:
	Image();
	~Image();

	char* getName() const;
	char* getCamera() const;
	char* getDate() const;
	char* getTime() const;
	char* getLastOpened() const;
	int getID() const;

	int setName(const char* str);
	int setCamera(const char* str);
	int setDate(const char* str);
	int setTime(const char* str);
	int setLastOpened(const char* str);
	int setId(int id);

	void printInfo();


private:
	char * name;
	char * camera;
	char * date;
	char * time;
	char * LastOpened;
	char Identity;	//Needed when identifying faces. If not identified, equals 0

};


#endif
