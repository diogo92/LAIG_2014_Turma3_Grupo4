#ifndef CAMERA_H
#define CAMERA_H

#include <string>

using namespace std;


class Camera{
public:
	Camera(){};
	Camera(string id,string direction,float near,float far,float left,float right,float top, float bottom);//ORTHO
	Camera(string id,float near,float far,float angle,float pos[3],float target[3]);//PERSPECTIVE
	bool initial;
	bool isActive;
	string id,direction;
	float near,far,left,right,top,bottom,angle,pos[3],target[3];
	int type;//0 - ORTHO; 1 - PERSPECTIVE
};

#endif