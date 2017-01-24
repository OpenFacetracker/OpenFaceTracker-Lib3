# Readme #

## How do I get set up? ##

Build Openfacetracker using source code, to understand the sructure of the OFT project please read the WIKI .

## Dependecies(Debian - ubuntu) ##

	$ sudo apt-get install libopencv-dev

Please Read the WIKI, so as to get the right verson of OpenCV and QT

## Linux ##

	$ git clone https://github.com/OpenFacetracker/OpenFaceTracker-Lib3.git
	$ cd OpenFaceTracker-Lib3


Making the project :

	$ make
	*  OpenFaceTracker Building    *
	make compil 		: Compil facetracker source code
	make lib        	: Build facetracker as a library
	make binary     	: Build facetracker as a binary file
	make memleaks		: Check memory leaks


to compile all oft modules :

	$ make compil

to generate the binary file :

	$ make binary

if you want to use OFT as a library , use :

	$ make lib

then execute it using

	$ ./openft

## Linux ( Adding Options) ##
You can compile OpenFaceTracker using different Options .

* <b>-DFT_USE_COLOR</b>  	= Enable color output
* <b>-DFT_DEBUG_ENABLED</b> 	= Enable Debug mode
* <b>-DFT_ALLOW_EXCEPT</b>	= Enable exceptions
* <b>-DFT_WINCAM_LIST</b> 	= Enable camera listing for Windows
* <b>-DFT_TEST_PERFORMANCE</b> = Enable performance testing
* <b>-DFT_NO_UI</b>		= Disable graphique check
* <b>-DFT_FORM</b>		= Enable output for FORM detection
* <b>-DFT_TEST_RECOGNISE</b>	= Enable recognition
* <b>-DFT_OPTIMISATION</b>	= Enable optimisation

## Windows (OpenFaceTrackerLib3) ##

No Visual Project file for this version

## Available Arguments  ##
-o : allows you to open a media source (camera , picture , video, rtsp link..)

	$ ./openft -o CAM0 (open camera id=0)
	$ ./openft -o video.avi (open the file video.avi)

## Contributors ##

* Hamza Bourrahim
* Godeleine Champenois
* Worphy Bimboutsa
* Ralph Obame
