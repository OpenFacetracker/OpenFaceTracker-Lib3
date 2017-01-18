/*
 * Facetracker
 * @authors : Hamza & Godeleine & Quentin
 *
*/


#include <oft3/secure.h>


char * Security::rawInput(char* inp){

#ifdef BOUNDS_PROTECTION
	if(strlen(inp) > MAX_SIZE){
		return NULL;
	}
#endif

	return 0;
}
