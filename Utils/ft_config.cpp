/*
 * Facetracker
 * @authors : Hamza & Godeleine & Quentin
 *
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fstream>
#include <string>
#include <iostream>
#include <oft3/core.h>
#include <cstring>
#include <vector>

#define SYNTAXE_ERROR -1

using namespace ft;
using namespace std;

void Config::parseConfig(char line[100], const char * elem, char *result){
  int i, n;
	char token[2] = "=";
	char cp[100];
	char* tk[2] = {};
	conf cf;
	cf.val = NULL;
	memset(cp, '\0', sizeof(cp));
	strcpy(cp, line);
 	if(*line == '#'){
 		/* comments */
 		return ;
 	}
 	if(strstr(line, "=")){
 		/* contain = */
 		tk[0] = strtok(cp, token);
 		if (tk[0])
    	{
      		for (n = 1; n < 2; n++)
      		{
        		tk[n] = strtok(0, token);
        		if (!tk[n]) break;
      		}
    	}
    	for (int i = 0; i < n; i++){
      		if( strstr(tk[i],elem) ){
      			/* TODO: copy tk to result */
      			strcpy(result, tk[1]);
      		}
    	}
 	}else{
 		/* syntaxe error */
 	}
}
char * Config::getElem(const char * elem){
 	Console *console = new Console;
 	char s[100];
 	int stat;
 	//char *result = (char *)malloc(sizeof(char));
  char *result = new char;
 	ifstream conf;
 	conf.open(CONFIG);
 	if(!conf.good()){
 		console->writeError("Can't found the ft config file", INLINE);
 	}else{
 		while(!conf.eof()){
 			conf.getline(s, 100);
 			this->parseConfig(s, elem, result);
 		}
 		if(result != NULL){
 				return this->convert(result);
 		}
 	}

  delete result;
	delete console;

 	/* we don't have to close the File since we are using C++ :D*/
}
char * Config::convert(char * result){
	/* del the first char from result , which  is ' '  */
	//char * finale = (char *)malloc(sizeof(char));
  char * finale = new char;
	string tmp(result);
	tmp.erase(0,1);
	strcpy(finale, tmp.c_str());

	return finale;
  delete finale;
}
