#ifndef DEMOSCENE_H
#define DEMOSCENE_H

#include "CGFscene.h"
#include "CGFshader.h"
#include "CGFapplication.h"
#include <map>
#include <string>
#include <typeinfo>
#include "NewGraph.h"
class DemoScene : public CGFscene
{
public:
	void init();
	void display();
	void update(unsigned long t);
	~DemoScene();
	void setCamera();
	void setLights();
	int drawMode;
	int activeCameraNumber;
	vector<CGFlight* > lights;
	vector<Light* > graphLights;
	map<string,Camera> cameras;
	void setLightVector();
	void processCameras();
private:
	CGFlight* light0;
	CGFobject* test;
	
};

#endif