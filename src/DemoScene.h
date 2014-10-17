#ifndef DEMOSCENE_H
#define DEMOSCENE_H

#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

#include "CGFscene.h"
#include "CGFshader.h"
#include "CGFapplication.h"
#include "CGFaxis.h"
#include "XMLScene.h"
#include "Graph.h"
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
	void setGlobals(const GlobalData &globals);
	void setCamera();
	void setLights();
	int drawMode;
	int activeCameraNumber;
	vector<CGFlight* > lights;
	vector<Light* > graphLights;
	map<string,Camera> cameras;
	void setLightVector();
	void processCameras();
	void setAnfFileName(char *filename,unsigned int size);
private:
};

#endif