#
# Facetracker
# @authors : Hamza & Godeleine & Quentin
#
#  Makefile for the XML library


all: $(obj)
	@echo 'using g++ ..'
	@echo 'testing the xml library ..'
	#g++ -c Source.cpp -o src.o  just for testing , contains a main function
	g++ -c Image.cpp -o img.o -I ../../Header
	g++ -c XmlParsing.cpp -o xmlparse.o -I ../../Header
	g++ -c tinystr.cpp -o ts.o
	g++ -c tinyxml.cpp -o tx.o
	g++ -c tinyxmlerror.cpp -o txe.o
	g++ -c tinyxmlparser.cpp -o tp.o
	@echo 'done'
