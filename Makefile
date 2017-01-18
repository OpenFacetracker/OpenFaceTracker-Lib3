#
# Facetracker
# @authors : Hamza & Godeleine & Quentin
# installing open cv , using libopencv-dev
#
OBJ=help
BINDIR=obj
WININSTDIR=install
ARCHDIR=targz

all: $(OBJ)

help:
	@echo  '**************************************'
	@echo  '*  Facetracker Building    *'
	@echo  '**************************************'
	@echo
	@echo  'make compil 		: Compil facetracker source code'
	@echo  'make lib        : Build facetracker as a library'
	@echo  'make binary     : Build facetracker as a binary file'
	@echo  'make memleaks		: Check memory leaks'

compil: compilmsg
compilmsg:
	#Xml/libxml/libxmlforft.a
	@echo ===================[Compiling FT]===================
	@echo 'using g++ ..'
	#g++ -DFT_USE_COLOR=TRUE Utils/ft_main.cpp Console/ft_console.cpp Utils/ft_parser.cpp Utils/ft_config.cpp Utils/ft_log.cpp -o facetracker
	g++ -c  -DFT_USE_COLOR=TRUE -DFT_DEBUG_ENABLED=1 -I ./Header Utils/ft_main.cpp -o obj/ftmain.o
	g++ -c  -DFT_USE_COLOR=TRUE -DFT_DEBUG_ENABLED=1 -I ./Header Console/ft_console.cpp -o obj/ftcons.o
	g++ -c  -DFT_USE_COLOR=TRUE -DFT_DEBUG_ENABLED=1 -I ./Header Utils/ft_parser.cpp -o obj/ftpars.o
	g++ -c  -DFT_USE_COLOR=TRUE -DFT_DEBUG_ENABLED=1 -I ./Header Utils/ft_utils.cpp -o obj/ftutils.o
	g++ -c  -DFT_USE_COLOR=TRUE -DFT_DEBUG_ENABLED=1 -I ./Header Utils/ft_config.cpp -o obj/ftconfig.o
	g++ -c  -DFT_USE_COLOR=TRUE -DFT_DEBUG_ENABLED=1 -I ./Header Utils/ft_log.cpp -o obj/ftlog.o
	g++ -c 	-DFT_USE_COLOR=TRUE -DFT_DEBUG_ENABLED=1 -I ./Header -DFT_FORM=1 Camera/ft_detect.cpp `pkg-config --cflags --libs opencv` -o obj/ftdetect.o
	g++ -c 	-DFT_USE_COLOR=TRUE -DFT_DEBUG_ENABLED=1 -I ./Header -DFT_FORM=1 Camera/ft_person.cpp `pkg-config --cflags --libs opencv` -o obj/ftperson.o
	g++ -c 	-DFT_USE_COLOR=TRUE -DFT_DEBUG_ENABLED=1 -I ./Header -DFT_FORM=1  Camera/ft_draw.cpp `pkg-config --cflags --libs opencv` -o obj/ftdraw.o
	@echo "compiling ft recognition module .."
	make -C Camera/recognition/
	#g++ -c 	-DFT_USE_COLOR=TRUE -DFT_DEBUG_ENABLED=1 Camera/core/drawing.cpp `pkg-config --cflags --libs opencv` -o obj/ftcoredraw.o
	#using make to compile the xmllib
	#cd lib/XmlLibrary
	make -C lib/XmlLibrary/
	#cd ../../
	#linking all .o files
	#g++ obj/*.o lib/XmlLibrary/*.o `pkg-config --cflags --libs opencv` -o facetracker
	@echo 'done'
	@echo ===================[Finished]===================

lib: libmsg
libmsg:
	@echo ===================[Building library]===================
	@echo 'using g++ ..'
	#g++ -DFT_USE_COLOR=TRUE Utils/ft_main.cpp Console/ft_console.cpp Utils/ft_parser.cpp Utils/ft_config.cpp Utils/ft_log.cpp -o facetracker
	g++ -c  -DFT_USE_COLOR=TRUE -DFT_DEBUG_ENABLED=1 -I ./Header -DFT_LIB Utils/ft_main.cpp -o obj/ftmain.o
	g++ -c  -DFT_USE_COLOR=TRUE -DFT_DEBUG_ENABLED=1 -I ./Header -DFT_LIB Console/ft_console.cpp -o obj/ftcons.o
	g++ -c  -DFT_USE_COLOR=TRUE -DFT_DEBUG_ENABLED=1 -I ./Header -DFT_LIB Utils/ft_parser.cpp -o obj/ftpars.o
	g++ -c -fPIC  -DFT_USE_COLOR=TRUE -DFT_DEBUG_ENABLED=1 -I ./Header -DFT_LIB Utils/ft_utils.cpp -o obj/ftutils.o
	g++ -c  -DFT_USE_COLOR=TRUE -DFT_DEBUG_ENABLED=1 -I ./Header -DFT_LIB Utils/ft_config.cpp -o obj/ftconfig.o
	g++ -c  -DFT_USE_COLOR=TRUE -DFT_DEBUG_ENABLED=1 -I ./Header -DFT_LIB Utils/ft_log.cpp -o obj/ftlog.o
	g++ -c 	-DFT_USE_COLOR=TRUE -DFT_DEBUG_ENABLED=1 -I ./Header -DFT_LIB -DFT_FORM=1 Camera/ft_detect.cpp `pkg-config --cflags --libs opencv` -o obj/ftdetect.o
	g++ -c 	-DFT_USE_COLOR=TRUE -DFT_DEBUG_ENABLED=1 -I ./Header -DFT_LIB -DFT_FORM=1 Camera/ft_person.cpp `pkg-config --cflags --libs opencv` -o obj/ftperson.o
	g++ -c 	-DFT_USE_COLOR=TRUE -DFT_DEBUG_ENABLED=1 -I ./Header -DFT_LIB -DFT_FORM=1 -DFT_TEST_RECOGNISE=1 Camera/ft_draw.cpp `pkg-config --cflags --libs opencv` -o obj/ftdraw.o
	@echo "compiling ft recognition module .."
	make -C Camera/recognition/
	#g++ -c 	-DFT_USE_COLOR=TRUE -DFT_DEBUG_ENABLED=1 Camera/core/drawing.cpp `pkg-config --cflags --libs opencv` -o obj/ftcoredraw.o
	#using make to compile the xmllib
	#cd lib/XmlLibrary
	make -C lib/XmlLibrary/
	ar -cvq openfacetracker_lin_lib-2.4.1.a obj/*.o
	@echo ===================[Finished]===================
binary: binarymsg
binarymsg:
	@echo ===================[Building binary]===================
	g++ obj/*.o lib/XmlLibrary/*.o `pkg-config --cflags --libs opencv` -o openft
	@echo ===================[Finished]===================
memleaks: memleaksmsg
memleaksmsg:
	@echo usiing Valgrind ..
	valgrind --leak-check=yes ./facetracker -r PATH_TMP

mc:	mcmsg
mcmsg:
	#compile a module
	g++ -c 	-DFT_USE_COLOR=TRUE -DFT_DEBUG_ENABLED=1 -DFT_FORM=1 Camera/ft_detect.cpp `pkg-config --cflags --libs opencv` -o obj/ftdetect.o
	g++ -c 	-DFT_USE_COLOR=TRUE -DFT_DEBUG_ENABLED=1 -DFT_FORM=1 Camera/ft_draw.cpp `pkg-config --cflags --libs opencv` -o obj/ftdraw.o
	g++ -c  -DFT_USE_COLOR=TRUE -DFT_DEBUG_ENABLED=1 Utils/ft_utils.cpp -o obj/ftutils.o
	g++ obj/*.o lib/XmlLibrary/*.o `pkg-config --cflags --libs opencv` -o openft
