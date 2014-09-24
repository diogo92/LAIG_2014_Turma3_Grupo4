#include "XMLScene.h"

XMLScene::XMLScene(char *filename, struct global_data &globals)
{

	// Read XML from file
	char * temp = NULL;
	doc=new TiXmlDocument( filename );
	bool loadOkay = doc->LoadFile();

	if ( !loadOkay )
	{
		printf( "Could not load file '%s'. Error='%s'. Exiting.\n", filename, doc->ErrorDesc() );
		exit( 1 );
	}

	TiXmlElement* anfElement= doc->FirstChildElement( "anf" );

	if (anfElement == NULL)
	{
		printf("Main anf block element not found! Exiting!\n");
		exit(1);
	}

	globalsElement = anfElement->FirstChildElement( "globals" );

	if (globalsElement == NULL)
		printf("globals block not found!\n");
	else
	{
		printf("Processing globals:\n");

		TiXmlElement* drawElement=globalsElement->FirstChildElement("drawing");
		if (drawElement)
		{
			temp = NULL;
			temp = (char *) drawElement->Attribute("mode");

			if (temp){
				if(strcmp(temp,"fill") == 0) {
					globals.drawMode = 0;
				} else if(strcmp(temp,"line") == 0) {
					globals.drawMode = 1;
				} else if(strcmp(temp,"point") == 0) {
					globals.drawMode = 2;
				} else {
					printf("Invalid value at drawing mode\n");
					exit(-1);
				}
				printf(">> drawing mode: %s\n", temp);
			}
			else{
				printf("Error parsing drawing mode\n");
				exit(-1);
			}

			temp = NULL;
			temp = (char *) drawElement->Attribute("shading");

			if (temp){
				if(strcmp(temp,"flat") == 0){
					globals.drawShading = 0;
				}
				else if(strcmp(temp,"gouraud") == 0){
					globals.drawShading = 1;
				}
				else{
					printf("Invalid value at drawing shading\n");
					exit(-1);
				}
				printf(">> drawing shading: %s\n", temp);
			}
			else{
				printf("Error parsing drawing shading\n");
				exit(-1);
			}

			float r,g,b,a;
			temp = NULL;
			temp = (char *) drawElement->Attribute("background");

			if(temp && sscanf(temp,"%f %f %f %f",&r, &g, &b, &a)==4)
			{
				globals.drawBackground[0] = r;
				globals.drawBackground[1] = g;
				globals.drawBackground[2] = b;
				globals.drawBackground[3] = a;
				printf(">> drawing background (rgba): %f %f %f %f\n", r, g, b, a);
			}
			else {
				printf("Error parsing drawing background");
				exit(-1);
			}

		}
		else {
			printf("drawing not found\n");
			exit (-1);
		}

		TiXmlElement* cullingElement=globalsElement->FirstChildElement("culling");
		if (cullingElement)
		{
			temp = NULL;
			temp = (char *) cullingElement->Attribute("face");

			if (temp){
				if(strcmp(temp,"none") == 0){
					globals.cullingFace = 0;
				}
				else if(strcmp(temp,"back") == 0){
					globals.cullingFace = 1;
				}
				else if(strcmp(temp,"front") == 0){
					globals.cullingFace = 2;
				}
				else if(strcmp(temp,"both") == 0){
					globals.cullingFace = 3;
				}
				else{
					printf("Invalid value at culling face\n");
					exit(-1);
				}
				printf(">> culling face: %s\n", temp);
			}
			else{
				printf("Error parsing culling face\n");
				exit(-1);
			}

			temp = NULL;
			temp = (char *) cullingElement->Attribute("order");

			if (temp){
				if(strcmp(temp,"ccw") == 0){
					globals.cullingOrder = 0;
				}
				else if(strcmp(temp,"cw") == 0){
					globals.cullingOrder = 1;
				}
				else{
					printf("Invalid value at culling order\n");
					exit(-1);
				}
				printf(">> culling order: %s\n", temp);
			}
			else{
				printf("Error parsing culling order\n");
				exit(-1);
			}
		}
		else {
			printf("culling not found\n");
			exit (-1);
		}

	}

}

XMLScene::~XMLScene()
{
	delete(doc);
}

//-------------------------------------------------------

TiXmlElement *XMLScene::findChildByAttribute(TiXmlElement *parent,const char * attr, const char *val)
// Searches within descendants of a parent for a node that has an attribute _attr_ (e.g. an id) with the value _val_
// A more elaborate version of this would rely on XPath expressions
{
	TiXmlElement *child=parent->FirstChildElement();
	int found=0;

	while (child && !found)
		if (child->Attribute(attr) && strcmp(child->Attribute(attr),val)==0)
			found=1;
		else
			child=child->NextSiblingElement();

	return child;
}

