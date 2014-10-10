#include "Appearance.h"


Appearance::Appearance(string appid,float shininess,float * amb,float * dif, float * spe): CGFappearance(amb,dif,spe,shininess){
	this->id = appid;
	this->s=1;
	this->t=1;
}

Appearance::Appearance(): CGFappearance(){

}

Appearance::~Appearance(){

}