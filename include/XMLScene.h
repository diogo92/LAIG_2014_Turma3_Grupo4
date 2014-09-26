#ifndef _XMLSCENE_H_
#define _XMLSCENE_H_

#include "tinyxml.h"
#include "GlobalData.h"
#include "Graph.h"
#include "Rectangle.h"
#include "Torus.h"
#include "Sphere.h"

class XMLScene
{
public:
	XMLScene(char *filename, GlobalData &globals, Graph &graphScene);
	~XMLScene();

	static TiXmlElement *findChildByAttribute(TiXmlElement *parent,const char * attr, const char *val);
	
protected:
	TiXmlDocument* doc;
	TiXmlElement* globalsElement; 
	TiXmlElement* graphElement;

	TiXmlElement* textsElement;
	TiXmlElement* leavesElement;
	TiXmlElement* nodesElement;
};

#endif