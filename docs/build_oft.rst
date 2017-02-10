.. role:: bash(code)
   :language: bash
Dependecies
===============
OpenFaceTrackerLib uses Opencv 3.2. This latter has introduced many new algorithms and features comparing to version 2.4. Some modules have been rewritten, some have been reorganized. Although most of the algorithms from 2.4 are still present, the interfaces can differ. You can check out the changelog via this link

* http://opencv.org/opencv-3-2.html


Building Opencv 3.2
-----------------

To get the best environment for OpenFaceTracker3, there are some instructions that you should follow. OpenCV3 must be build with some extra options, so please follow this tutorial .


Downloading Opencv3.2 for Linux
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~


First download Opencv3.2

:bash:`wget https://github.com/opencv/opencv/archive/3.2.0.zip`

:bash:`unzip 3.2.0.zip`

Create a release folder

:bash:`cd opencv-3.2.0/`

:bash:`mkdir release`

:bash:`cd release`


Opencv-Contrib
~~~~~~~~~~~~~~~~~~~~~~


OpenFaceTracker3 is using <b>opencv-contrib</b> it is an experimental and non-free algorithms. It does not receive so much attention from the support team comparing to main repository, but the community makes an effort to keep it in a good shape.

To download Opencv-contrib

:bash:`git clone https://github.com/opencv/opencv_contrib.git`

Building With extra options
~~~~~~~~~~~~~~~~~~~~~~


First, check if you got cmake and qmake installed .

:bash:`cmake`

install it using apt-get(debian-ubuntu)

:bash:`sudo apt-get install cmake`

:bash:`sudo apt-get install qt5-qmake`


we will build opencv with some extra function

:bash:`cmake -D CMAKE_BUILD_TYPE=RELEASE -D CMAKE_INSTALL_PREFIX=/usr/local -D WITH_TBB=ON -D BUILD_NEW_PYTHON_SUPPORT=ON -D WITH_V4L=ON -D INSTALL_C_EXAMPLES=ON -D INSTALL_PYTHON_EXAMPLES=ON -D BUILD_EXAMPLES=ON -D WITH_QT=ON -D WITH_GTK=ON -D WITH_OPENGL=ON -DOPENCV_EXTRA_MODULES_PATH=<path-to-opencv_contrib>/modules ..`
