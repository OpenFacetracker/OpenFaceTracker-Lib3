/*
 * Facetracker
 * @authors : Hamza & Godeleine & Quentin
 *
*/

#include <oft3/core.h>

#ifdef _WIN32
	#define _CRTDBG_MAP_ALLOC
	#include <crtdbg.h>
#endif

using namespace ft;
using namespace std;
#ifndef FT_LIB
int main(int argc, char ** argv){

	int i;
	Console *console = new Console;
	Parser 	*parser  = new Parser;
	Config 	*config  = new Config;
	Log		*log	 = new Log("log.txt");
	char * result = NULL;

	console->header();
	console->init_color(); /* init color for getopt output */
	/* check arg number */
	if(argc < 2){
		console->writeError("facetracker need arguments, use -h for help", INLINE);
		return 0;
	}
	/* parse argv */
	parser->parse(argc, argv);

	/* delete objects */
	delete console;
	delete parser;
	delete config;
	delete log;

#ifdef _WIN32
	system("pause");
	_CrtDumpMemoryLeaks();
#endif
 	return 0;

}
#endif
