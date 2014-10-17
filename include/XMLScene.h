#ifndef _XMLSCENE_H_
#define _XMLSCENE_H_

#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

#include "tinyxml.h"
#include "GlobalData.h"
#include "Primitives.h"
#include "Appearance.h"
#include "Camera.h"
#include "Light.h"
#include "Graph.h"

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