#include "XMLScene.h"

XMLScene::XMLScene(char *filename, GlobalData &globals, Graph &graphScene)
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

	graphElement = anfElement->FirstChildElement("graph");

	if (graphElement == NULL){
		printf("graph element not found\n");
		exit(-1);
	}
	else {
		printf("processing graph\n");

		temp = NULL;
		temp = (char *) graphElement->Attribute("rootid");
		
		if(temp == NULL){
			printf("graph attribute rootid not found\n");
			exit(-1);
		}
		else {
			printf(">> graph rootid: %s\n", temp);
			graphScene.nodes.push_back(Node(temp));
			graphScene.root = & graphScene.nodes.at(graphScene.nodes.size()-1);

		}

		TiXmlElement *node = graphElement->FirstChildElement();
		TiXmlElement *nodeElement;
		int atual;
		bool found;
		while(node){
			
			nodeElement = NULL;
			temp = NULL;
			temp = (char *) node->Attribute("id");

			if(temp == NULL){
				printf("node attribute id not found\n");
				exit(-1);
			}
			else {
				int nodePosition = -1;
				for(int i = 0; i < graphScene.nodes.size(); i++){
					if(strcmp(temp,graphScene.nodes.at(i).id)==0){
						nodePosition = i;
						break;
					}
				}

				if(nodePosition == -1){
					graphScene.nodes.push_back(Node(temp));
					for(int i = 0; i < graphScene.nodes.size(); i++){
						if(strcmp(temp,graphScene.nodes.at(i).id)==0){
							atual =i;
							break;
						}
					}
				}
				else {
					atual = nodePosition;
				}
				printf(">> node id: %s\n",temp);

				nodeElement = node->FirstChildElement("transforms");

				if(nodeElement == NULL){
					printf("  block transforms not found\n");
					exit(-1);
				}
				else{
					// tranforms here
				}

				nodeElement = NULL;

				nodeElement = node->FirstChildElement("primitives");

				if(nodeElement == NULL){
					printf("  block primitives not found\n");
					exit(-1);
				}
				else{
					nodeElement = nodeElement->FirstChildElement();
					while(nodeElement){
						temp = (char *) nodeElement->Value();

						if(strcmp(temp,"rectangle") == 0){
							printf("  primitive rectangle\n");
							float x1,x2,y1,y2;
							
							temp = NULL;
							temp = (char *) nodeElement->Attribute("xy1");
							
							if(temp && sscanf(temp,"%f %f",&x1, &y1)==2)
							{
								printf("  >> xy1: %f %f\n", x1, y1);
							}
							else {
								printf("  error parsing xy1\n");
								exit(-1);
							}
							
							temp = NULL;
							temp = (char *) nodeElement->Attribute("xy2");
							
							if(temp && sscanf(temp,"%f %f",&x2, &y2)==2)
							{
								printf("  >> xy2: %f %f\n", x2, y2);
							}
							else {
								printf("  error parsing xy2\n");
								exit(-1);
							}

							graphScene.nodes.at(atual).primitives.push_back(Rectangle(x1,y1,x2,y2));
						}

						nodeElement = nodeElement->NextSiblingElement();
					}
					// primitives here
				}

				nodeElement = NULL;

				nodeElement = node->FirstChildElement("descendants");

				if(nodeElement == NULL){
					printf("  block descendants not found\n");
					exit(-1);
				}
				else{
					nodeElement = nodeElement->FirstChildElement("noderef");
					if(nodeElement == NULL){
						printf("  doesn't have descendants\n");
					}
					else{
						temp = NULL;
						temp = (char *) nodeElement->Attribute("id");

						if(temp == NULL){
							printf("  error parsing noderef attribute id\n");
							exit(-1);
						}
						else{
							found = false;
							for(int i = 0; i < graphScene.nodes.size();i++){
								if(strcmp(temp,graphScene.nodes.at(i).id)==0){
									found = true;
									graphScene.nodes.at(atual).descendants.push_back(i);
									break;
								}
							}

							if(found == false){
								graphScene.nodes.push_back(Node(temp));
								graphScene.nodes.at(atual).descendants.push_back(graphScene.nodes.size()-1);
								found = true;
							}

							if(!found){
								printf("  error adding descendant\n");
								exit(-1);
							}
							
						}
					}
				}
			}

			node = node->NextSiblingElement();
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


