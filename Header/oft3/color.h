/*
 * Facetracker
 * @authors : Hamza & Godeleine & Quentin
 *
*/

/*
* Colors for undefined variables
* You can use this if you want to print output with a variable
* Example printf(ERROR "error %d\n",nb);
* Or either cout << ERROR << error << nb << endl;
*/
#ifndef HCOLOR
#define HCOLOR

#include <oft3/core.h>

#ifdef linux
	#define FT_ERROR 	"[\033[31m!\033[0m] ./"
	#define FT_ACTION 	"[\033[36m+\033[0m] ./"
	#define FT_OK 		"[\033[32mo\033[0m] ./"
	#define FT_DEBUG	"[\033[33m#\033[0m] ./"
#endif
#ifdef _WIN32
	#define FT_ERROR 	"[!] ./"
	#define FT_ACTION 	"[+] ./"
	#define FT_OK 		"[o] ./"
	#define FT_DEBUG	"[#] ./"
#endif

#endif
