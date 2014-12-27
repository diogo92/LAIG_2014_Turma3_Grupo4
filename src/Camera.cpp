#include "Camera.h"

Camera::Camera(string id,string direction,float near,float far,float left,float right,float top, float bottom){//ORTHO
	this->id=id;
	this->direction=direction;
	this->near=near;
	this->far=far;
	this->left=left;
	this->right=right;
	this->top=top;
	this->bottom=bottom;
	initial=false;
	isActive=false;
	type=0;
}

Camera::Camera(string id,float near,float far,float angle,float pos[3],float target[3]){//PERSPECTIVE
	this->id=id;
	this->near=near;
	this->far=far;
	this->angle=angle;
	this->setX(pos[0]);
	this->setY(pos[1]);
	this->setZ(pos[2]);
	for(int i=0;i<3;i++){
		this->target[i]=target[i];
	}
	initial=false;
	isActive=false;
	type=1;
}

void Camera::applyView(){
	if(type==0){
		if(direction=="x")
			gluLookAt(1,0,0,0,0,0,0,1,0);
		else if(direction=="y")
			gluLookAt(0,1,0,0,0,0,0,0,-1);
		else
			gluLookAt(0,0,1,0,0,0,0,1,0);
	}
	else{
		gluLookAt(position[0],position[1],position[2],target[0],target[1],target[2],0,1,0);
	}
}

void Camera::updateProjectionMatrix(int width, int height) {
	if(type==0){
		float aspect = (float) width / (float) height;
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		glOrtho(left, right, bottom, top, near, far);
	}
	else{
		float aspect = (float) width / (float) height;
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		gluPerspective(angle, aspect, near, far);
	}
}