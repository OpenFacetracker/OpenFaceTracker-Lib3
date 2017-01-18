/*
 * Facetracker
 * @authors : Hamza & Godeleine & Quentin
 *
*/
#include <stdlib.h>
#include <iostream>
#include <string.h>
#include <oft3/Image.h>

/* strcpy_s is not available on linux so we should define it as strcpy */
#ifdef linux
	#define strcpy_s(X, Y, Z) strcpy(X, Z)
#endif

using namespace std;

Image::Image()
{
	name = (char*)calloc(LENGTH_MAX_NAME_PICTURE, sizeof(char));
	camera = (char*)calloc(LENGTH_MAX_NAME_PICTURE, sizeof(char));
	date = (char*)calloc(DATE_LENGHT_PICTURE, sizeof(char));
	time = (char*)calloc(DATE_LENGHT_PICTURE, sizeof(char));
	LastOpened = (char*)calloc(DATE_LENGHT_PICTURE, sizeof(char));
	Identity = 0;
}


Image::~Image()
{
	free(name);
	free(camera);
	free(date);
	free(time);
	free(LastOpened);
}

char* Image::getName() const
{
	return this->name;
}

char* Image::getCamera() const
{
	return this->camera;
}

char* Image::getDate() const
{
	return this->date;
}

char* Image::getTime() const
{
	return this->time;
}

char* Image::getLastOpened() const
{
	return this->LastOpened;
}

int Image::getID() const
{
	return this->Identity;
}

int Image::setName(const char* str)
{
	if (strlen(str) > LENGTH_MAX_NAME_PICTURE)
		return -1;
	strcpy_s(this->name, LENGTH_MAX_NAME_PICTURE, str);
	return 0;
}

int Image::setCamera(const char* str)
{
	if (strlen(str) > LENGTH_MAX_NAME_PICTURE)
		return -1;
	strcpy_s(this->camera, LENGTH_MAX_NAME_PICTURE, str);
	return 0;
}

int Image::setDate(const char* str)
{
	if (strlen(str) > DATE_LENGHT_PICTURE)
		return -1;
	strcpy_s(this->date, DATE_LENGHT_PICTURE, str);
	return 0;
}

int Image::setTime(const char* str)
{
	if (strlen(str) > DATE_LENGHT_PICTURE)
		return -1;
	strcpy_s(this->time, DATE_LENGHT_PICTURE, str);
	return 0;
}
int Image::setLastOpened(const char* str)
{
	if (strlen(str) > DATE_LENGHT_PICTURE)
		return -1;
	strcpy_s(this->LastOpened, DATE_LENGHT_PICTURE, str);
	return 0;
}

int Image::setId(int id)
{
	this->Identity = id;
	return 0;
}

void Image::printInfo()
{
	cout << "Name : " << getName() << endl;
	cout << "Camera: " << getCamera() << endl;
	cout << "Date : " << getDate() << " at " << getTime() << endl;
	cout << "Last Opened : " << getLastOpened() << endl;
	cout << "ID : " << getID() << endl;
}
