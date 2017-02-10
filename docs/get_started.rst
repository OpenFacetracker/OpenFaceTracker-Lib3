.. role:: bash(code)
   :language: bash
Getting Started
===============

This document will show you how to get up and running with OpenFaceTracker. You will have you own facial recognition
system in 10 minutes.


Quick Installation
--------------------

OpenFaceTracker needs OpenCV3.2 and QT4 installed on your machine, you've got two options :

- If you love compiling libraries by hand, please follow  :ref:`build_oft`

- Installing Opencv and QT using your favorite packaging tool .

Downloading OpenFaceTracker
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Our github page is available at .. _OftGithub: https://github.com/OpenFacetracker , make sure you're cloning the right repo. OpenFaceTracker-Lib3 is the one under development.

:bash:`git clone https://github.com/OpenFacetracker/OpenFaceTracker-Lib3.git`

:bash:`cd OpenFaceTracker-Lib3`


At this step, you've got two options :

- Compiling OFT as a library

- Compiling OFT as a standalone binary file


Compiling OFT as a library
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

:bash:`make lib`


Compiling OFT as a standalone binary file
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

:bash:`make compil`

:bash:`make binary`


Launching process
------------------
After compiling Oft, you can execute it using

:bash:`./openft <options>`


Execution Options List
~~~~~~~~~~~~~
There are lot of options available, here is a list of the main options :

-o <file>         Open the file and execute the detection and recognition module
-h                Show help and exit
-l                Show the list of all available cameras
-x                Testing the XML DB
-r                Reading from the OFT config
-c                Check the environment
