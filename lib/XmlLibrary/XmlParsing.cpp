/*
 * Facetracker
 * @authors : Hamza & Godeleine & Quentin
 *
*/
#include <stdlib.h>
#include <iostream>
#include <oft3/utils/XmlParsing.h>

#ifdef linux
	#define strcpy_s(X, Y, Z) strcpy(X, Z)
#endif


using namespace std;


//Constructor
DATA::DATA(const char * path) : image()
{
	XmlFile = new TiXmlDocument(path);
	XmlFile->LoadFile(path);
	if (XmlFile->Error())
		cout << XmlFile->ErrorDesc() << endl;
	hdl = new TiXmlHandle(XmlFile);
	if (hdl)
		Element = hdl->FirstChildElement().FirstChildElement().Element();
	Filepath = (char *)malloc((strlen(path) + 1)*sizeof(char));
	strcpy_s(Filepath, strlen(path) +1, path);
	strcpy_s(url, URL_LENGHT_MAX, Element->Attribute("url"));
	number = atoi(Element->Attribute("number"));
}

DATA::~DATA()
{
	//image is a full member of DATA, will be destructed automaticly
	delete XmlFile;
	delete hdl;
	delete Filepath;
}

void DATA::printDATAInfo()
{
	if (XmlFile->Error())
	{
		cout << "ERROR: " << XmlFile->ErrorDesc() << endl;
		cout << "in col " << XmlFile->ErrorCol() << " and row " << XmlFile->ErrorRow() << endl;
	}
	else
	{
		cout << "Xml path : " << Filepath << endl;
		cout << "Working in folder : " << url << endl;
		cout << "Number of images in folder : " << getNumber() << endl;
	}
	cout << endl;
}

//Element is currently on element data
char DATA::setImageFromXml()
{
	TiXmlElement *temp = Element;
	if (getNumber() == 0) return NO_PICTURE_IN_FOLDER;

	//getting images id. If no attribute, id is considered 0
	if (temp->Attribute("id"))
	{
		image.setId(atoi(temp->Attribute("id")));
		cout << temp->Attribute("id") << endl;
	}
	else
		image.setId(0);

	/*xml structure:
	 * <facetracker>
	 *		<data>
	 *			<image>
	 *				...
	 *			</image>
	 *		</data>
	 * </facetracker>
	 */
	temp = Element->FirstChildElement();

	if (!temp)	//in case of writings errors
	{
		cerr << "le noeud � atteindre n'existe pas" << endl;
		return XML_READING_ERROR;
	}

	// Placing ourselves on the first information (name)
	temp = temp->FirstChildElement();

	if (!strcmp(temp->Value(), "name"))
	{
		if (image.setName(temp->GetText()))
			return XML_READING_ERROR;
	}

	temp = temp->NextSiblingElement();
if (!strcmp(temp->Value(), "camera"))
	{
		if (image.setCamera(temp->GetText()))
			return XML_READING_ERROR;
	}

	temp = temp->NextSiblingElement();
	if (!strcmp(temp->Value(), "date"))
	{
		if (image.setDate(temp->GetText()))
			return XML_READING_ERROR;
	}

	temp = temp->NextSiblingElement();
	if (!strcmp(temp->Value(), "time"))
	{
		if (image.setTime(temp->GetText()))
			return XML_READING_ERROR;
	}

	temp = temp->NextSiblingElement();
	if (!strcmp(temp->Value(), "LastOpened"))
	{
		if (image.setLastOpened(temp->GetText()))
			return XML_READING_ERROR;
	}

	return SUCCESS;
}

char DATA::addImageToXml()
{
	TiXmlElement * NewElement = new TiXmlElement("image");
	TiXmlElement * temp = Element;
	TiXmlText * NewText = new TiXmlText("New");
	int number = getNumber() + 1;

	//placing element in Node <data>
	if (strcmp(getNodeName(), "data"))
		return NOT_DATA_NODE_ERROR;

	if(setNumber(number))
		return XML_WRITING_ERROR;

	//create new image
	//NewElement.SetAttribute("id", "0");
	temp->InsertBeforeChild(Element->FirstChildElement(), *NewElement);

	NewElement->LinkEndChild(NewText);
	temp = temp->FirstChildElement();


	//name
	NewElement->SetValue("name");
	NewText->SetValue(image.getName());
	temp->InsertEndChild(*NewElement);

	//camera
	NewElement->SetValue("camera");
	NewText->SetValue(image.getCamera());
	temp->InsertEndChild(*NewElement);

	//date
	NewElement->SetValue("date");
	NewText->SetValue(image.getDate());
	temp->InsertEndChild(*NewElement);

	//time
	NewElement->SetValue("time");
	NewText->SetValue(image.getTime());
	temp->InsertEndChild(*NewElement);

	//LastOpened
	NewElement->SetValue("LastOpened");
	NewText->SetValue(image.getLastOpened());
	temp->InsertEndChild(*NewElement);

	/*
	NewElement->SetValue("ID");
	NewText->SetValue(image.getID());
	temp->InsertEndChild(*NewElement);
	*/

	XmlFile->SaveFile(Filepath);		//Saving changes

	delete(NewElement);

	return 0;
}

char DATA::deleteImageFromXml()
{
	int number = getNumber() - 1;
	const char *value = Element->Value();

	if (strcmp(value, "data"))
	{
		cout << "Please indicate the folder" << endl;
		return NOT_DATA_NODE_ERROR;
	}
	setNumber(number);
	Element->RemoveChild(Element->FirstChildElement());


	XmlFile->SaveFile(Filepath);

	return 0;
}

int DATA::getNumber() const
{
	return this->number;
}

const char * DATA::getUrl() const
{
	return this->url;
}

const char * DATA::getNodeName() const
{
	return this->Element->Value();
}

char DATA::setNumber(int newNumber)
{
	//if Element isn't a data node
	if (strcmp(Element->Value(), "data"))
	{
		cout << "Please indicate the folder" << endl;
		return NOT_DATA_NODE_ERROR;
	}
	Element->SetAttribute("number", newNumber);
	this->number = newNumber;

	XmlFile->SaveFile(Filepath);

	return 0;
}

char DATA::moveIntoFolder(const char * folder)
{
	int ok = 1;
	//We place ourselves on the first data node
	Element = hdl->FirstChildElement().FirstChildElement().Element();
	ok = strcmp(Element->Attribute("url"), folder);
	//Looking for the right node
	while (ok && Element)
	{
		Element = Element->NextSiblingElement("data");
		if (Element)
			ok = strcmp(Element->Attribute("url"), folder);
	}

	//if the node doesn't exist, we create it at the beginning of the xml file
	if (ok)
	{
		cout << "adding new data" << endl;
		TiXmlElement NewData("data");
		NewData.SetAttribute("url", folder);
		NewData.SetAttribute("number", 0);	//the new folder hasn't any image yet
		number = 0;
		Element = hdl->FirstChildElement().Element();
		Element->InsertBeforeChild(Element->FirstChildElement(), NewData);
		XmlFile->SaveFile(Filepath);
		moveIntoFolder(folder);
	}
	else
		number = atoi(Element->Attribute("number"));

	if(strcpy_s(url, URL_LENGHT_MAX, folder))
		return URL_CHANGING_ERROR;


	return 0;
}
