#include "XMLScene.h"

XMLScene::XMLScene(char *filename, GlobalData &globals, Graph &graphScene)
{

	// Read XML from file
	string temp;
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
			temp = drawElement->Attribute("mode");

			if (!temp.empty()){
				if(strcmp(temp.c_str(),"fill") == 0) {
					globals.drawMode = 0;
				} else if(strcmp(temp.c_str(),"line") == 0) {
					globals.drawMode = 1;
				} else if(strcmp(temp.c_str(),"point") == 0) {
					globals.drawMode = 2;
				} else {
					printf("Invalid value at drawing mode\n");
					exit(-1);
				}
				printf(">> drawing mode: %s\n", temp.c_str());
			}
			else{
				printf("Error parsing drawing mode\n");
				exit(-1);
			}

			temp = drawElement->Attribute("shading");

			if (!temp.empty()){
				if(strcmp(temp.c_str(),"flat") == 0){
					globals.drawShading = 0;
				}
				else if(strcmp(temp.c_str(),"gouraud") == 0){
					globals.drawShading = 1;
				}
				else{
					printf("Invalid value at drawing shading\n");
					exit(-1);
				}
				printf(">> drawing shading: %s\n", temp.c_str());
			}
			else{
				printf("Error parsing drawing shading\n");
				exit(-1);
			}

			float r,g,b,a;
			temp = drawElement->Attribute("background");

			if(temp.c_str() && sscanf(temp.c_str(),"%f %f %f %f",&r, &g, &b, &a)==4)
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
			temp = cullingElement->Attribute("face");

			if (!temp.empty()){
				if(strcmp(temp.c_str(),"none") == 0){
					globals.cullingFace = 0;
				}
				else if(strcmp(temp.c_str(),"back") == 0){
					globals.cullingFace = 1;
				}
				else if(strcmp(temp.c_str(),"front") == 0){
					globals.cullingFace = 2;
				}
				else if(strcmp(temp.c_str(),"both") == 0){
					globals.cullingFace = 3;
				}
				else{
					printf("Invalid value at culling face\n");
					exit(-1);
				}
				printf(">> culling face: %s\n", temp.c_str());
			}
			else{
				printf("Error parsing culling face\n");
				exit(-1);
			}

			temp = cullingElement->Attribute("order");

			if (!temp.empty()){
				if(strcmp(temp.c_str(),"ccw") == 0){
					globals.cullingOrder = 0;
				}
				else if(strcmp(temp.c_str(),"cw") == 0){
					globals.cullingOrder = 1;
				}
				else{
					printf("Invalid value at culling order\n");
					exit(-1);
				}
				printf(">> culling order: %s\n", temp.c_str());
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

		temp = graphElement->Attribute("rootid");
		string atualnode = graphElement->Attribute("rootid");

		if(temp.empty()){
			printf("graph attribute rootid not found\n");
			exit(-1);
		}
		else {
			printf(">> graph rootid: %s\n", atualnode.c_str());
			graphScene.root = graphElement->Attribute("rootid");
			graphScene.nodes[atualnode] = Node(atualnode);

		}

		TiXmlElement *node = graphElement->FirstChildElement();
		TiXmlElement *nodeElement;
		bool found;
		while(node){
			
			nodeElement = NULL;
			temp = node->Attribute("id");
			atualnode = node->Attribute("id");

			if(temp.empty()){
				printf("node attribute id not found\n");
				exit(-1);
			}
			else {
				printf(">> node id: %s\n",atualnode.c_str());
				if ( graphScene.nodes.find(atualnode) == graphScene.nodes.end() ) {
				  graphScene.nodes[temp] = Node(atualnode);
				}
				
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

						if(strcmp(temp.c_str(),"rectangle") == 0){
							printf("  primitive rectangle\n");
							float x1,x2,y1,y2;
							
							temp = nodeElement->Attribute("xy1");
							
							if(temp.c_str() && sscanf(temp.c_str(),"%f %f",&x1, &y1)==2)
							{
								printf("  >> xy1: %f %f\n", x1, y1);
							}
							else {
								printf("  error parsing xy1\n");
								exit(-1);
							}
							
							temp = nodeElement->Attribute("xy2");
							
							if(temp.c_str() && sscanf(temp.c_str(),"%f %f",&x2, &y2)==2)
							{
								printf("  >> xy2: %f %f\n", x2, y2);
							}
							else {
								printf("  error parsing xy2\n");
								exit(-1);
							}

							graphScene.nodes[atualnode].primitives.push_back(new Rectangle(x1,y1,x2,y2));
						}
						else if(strcmp(temp.c_str(),"torus") == 0){
							printf("  primitive torus\n");
							float innerradius,outerradius;
							int slices,loops;
							
							temp = nodeElement->Attribute("inner");
							
							if(temp.c_str() && sscanf(temp.c_str(),"%f", &innerradius)==1)
							{
								printf("  >> inner: %f\n", innerradius);
							}
							else {
								printf("  error parsing inner\n");
								exit(-1);
							}
							
							temp = nodeElement->Attribute("outer");
							
							if(temp.c_str() && sscanf(temp.c_str(),"%f",&outerradius)==1)
							{
								printf("  >> outer: %f\n", outerradius);
							}
							else {
								printf("  error parsing outer\n");
								exit(-1);
							}

							temp = nodeElement->Attribute("slices");
							
							if(temp.c_str() && sscanf(temp.c_str(),"%d",&slices)==1)
							{
								printf("  >> outer: %d\n", slices);
							}
							else {
								printf("  error parsing slices\n");
								exit(-1);
							}

							temp = nodeElement->Attribute("loops");
							
							if(temp.c_str() && sscanf(temp.c_str(),"%d",&loops)==1)
							{
								printf("  >> outer: %d\n", loops);
							}
							else {
								printf("  error parsing loops\n");
								exit(-1);
							}

							graphScene.nodes[atualnode].primitives.push_back(new Torus(innerradius,outerradius,slices,loops));
						} else if(strcmp(temp.c_str(),"sphere") == 0){
							printf("  primitive sphere\n");
							float radius;
							int slices,stacks;
							
							temp = nodeElement->Attribute("radius");
							
							if(temp.c_str() && sscanf(temp.c_str(),"%f", &radius)==1)
							{
								printf("  >> inner: %f\n", radius);
							}
							else {
								printf("  error parsing radius\n");
								exit(-1);
							}
							
							temp = nodeElement->Attribute("slices");
							
							if(temp.c_str() && sscanf(temp.c_str(),"%d",&slices)==1)
							{
								printf("  >> outer: %d\n", slices);
							}
							else {
								printf("  error parsing slices\n");
								exit(-1);
							}

							temp = nodeElement->Attribute("stacks");
							
							if(temp.c_str() && sscanf(temp.c_str(),"%d",&stacks)==1)
							{
								printf("  >> outer: %d\n", stacks);
							}
							else {
								printf("  error parsing stacks\n");
								exit(-1);
							}

							graphScene.nodes[atualnode].primitives.push_back(new Sphere(radius,slices,stacks));
						}



						nodeElement = nodeElement->NextSiblingElement();
					}
					// primitives here
				}

				nodeElement = NULL;

				nodeElement = node->FirstChildElement("descendants");

				string atualdescendant;

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
						temp = nodeElement->Attribute("id");
						atualdescendant = nodeElement->Attribute("id");

						if(temp.empty()){
							printf("  error parsing noderef attribute id\n");
							exit(-1);
						}
						else{
							if ( graphScene.nodes.find(atualdescendant) == graphScene.nodes.end() ) {
								graphScene.nodes[atualdescendant] = Node(atualdescendant);
							}
							graphScene.nodes[atualnode].descendants.push_back(&graphScene.nodes[atualdescendant]);
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


