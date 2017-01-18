/*
 * Facetracker
 * @authors : Hamza & Godeleine & Quentin
 *
*/

#include <oft3/core.h>
#include <fstream>
using namespace std;
using namespace ft;

Log::Log(const char * name){
	/* create new log list */
	log = NULL;
	//this->addLog("============== LOG ==============");
	logname = name;
}

Log::~Log(){
	/* destructor */
}

void Log::addLog(char * text){
	llog * tmp = NULL;
	Console * console = new Console;
	tmp = (llog *)malloc(sizeof(llog));
	tmp->pNext = NULL;
	tmp->string = NULL;
	if(!tmp){
		console->writeError("Can't allocate memory",INLINE);
	}else{
		tmp->string = text;
		tmp->pNext = log;
	}
	log = tmp;
	delete console;
}

void Log::writeLog(){
	/* write log in the file logname */
	Console * console = new Console;
	ofstream logfile;
	if(!log){
		console->writeError("Nothing to write to the log file",INLINE);
	}
	logfile.open(logname);
	if(!logfile.good()){
		console->writeError("can't found the log file",INLINE);
		return ;
	}
	while(log != NULL){
		/* parse all the list */
		logfile << log->string << endl;
		log = log->pNext;
	}
	/* free the list */
	this->freeLog();
	delete console;
	return ;
}

void Log::freeLog(){
	if(!log)
		return ;
	while(log != NULL){
		free(log);
		log = log->pNext;
	}
	return ;
}
