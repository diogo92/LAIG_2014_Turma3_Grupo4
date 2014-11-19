#ifndef _XMLSCENE_H_
#define _XMLSCENE_H_

#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

#include "Primitives.h"
#include "tinyxml.h"
#include "GlobalData.h"
#include "Appearance.h"
#include "Camera.h"
#include "Light.h"
#include "Graph.h"
#include "LinearAnimation.h"
#include "CircularAnimation.h"

class XMLScene
{
public:
	XMLScene(char *filename, GlobalData &globals, Graph &graphScene);
	~XMLScene();

	static TiXmlElement *findChildByAttribute(TiXmlElement *parent,const char * attr, const char *val);
	void parseGlobals(GlobalData &globals);
	void parseCameras(Graph &graphScene);
	void parseLights(Graph &graphScene);
	void parseTextures(Graph &graphScene);
	void parseAppearances(Graph &graphScene);
	void parseGraph(Graph &graphScene);
	void parseAnimations(Graph &graphScene);
protected:
	string temp;
	TiXmlDocument* doc;
	TiXmlElement* globalsElement; 
	TiXmlElement* graphElement;
	TiXmlElement* textureElement;
	TiXmlElement* appearanceElement;
	TiXmlElement* cameraElement;
	TiXmlElement* lightElement;
	TiXmlElement* animsElement;
	int cull;
};

#endif