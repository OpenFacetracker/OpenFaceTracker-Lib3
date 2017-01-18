/*
 * Facetracker
 * @authors : Hamza & Godeleine & Quentin
 *
*/
#include <opencv/cv.h>
#include <opencv/highgui.h>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/face.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/objdetect.hpp>
#include <oft3/ft_person.h>

Person::Person(){

}

Person::~Person(){

}

void Person::setRect(CvRect * p_r){
  this->m_r = p_r;
}

void Person::setName(string p_name){
  this->m_name = p_name;
}

void Person::setId(int p_id){
  this->m_id = p_id;
}

CvRect * Person::getRect(){

  return this->m_r;
}

string Person::getName(){

  return this->m_name;
}

int Person::getId(){

  return this->m_id;
}
