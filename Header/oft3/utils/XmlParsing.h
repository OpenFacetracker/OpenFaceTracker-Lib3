#ifndef _XMLPARSING_H_
#define _XMLPARSING_H_

#include <stdio.h>
#include "../lib/XmlLibrary/tinyxml.h"
#include <string.h>
#include <oft3/Image.h>

#define PATH_LENGHT_MAX 300
#define URL_LENGHT_MAX 200
#define SUCCESS 0
#define NO_PICTURE_IN_FOLDER 1
#define XML_READING_ERROR 2
#define XML_WRITING_ERROR 3
#define URL_CHANGING_ERROR 4
#define NOT_DATA_NODE_ERROR 5

/*
 * The programme receives the url of a folder with pictures from the camera.
 * It takes each picture, gets its metadata and stores it in an image object.
 * If a face is detected on the picture, that picture is moved in another folder
 * and its informations stored in the xml file.
 *
 * When working with the pictures, a DATA must be created.
 * DATA contains an instance of class Image and access to xml, where infos are stored.
 */

/* TODO:
 * - Some function aren't done yet (TODO)
 * - Add security: if image ID isn't the same as the data ID, ask for confirmation
 * before adding. All images in a data have the same id (doesn't make make sense otherway),
 * thought many data may have the url (meaning that the images may be in the same folder)
 */


class DATA
{
public:
	//current image
	Image image;

	//Create a DATA with a file, and init the parsor in the first folder
	DATA(const char *path);		//path = xml file
	~DATA();

	int getNumber() const;	//return the number of pictures in the folder
	const char * getUrl() const;		//return url of file with pictures
	//for debug
	const char * getNodeName() const;

	/*
	 * Place Element in the good data node in xml file. If the node doesn't exist,
	 * it creates it.
	 * By defaut, DATA works on the first node of the XmlFile
	 */
	char moveIntoFolder(const char * folder);

	//get informations of the first image in xml file and put it in image
	char setImageFromXml();

	//add the image to the Xml file at the begining of the data
	char addImageToXml();

	//delete the first image from xml file
	char deleteImageFromXml();

	//cleans the xml file from ALL the empty folders
	char removeEmptyFolder();						//TODO
	//remove the folder from XmlFile (wether empty or not)
	char removeFolder(char * url);					//TODO
	//Find Image in the whole facetracker data from name
	char findImageInFacetracker(char * ImageName);	//TODO
	//Find image in folder
	char findImageInFolder(char * ImageName);		//TODO
	//Find all images with id=ID in facetracker
	char findImageID(int ID);						//TODO


	// prints errors, the url, the number of images in the folder via getNumber()
	void printDATAInfo();

private:
	int number;
	char url[URL_LENGHT_MAX];		//adress of the folder with the pictures
	char * Filepath;
	TiXmlElement *Element;	//parsor
	TiXmlDocument * XmlFile;
	TiXmlHandle * hdl;

	/* setNumber()
	 * Changes int number with the new number of picture and the information in the xml file.
	 * This methode is private as it should'nt be used unless we are working on a picture.
	 */
	char setNumber(int newNumber);

};

#endif
