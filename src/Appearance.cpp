#include "Appearance.h"


Appearance::Appearance(void)
{
}


Appearance::~Appearance(void)
{
}

Appearance::Appearance(string id,float shininess, float ambient[4], float diffuse[4], float specular[4]){

	this->id = id;
	this->shininess = shininess;
	this->ambient[0] = ambient[0];
	this->ambient[1] = ambient[1];
	this->ambient[2] = ambient[2];
	this->ambient[3] = ambient[3];
	this->diffuse[0] = diffuse[0];
	this->diffuse[1] = diffuse[1];
	this->diffuse[2] = diffuse[2];
	this->diffuse[3] = diffuse[3];
	this->specular[0] = specular[0];
	this->specular[1] = specular[1];
	this->specular[2] = specular[2];
	this->specular[3] = specular[3];

}