#ifndef DEMOSCENE_H
#define DEMOSCENE_H

#include "CGFscene.h"
#include "CGFshader.h"
#include "CGFapplication.h"
#include <map>
#include <string>
#include <typeinfo>

class DemoScene : public CGFscene
{
public:
	void init();
	void display();
	void update(unsigned long t);
	~DemoScene();
	void setCamera();
	void setLights();
private:
	CGFlight* light0;
	CGFobject* test;
	vector<CGFlight*> lights;
	
};

#endif