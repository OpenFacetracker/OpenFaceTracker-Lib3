[![GitHub license](https://img.shields.io/badge/content-core-yellow.svg)](https://raw.githubusercontent.com/Facetracker-project/facetracker-core/master/COPYING)
[![GitHub license](https://img.shields.io/badge/codename-TheMachine-red.svg)](https://raw.githubusercontent.com/Facetracker-project/facetracker-core/master/COPYING)
[![GitHub license](https://img.shields.io/badge/license-GPLv2-blue.svg)](https://raw.githubusercontent.com/Facetracker-project/facetracker-core/master/COPYING) [![Code Climate](https://codeclimate.com/repos/56363a6b6956801daf00c1ec/badges/31b2ffeeb02d53158157/gpa.svg)](https://codeclimate.com/repos/56363a6b6956801daf00c1ec/feed) [![Test Coverage](https://codeclimate.com/repos/56363a6b6956801daf00c1ec/badges/31b2ffeeb02d53158157/coverage.svg)](https://codeclimate.com/repos/56363a6b6956801daf00c1ec/coverage) [![GitHub version](https://badge.fury.io/gh/invicnaper%2FMWF.svg)](http://badge.fury.io/gh/invicnaper%2FMWF)
# README #

This README would normally document whatever steps are necessary to get facetracker up and running.

![alt text](https://cdn1.iconfinder.com/data/icons/skype-icons/128/skype_camera.png "FT logo")

### What is this repository for? ###

* Share facetracker code 
* Facetracker is insipred from the American Tv show "Person Of Interest"
* Version 1.2
* This repo contains facetracker-core  . You can check out facetracker-gui via this link . https://github.com/Facetracker-project/facetracker-gui

### Screen ###


![alt text](http://naper.eu/me/images/facetracker.jpg "FT screen")

![alt text](http://nsa38.casimages.com/img/2015/10/31/151031055257844926.png "FT screen")


### How do I get set up? ###

build facetracker using source code

#Linux (Facetracker core)

	$ git clone https://github.com/Facetracker-project/facetracker-core.git
	$ cd facetracker-core/
	
installing dependecies(Debian - ubuntu) : 

	$ sudo apt-get install libopencv-dev
	
making the project : 

	$ make
	**************************************
	*  Facetracker Building    *
	**************************************
	make ftall		: Build facetracker
	make memleaks		: Check memory leaks

to compile all facetracker modules : 

	$ make ftall
	
then execute it using

	$ ./facetracker
	
#Linux ( Adding Options)
You can compile facetracker using different Options . 

* <b>-DFT_USE_COLOR</b>  	= Enable color output
* <b>-DFT_DEBUG_ENABLED</b> 	= Enable Debug mode
* <b>-DFT_ALLOW_EXCEPT</b>	= Enable exceptions
* <b>-DFT_WINCAM_LIST</b> 	= Enable camera listing for Windows
* <b>-DFT_TEST_PERFORMANCE</b> = Enable performance testing
* <b>-DFT_NO_UI</b>		= Disable graphique check
* <b>-DFT_FORM</b>		= Enable output for FORM detection
* <b>-DFT_TEST_RECOGNISE</b>	= Enable recognition
* <b>-DFT_OPTIMISATION</b>	= Enable optimisation

#Windows (facetracker core)

Open the <b>.sln</b> file using Visual Studio

#Available Arguments
-o : allows you to open a media source (camera , picture , video, rtsp link..)

	$ ./facetracker -o CAM0 (open camera id=0)
	$ ./facetracker -o video.avi (open the file video.avi)

### Contributors ###

* Hamza Bourrahim
* Godeleine Champenois
* Quentin Jeannaud

