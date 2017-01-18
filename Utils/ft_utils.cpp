/*
 * Facetracker
 * @authors : Hamza & Godeleine & Quentin
 *
*/

#include <oft3/core.h>

using namespace std;
using namespace ft;

void FtUtils::cmdParser(char * cmd){

}
int FtUtils::checkEnv(){
	cout << FT_ACTION << "staring check .." << endl;
#ifdef linux
	cout << FT_DEBUG << "ft runing under linux" << endl;
#endif
	cout << FT_ACTION << "checking graphic card" << endl;
	cout << FT_ACTION << "checking all files " << endl;

#ifdef linux
	sleep(3);
#endif

	return 1;
}

const char * FtUtils::version(){
		/* show oftlib version */
		return VERSION;
}
