#ifndef _XMLSCENE_H_
#define _XMLSCENE_H_

#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

#include "tinyxml.h"
#include "GlobalData.h"
#include "Rectangle.h"
#include "Triangle.h"
#include "Torus.h"
#include "Sphere.h"
#include "Cylinder.h"
#include "Appearance.h"
#include "Camera.h"
#include "Light.h"
#include "NewGraph.h"

class XMLScene
{
public:
	XMLScene(char *filename, GlobalData &globals, NewGraph &graphScene);
	~XMLScene();

	static TiXmlElement *findChildByAttribute(TiXmlElement *parent,const char * attr, const char *val);
	void parseGlobals(GlobalData &globals);
	void parseCameras(NewGraph &graphScene);
	void parseLights(NewGraph &graphScene);
	void parseTextures(NewGraph &graphScene);
	void parseAppearances(NewGraph &graphScene);
	void parseGraph(NewGraph &graphScene);
protected:
	string temp;
	TiXmlDocument* doc;
	TiXmlElement* globalsElement; 
	TiXmlElement* graphElement;
	TiXmlElement* textureElement;
	TiXmlElement* appearanceElement;
	TiXmlElement* cameraElement;
	TiXmlElement* lightElement;

	TiXmlElement* textsElement;
	TiXmlElement* leavesElement;
	TiXmlElement* nodesElement;
};

#endif