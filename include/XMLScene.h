#ifndef _XMLSCENE_H_
#define _XMLSCENE_H_

#include "tinyxml.h"
#include "DataHolders.h"
#include <cstring>

class XMLScene
{
public:
	XMLScene(char *filename, struct global_data &globals);
	~XMLScene();

	static TiXmlElement *findChildByAttribute(TiXmlElement *parent,const char * attr, const char *val);
	
protected:

	TiXmlDocument* doc;

	TiXmlElement* globalsElement; 
	TiXmlElement* matsElement;
	TiXmlElement* textsElement;
	TiXmlElement* leavesElement;
	TiXmlElement* nodesElement;
	TiXmlElement* graphElement;
};

#endif