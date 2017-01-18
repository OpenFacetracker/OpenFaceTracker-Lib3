/*
 * Facetracker
 * @authors : Hamza & Godeleine & Quentin
 *
*/
#include <stdio.h>
#include <stdlib.h>
#ifdef linux
	#include <getopt.h>
#endif
#ifdef _WIN32
	//#include "../lib/Xgetopt/XGetopt.h"
	#include <tchar.h>
#endif
#include <oft3/core.h>
#include <string.h>
#include <oft3/utils/XmlParsing.h>

static int verbose_flag;

using namespace ft;

char	*optarg;
int		optind = 0;

void Parser::parse(int argc, char ** argv){
#ifdef linux
  int c;
  Console *console = new Console;
  Config  *config  = new Config;
  Camera  *camera  = new Camera;
  FtUtils *utils   = new FtUtils;

  char *elem;

  while (1)
    {
      	static struct option long_options[] =
        {
          /* These options set a flag. */
          {"verbose", no_argument,       &verbose_flag, 1},
          {"brief",   no_argument,       &verbose_flag, 0},
          /* These options don’t set a flag.
             We distinguish them by their indices. */
          {"help",     no_argument,       0, 'h'},
          {"append",  required_argument,       0, 'o'},
          {"list",  no_argument,       0, 'l'},
          {"read",  required_argument, 0, 'r'},
          {"create",  required_argument, 0, 'x'},
          {"file",    required_argument, 0, 'f'},
          {0, 0, 0, 0}
        };
      	/* getopt_long stores the option index here. */
      	int option_index = 0;

      	c = getopt_long (argc, argv, "hlcx:r:f:o:",
                       long_options, &option_index);

      	/* Detect the end of the options. */
      	if (c == -1)
        	break;

      	switch (c)
        {
        	case 0:
          		/* If this option set a flag, do nothing else now. */
          		if (long_options[option_index].flag != 0)
            		break;
          		printf ("option %s", long_options[option_index].name);
          		if (optarg)
            		printf (" with arg %s", optarg);
          		printf ("\n");
          		break;

        	case 'h':
          		console->help();
          		break;

          	case 'l':
          		/* list cameras */
          		camera->listCamera();
          		break;

        	case 'o':
          		/* open camera for test */
							DEBUGP ("Opening camera");
        			if(!optarg){
        				std::cout << FT_ERROR << "please give a valid file name" << std::endl;
        			}else{
        				camera->cOpen(optarg);
        			}
          		break;

        	case 'x':
          		/* Read xml file */
              	this->xmltest(optarg);
          		break;
					case 'c':
              /* check env */
                utils->checkEnv();
              break;

        	case 'r':
								elem = config->getElem(optarg);
								console->writeAction("Value = ", WITHOUT);
								std::cout << elem << std::endl;
          		break;

        	case 'f':

          		break;

        	case '?':
          		/* getopt_long already printed an error message. */
          		break;

        	default:
          		abort ();
        }
  }

  /* Instead of reporting ‘--verbose’
  and ‘--brief’ as they are encountered,
  we report the final status resulting from them. */
  if (verbose_flag)
    console->writeAction("verbose flag is set", INLINE);

  if (optind < argc)
  {
    console->writeError("non-option ARGV-elements: ", WITHOUT);
    //printf ("non-option ARGV-elements: ");
    while (optind < argc)
        printf ("%s ", argv[optind++]);
    putchar ('\n');
  }
  delete config;
  delete console;
  delete camera;
  delete utils;
#endif
#ifdef _WIN32
	this->win32parse(argc, argv);
#endif
	return ;
}
void Parser::win32parse(int argc, char ** argv){
	/* using win32getopt */
	int c;
	Console *console = new Console;
	Config  *config  = new Config;
	Camera  *camera  = new Camera;
	FtUtils *utils   = new FtUtils;
	char * elem = NULL;
	while ((c = this->win32getopt(argc, argv, "hlcx:r:f:o:")) != EOF)
	{
		switch (c)
		{
			case 'h':
          		console->help();
          		break;

          	case 'l':
          		/* list cameras */
          		camera->listCamera();
          		break;

        	case 'o':
          		/* open camera for test */
				DEBUGP ("test");
        		if(!optarg){
        			std::cout << FT_ERROR << "please give a valid camera name" << std::endl;
        		}else{
        			camera->cOpen(optarg);
        		}
          		break;

        	case 'x':
          		/* Read xml file */
              	//this->xmltest(optarg);
          		break;
			case 'c':
              /* check env */
                utils->checkEnv();
              break;

        	case 'r':
				elem = config->getElem(optarg);
				console->writeAction("Value = ", WITHOUT);
				std::cout << elem << std::endl;
          		break;

        	case 'f':

          		break;
			case '?':
				/* show help */
				console->help();
				break;
			default:

				break;
		}
	}
	delete config;
	delete console;
	delete camera;
	delete utils;
}
int Parser::win32getopt(int argc, char ** argv, char *optstring){
#ifdef _WIN32
	static char *next = NULL;
	char c;
	char *cp;
	int i;

	if (optind == 0)
		next = NULL;

	optarg = NULL;

	if (next == NULL || *next == _T('\0'))
	{
		if (optind == 0)
			optind++;

		if (optind >= argc || argv[optind][0] != _T('-') || argv[optind][1] == _T('\0'))
		{
			optarg = NULL;
			if (optind < argc)
				optarg = argv[optind];
			return EOF;
		}

		if (strcmp(argv[optind], _T("--")) == 0)
		{
			optind++;
			optarg = NULL;
			if (optind < argc)
				optarg = argv[optind];
			return EOF;
		}

		next = argv[optind];
		next++;		// skip past -
		optind++;
	}

	c = *next++;
	cp = strchr(optstring, c);

	if (cp == NULL || c == _T(':'))
		return ('?');

	cp++;
	if (*cp == _T(':'))
	{
		if (*next != _T('\0'))
		{
			optarg = next;
			next = NULL;
		}
		else if (optind < argc)
		{
			optarg = argv[optind];
			optind++;
		}
		else
		{
			return _T('?');
		}
	}
	/*
	for debug use static_cast<void*>
	for(i = 0; i<strlen(cp);i++){
		printf("adresse de %c is 0x%p\n",cp[i],cp[i]);
	}
	*/
	return c;
#endif

}
#ifdef FT_XML_LIB
void Parser::xmltest(char *path){
  DATA data(path);

  //affiche data tout juste initialisé
  std::cout << "initialisation ..." << std::endl;
  std::cout << data.getNodeName() << std::endl;
  data.printDATAInfo();

  //On se déplace dans la deuxième node (url2)
  std::cout << "Testing moveIntoFolder" << std::endl;
  data.moveIntoFolder("url2");
  std::cout << data.getNodeName() << std::endl;
  data.printDATAInfo();
  data.moveIntoFolder("url3");

  //On récupère la première image du dossier url2 (image2)
  std::cout << "getting image2" << std::endl;
  data.moveIntoFolder("url2");
  data.setImageFromXml();
  data.image.printInfo();

  //On supprime l'image récupérée
  std::cout << "Testing deleteImageFromXml()" << std::endl;
  data.deleteImageFromXml();
  data.deleteImageFromXml();

  system("pause");

  //On se replace dans la node data url1 et on ajout l'image
  data.moveIntoFolder("url1");
  std::cout << "Testing addImageToXml()" << std::endl;
  data.addImageToXml();
}

#else

void Parser::xmltest(char *path){
	std::cout << FT_ERROR << "XML lib is not supported , please use FT_XML_LIB" << std::endl;

}

#endif
