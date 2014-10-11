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
	for(int i=0;i<3;i++){
		this->pos[i]=pos[i];
		this->target[i]=target[i];
	}
	initial=false;
	isActive=false;
	type=1;
}