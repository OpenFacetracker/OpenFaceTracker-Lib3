/*
 * Facetracker
 * @authors : Hamza & Godeleine & Quentin
 *
*/
/*
	TODO :
		-Parser with getoptlong
*/
#include <oft3/core.h>
using namespace std;
void ft::Console::writeError(const char * msg, int option){
	cout << "[" ;
#ifdef _WIN32
	this->color(12, 0);
#elif linux
	this->color(31, 0);
#endif
	cout << "Error";
	this->init_color();
	switch(option){
		case INLINE:
			cout << "] : " <<  msg << endl;
			break;
		case WITHOUT:
			cout << "] : " <<  msg;
			break;
		default:
			cout << "] : " <<  msg << endl;
			break;
	}
	return ;
}
void ft::Console::writeDone(const char * msg, int option){
	cout << "[" ;
#ifdef _WIN32
	this->color(10, 0);
#elif linux
	this->color(32, 0);
#endif
	cout << "Ok";
	this->init_color();
	switch(option){
		case INLINE:
			cout << "] : " <<  msg << endl;
			break;
		case WITHOUT:
			cout << "] : " <<  msg;
			break;
		default:
			cout << "] : " <<  msg << endl;
			break;
	}
	return ;
}
void ft::Console::writeAction(const char * msg, int option){
	cout << "[" ;
#ifdef _WIN32
	this->color(14, 0);
#elif linux
	this->color(36, 0);
#endif
	cout << "Action";
	this->init_color();
	switch(option){
		case INLINE:
			cout << "] : " <<  msg << endl;
			break;
		case WITHOUT:
			cout << "] : " <<  msg;
			break;
		default:
			cout << "] : " <<  msg << endl;
			break;
	}
	return ;
}
void ft::Console::color(int font_color, int back_color){
#ifdef _WIN32
	HANDLE H=GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(H,back_color*16+font_color);
#elif linux
    switch(font_color){
		case 34:
			printf("\033[34m");
			break;
		case 31:
			printf("\033[31m");
			break;
		case 32:
			printf("\033[32m");
			break;
		case 33:
			printf("\033[33m");
			break;
		case 36:
			printf("\033[36m");
			break;
		default:
			printf("\033[0m");
			break;
	}
#endif
}
void ft::Console::init_color(){
#ifdef _WIN32
	this->color(15, 0);
#elif linux
	this->color(37, 0);
#endif
	return;
}
/* Fonction pour tester la fonction "Function_Result2" */
void ft::Console::testFunction_result()
{
	int x = rand() % 2;
	const char *NomFonction = "TestFunction_result";
	function_result(x, NomFonction);
	return;
}
/*
Entrée : Error, le nom de la fonction
Sortie : rien
S'il y a eu une erreur dans la fonction "TestFunction_Result" on appelle la fonction
"WriteError" pour afficher l'erreur */
void ft::Console::function_result(int Error, const char *NomFonction)
{
	if (Error){
		this->writeError(NomFonction, INLINE);
	}
	else{
		this->writeDone(NomFonction, INLINE);
	}
}
void ft::Console::header(){
#ifdef _WIN32
	this->color(9, 0);
#elif linux
	this->color(34, 0);
#endif
	cout << "======================" << endl;
	cout <<	   "';,."         << endl;
	cout <<	   " .d00O0KO0Okxl,."   << endl;
	cout <<	   ".0kO0kc'....':okl."  << endl;
	cout <<	   ".0O0: 'c,......;xd." << endl;
	cout <<	   " o0l .'..','',..:dc" << endl;
	cout <<	   " lOl. ...,odxx''cdc" << endl;
	cout <<	   " .xk:....,ldd:,:dod."<< endl;
	cout <<	   "   :xd:,''',:coollo "<< endl;
	cout <<	   "     .;cooooddool; " << endl;
	cout <<	   "             .. ;"<< endl;
	cout << "@ OpenFaceTracker " << endl;
	cout << "@ Version : "<< VERSION << endl;
	cout << "======================" << endl;
	this->init_color();
}
void ft::Console::help(){
	cout <<
		 "\nusage: ./facetracker [-option]\n\n"
            "  -h      help\n"
            "  -s      stop\n"
            "  -l      turn left\n"
            "  -r      turn right\n"
            "  -u      turn up\n"
            "  -d      turn down\n"
            "  -f      fire\n"
            "  -t      specify duration in milli seconds\n"
            "  -h      display this help\n\n"
            "notes:\n"
            "* it is possible to add verbose for every option\n"
            "  '--OPTION' can also be used \n"
            "";
}
/*
colors Linux :
noir : 30
rouge : 31
vert : 32
jaune : 33
bleu : 34
magneta : 35
cyan : 36
blanc : 37
Colors windows:
0 : Noir
1 : Bleu foncé
2 : Vert foncé
3 : Turquoise
4 : Rouge foncé
5 : Violet
6 : Vert caca d'oie
7 : Gris clair
8 : Gris foncé
9 : Bleu fluo
10 : Vert fluo
11 : Turquoise
12 : Rouge fluo
13 : Violet 2
14 : Jaune
15 : Blanc
*/
