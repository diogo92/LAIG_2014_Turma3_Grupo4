#include "XMLScene.h"

XMLScene::XMLScene(char *filename, GlobalData &globals, Graph &graphScene)
{

	// Read XML from file

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
	cameraElement = anfElement->FirstChildElement("cameras");
	lightElement = anfElement->FirstChildElement("lights");
	textureElement = anfElement->FirstChildElement("textures");
	appearanceElement = anfElement->FirstChildElement("appearances");
	graphElement = anfElement->FirstChildElement("graph");

	parseGlobals(globals);
	parseCameras(graphScene);
	parseLights(graphScene);
	parseTextures(graphScene);
	parseAppearances(graphScene);
	parseGraph(graphScene);
}

void XMLScene::parseGlobals(GlobalData &globals){
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

		TiXmlElement* lightingElement=globalsElement->FirstChildElement("lighting");
		if (lightingElement)
		{
			temp = lightingElement->Attribute("doublesided");

			if (!temp.empty()){
				if(strcmp(temp.c_str(),"false") == 0){
					globals.doublesided = false;
				}
				else if(strcmp(temp.c_str(),"true") == 0){
					globals.doublesided = true;
				}
				else{
					printf("Invalid value at lighting doublesided\n");
					exit(-1);
				}
				printf(">> lighting doublesided: %s\n", temp.c_str());
			}
			else{
				printf("Error parsing lighting doublesided\n");
				exit(-1);
			}

			temp = lightingElement->Attribute("local");

			if (!temp.empty()){
				if(strcmp(temp.c_str(),"true") == 0){
					globals.lightLocal = true;
				}
				else if(strcmp(temp.c_str(),"false") == 0){
					globals.lightLocal = false;
				}
				else{
					printf("Invalid value at lighting local\n");
					exit(-1);
				}
				printf(">> lighting local: %s\n", temp.c_str());
			}
			else{
				printf("Error parsing lighting local\n");
				exit(-1);
			}

			temp = lightingElement->Attribute("enabled");

			if (!temp.empty()){
				if(strcmp(temp.c_str(),"true") == 0){
					globals.lightEnabled = true;
				}
				else if(strcmp(temp.c_str(),"false") == 0){
					globals.lightEnabled = false;
				}
				else{
					printf("Invalid value at lighting enabled\n");
					exit(-1);
				}
				printf(">> lighting enabled: %s\n", temp.c_str());
			}
			else{
				printf("Error parsing lighting enabled\n");
				exit(-1);
			}

			float r,g,b,a;
			temp = lightingElement->Attribute("ambient");

			if(temp.c_str() && sscanf(temp.c_str(),"%f %f %f %f",&r, &g, &b, &a)==4)
			{
				globals.lightAmbient[0] = r;
				globals.lightAmbient[1] = g;
				globals.lightAmbient[2] = b;
				globals.lightAmbient[3] = a;
				printf(">> lighting ambient (rgba): %f %f %f %f\n", r, g, b, a);
			}
			else {
				printf("Error parsing lighting ambient");
				exit(-1);
			}
		}
		else {
			printf("lighting not found\n");
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
					cull=0;
				}
				else if(strcmp(temp.c_str(),"cw") == 0){
					globals.cullingOrder = 1;
					cull=1;
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
}
void XMLScene::parseCameras(Graph &graphScene){
	if(cameraElement == NULL){
		printf("cameras element not found\n");
		exit(-1);
	}

	else{
		printf("processing cameras\n");

		temp = cameraElement->Attribute("initial");

		if(temp.empty()){
			printf("camera attribute initial not found\n");
			exit(-1);
		}

		string initialID=temp;

		TiXmlElement *nodeCamera=cameraElement->FirstChildElement();
		while(nodeCamera){
			string type=nodeCamera->Value();
			string id=nodeCamera->Attribute("id");
			if(type=="perspective"){
				printf(">> processing perspective camera %s\n",id.c_str());
				float near,far,angle,pos[3],target[3];
				temp=nodeCamera->Attribute("near");
				if(temp.c_str() && sscanf(temp.c_str(),"%f",&near)==1)
				{
					printf(">> perspective camera near = %f\n", near);
				}
				else {
					printf("Error parsing near attribute");
					exit(-1);
				}
				temp=nodeCamera->Attribute("far");
				if(temp.c_str() && sscanf(temp.c_str(),"%f",&far)==1)
				{
					printf(">> perspective camera far = %f\n", far);
				}
				else {
					printf("Error parsing far attribute");
					exit(-1);
				}
				temp=nodeCamera->Attribute("angle");
				if(temp.c_str() && sscanf(temp.c_str(),"%f",&angle)==1)
				{
					printf(">> perspective camera angle = %f\n", angle);
				}
				else {
					printf("Error parsing angle attribute");
					exit(-1);
				}
				temp=nodeCamera->Attribute("pos");
				if(temp.c_str() && sscanf(temp.c_str(),"%f %f %f",&pos[0], &pos[1], &pos[2])==3)
				{
					printf(">> perspective camera pos: %f %f %f\n", pos[0], pos[1], pos[2]);
				}
				else {
					printf("Error parsing perspective camera position");
					exit(-1);
				}
				temp=nodeCamera->Attribute("target");
				if(temp.c_str() && sscanf(temp.c_str(),"%f %f %f",&target[0], &target[1], &target[2])==3)
				{
					printf(">> perspective camera target: %f %f %f\n", target[0], target[1], target[2]);
				}
				else {
					printf("Error parsing perspective camera target");
					exit(-1);
				}
				graphScene.cameras[id]= Camera(id,near,far,angle,pos,target);
				graphScene.cameras[id].type=1;
				if(id==initialID){
					graphScene.cameras[id].initial=true;
					graphScene.cameras[id].isActive=true;

				}
			}

			else if(type=="ortho"){
				printf(">> processing ortho camera %s\n",id.c_str());
				string direction;
				float near,far,left,right,top,bottom;
				direction=nodeCamera->Attribute("direction");
				if(direction.empty()){
					printf("Error parsing ortho camera direction");
					exit(-1);
				}
				temp=nodeCamera->Attribute("near");
				if(temp.c_str() && sscanf(temp.c_str(),"%f",&near)==1)
				{
					printf(">> ortho camera near = %f\n", near);
				}
				else {
					printf("Error parsing near attribute");
					exit(-1);
				}
				temp=nodeCamera->Attribute("far");
				if(temp.c_str() && sscanf(temp.c_str(),"%f",&far)==1)
				{
					printf(">> ortho camera far = %f\n", far);
				}
				else {
					printf("Error parsing far attribute");
					exit(-1);
				}
				temp=nodeCamera->Attribute("left");
				if(temp.c_str() && sscanf(temp.c_str(),"%f",&left)==1)
				{
					printf(">> ortho camera left = %f\n", left);
				}
				else {
					printf("Error parsing left attribute");
					exit(-1);
				}
				temp=nodeCamera->Attribute("right");
				if(temp.c_str() && sscanf(temp.c_str(),"%f",&right)==1)
				{
					printf(">> ortho camera right = %f\n", right);
				}
				else {
					printf("Error parsing right attribute");
					exit(-1);
				}
				temp=nodeCamera->Attribute("top");
				if(temp.c_str() && sscanf(temp.c_str(),"%f",&top)==1)
				{
					printf(">> ortho camera top = %f\n", top);
				}
				else {
					printf("Error parsing top attribute");
					exit(-1);
				}
				temp=nodeCamera->Attribute("bottom");
				if(temp.c_str() && sscanf(temp.c_str(),"%f",&bottom)==1)
				{
					printf(">> ortho camera bottom = %f\n", bottom);
				}
				else {
					printf("Error parsing bottom attribute");
					exit(-1);
				}
				graphScene.cameras[id]= Camera(id,direction,near,far,left,right,top,bottom);
				graphScene.cameras[id].type=0;
				if(id==initialID){
					graphScene.cameras[id].initial=true;
					graphScene.cameras[id].isActive=true;
					
				}
			}
			else{
				printf("wrong camera type");
				exit(-1);
			}
			nodeCamera=nodeCamera->NextSiblingElement();
		}

	}

}
void XMLScene::parseLights(Graph &graphScene){
	if(lightElement == NULL){
		printf("lights element not found\n");
		exit(-1);
	}

	else{
		int count=0;
		printf("processing lights\n");
		TiXmlElement *nodeLight=lightElement->FirstChildElement("light");
		TiXmlElement *nodeLightChild;
		while(nodeLight){
			if(count>=8){
				printf(">> no more than 8 lights can exist\n");
				break;
			}
			string id=nodeLight->Attribute("id");
			string type=nodeLight->Attribute("type");
			bool enabled,marker;
			float pos[4],amb[4],dif[4],spe[4];
			if(type=="omni"){
				printf(">> processing omni light %s\n",id.c_str());
				temp=nodeLight->Attribute("enabled");
				if(temp=="true"){
					enabled=true;
					printf("omni light enabled: true\n");
				}
				else if(temp=="false"){
					enabled=false;
					printf("omni light enabled: false\n");
				}
				else{
					printf("error parsing omni light attribute enabled");
					exit(-1);
				}
				temp=nodeLight->Attribute("marker");
				if(temp=="true"){
					marker=true;
					printf("omni light marker: true\n");
				}
				else if(temp=="false"){
					marker=false;
					printf("omni light marker: false\n");
				}
				else{
					printf("error parsing omni light attribute marker");
					exit(-1);
				}
				temp=nodeLight->Attribute("pos");
				if(temp.c_str() && sscanf(temp.c_str(),"%f %f %f",&pos[0], &pos[1], &pos[2])==3)
				{
					printf(">> omni light pos: %f %f %f\n", pos[0], pos[1], pos[2]);
				}
				else {
					printf("Error parsing omni light position");
					exit(-1);
				}

				nodeLightChild = findChildByAttribute(nodeLight,"type","ambient");
				if(nodeLightChild == NULL){
					printf("light ambient not found\n");
					exit(-1);
				}
			
				temp = nodeLightChild->Attribute("value");

				if(temp.c_str() && sscanf(temp.c_str(),"%f %f %f %f",&amb[0], &amb[1], &amb[2], &amb[3])==4)
				{
					printf("  >> ambient (rgba): %f %f %f %f\n", amb[0], amb[1], amb[2], amb[3]);
				}
				else {
					printf("Error parsing ambient\n");
					exit(-1);
				}

				nodeLightChild = findChildByAttribute(nodeLight,"type","diffuse");
				if(nodeLightChild == NULL){
					printf("light diffuse not found\n");
					exit(-1);
				}
			
				temp = nodeLightChild->Attribute("value");

				if(temp.c_str() && sscanf(temp.c_str(),"%f %f %f %f",&dif[0], &dif[1], &dif[2], &dif[3])==4)
				{
					printf("  >> diffuse (rgba): %f %f %f %f\n", dif[0], dif[1], dif[2], dif[3]);
				}
				else {
					printf("Error parsing diffuse\n");
					exit(-1);
				}

				nodeLightChild = findChildByAttribute(nodeLight,"type","specular");
				if(nodeLightChild == NULL){
					printf("light specular not found\n");
					exit(-1);
				}
			
				temp = nodeLightChild->Attribute("value");

				if(temp.c_str() && sscanf(temp.c_str(),"%f %f %f %f",&spe[0], &spe[1], &spe[2], &spe[3])==4)
				{
					printf("  >> specular (rgba): %f %f %f %f\n", spe[0], spe[1], spe[2], spe[3]);
				}
				else {
					printf("Error parsing specular\n");
					exit(-1);
				}
				pos[3]=0;
				Light* l=new Light(count,id,type,enabled,marker,pos,amb,dif,spe);
				graphScene.lights.push_back(l);

			}
			else if(type=="spot"){
				float tar[3],angle,exponent;
				printf(">> processing spot light %s\n",id.c_str());
				temp=nodeLight->Attribute("enabled");
				if(temp=="true"){
					enabled=true;
					printf("spot light enabled: true\n");
				}
				else if(temp=="false"){
					enabled=false;
					printf("spot light enabled: false\n");
				}
				else{
					printf("error parsing spot light attribute enabled");
					exit(-1);
				}
				temp=nodeLight->Attribute("marker");
				if(temp=="true"){
					marker=true;
					printf("spot light marker: true\n");
				}
				else if(temp=="false"){
					marker=false;
					printf("spot light marker: false\n");
				}
				else{
					printf("error parsing spot light attribute marker");
					exit(-1);
				}
				temp=nodeLight->Attribute("pos");
				if(temp.c_str() && sscanf(temp.c_str(),"%f %f %f",&pos[0], &pos[1], &pos[2])==3)
				{
					printf(">> spot light pos: %f %f %f\n", pos[0], pos[1], pos[2]);
				}
				else {
					printf("Error parsing spot light position");
					exit(-1);
				}

				temp=nodeLight->Attribute("target");
				if(temp.c_str() && sscanf(temp.c_str(),"%f %f %f",&tar[0], &tar[1], &tar[2])==3)
				{
					printf(">> spot light target: %f %f %f\n", tar[0], tar[1], tar[2]);
				}
				else {
					printf("Error parsing spot light target");
					exit(-1);
				}
				temp=nodeLight->Attribute("angle");
				if(temp.c_str() && sscanf(temp.c_str(),"%f",&angle)==1){
					printf(">> spot light angle: %f\n",angle);
				}
				else {
					printf("Error parsing spot light angle");
					exit(-1);
				}
				temp=nodeLight->Attribute("exponent");
				if(temp.c_str() && sscanf(temp.c_str(),"%f",&exponent)==1){
					printf(">> spot light exponent: %f\n",exponent);
				}
				else {
					printf("Error parsing spot light exponent");
					exit(-1);
				}

				nodeLightChild = findChildByAttribute(nodeLight,"type","ambient");
				if(nodeLightChild == NULL){
					printf("light ambient not found\n");
					exit(-1);
				}
			
				temp = nodeLightChild->Attribute("value");

				if(temp.c_str() && sscanf(temp.c_str(),"%f %f %f %f",&amb[0], &amb[1], &amb[2], &amb[3])==4)
				{
					printf("  >> ambient (rgba): %f %f %f %f\n", amb[0], amb[1], amb[2], amb[3]);
				}
				else {
					printf("Error parsing ambient\n");
					exit(-1);
				}

				nodeLightChild = findChildByAttribute(nodeLight,"type","diffuse");
				if(nodeLightChild == NULL){
					printf("light diffuse not found\n");
					exit(-1);
				}
			
				temp = nodeLightChild->Attribute("value");

				if(temp.c_str() && sscanf(temp.c_str(),"%f %f %f %f",&dif[0], &dif[1], &dif[2], &dif[3])==4)
				{
					printf("  >> diffuse (rgba): %f %f %f %f\n", dif[0], dif[1], dif[2], dif[3]);
				}
				else {
					printf("Error parsing diffuse\n");
					exit(-1);
				}

				nodeLightChild = findChildByAttribute(nodeLight,"type","specular");
				if(nodeLightChild == NULL){
					printf("light specular not found\n");
					exit(-1);
				}
			
				temp = nodeLightChild->Attribute("value");

				if(temp.c_str() && sscanf(temp.c_str(),"%f %f %f %f",&spe[0], &spe[1], &spe[2], &spe[3])==4)
				{
					printf("  >> specular (rgba): %f %f %f %f\n", spe[0], spe[1], spe[2], spe[3]);
				}
				else {
					printf("Error parsing specular\n");
					exit(-1);
				}
				pos[3]=1.0;
				Light* l=new Light(count,id,type,enabled,marker,pos,tar,angle,exponent,amb,dif,spe);
				graphScene.lights.push_back(l);
			}

			else{
				printf("error parsing lights");
				exit(-1);
			}
			count++;
			nodeLight=nodeLight->NextSiblingElement();
		}
	}
}
void XMLScene::parseTextures(Graph &graphScene){
	if(textureElement == NULL){
		printf("textures element not found\n");
		exit(-1);
	}
	else{
		printf("processing textures\n");
		TiXmlElement *nodeTexture = textureElement->FirstChildElement("texture");
		while(nodeTexture){
			temp = nodeTexture->Attribute("id");
			string texid = nodeTexture->Attribute("id");
			float texlength_s;
			float texlength_t;
			if(texid.empty()){
				printf("texture id not found\n");
				exit(-1);
			}
			else{
				printf(">> texture %s\n", texid.c_str());
				graphScene.textures[texid].id=texid;
			}

			temp = nodeTexture->Attribute("file");
			if(!temp.empty())
			{
				printf(">> file: %s\n",temp.c_str());
				graphScene.textures[texid].file=temp;
			}
			else{
				printf("texture file not found\n");
				exit(-1);
			}

			temp = nodeTexture->Attribute("texlength_s");
			if(temp.c_str() && sscanf(temp.c_str(),"%f",&texlength_s)==1)
			{
				printf(">> texlength_s: %f\n",texlength_s);
				graphScene.textures[texid].texlength_s=texlength_s;
			}
			else{
				printf("texture texlength_s not found\n");
				exit(-1);
			}

			temp = nodeTexture->Attribute("texlength_t");
			if(temp.c_str() && sscanf(temp.c_str(),"%f",&texlength_t)==1)
			{
				printf(">> texlength_t: %f\n",texlength_t);
				graphScene.textures[texid].texlength_t=texlength_t;
			}
			else{
				printf("texture texlength_t not found\n");
				exit(-1);
			}
			
			nodeTexture = nodeTexture->NextSiblingElement();
		}
	}
}
void XMLScene::parseAppearances(Graph &graphScene){
	if (appearanceElement == NULL){
		printf("appearances element not found\n");
		exit(-1);
	}
	else {
		printf("processing appearances\n");
		TiXmlElement *nodeAppearance = appearanceElement->FirstChildElement();
		unsigned int counter = 0;
		while(nodeAppearance){
			TiXmlElement * nodeAppearanceChild;
			temp = nodeAppearance->Attribute("id");
			string appid = nodeAppearance->Attribute("id");
			float shininess;
			if(appid.empty()){
				printf("appearance id not found\n");
				exit(-1);
			}
			else{
				printf(">> appearance %s\n", appid.c_str());
			}

			temp = nodeAppearance->Attribute("shininess");
			if(temp.c_str() && sscanf(temp.c_str(),"%f",&shininess)==1)
			{
				printf(">> shinissess: %f\n",shininess);
			}
			else{
				printf("appearance shininess not found\n");
				exit(-1);
			}
			string texid;
			bool hastexture=false;
			if(nodeAppearance->Attribute("textureref")){
				temp=nodeAppearance->Attribute("textureref");
				
					hastexture=true;
					texid=temp;
				
			}
			
			float amb[4];
			float dif[4];
			float spe[4];

			nodeAppearanceChild = findChildByAttribute(nodeAppearance,"type","ambient");
			if(nodeAppearanceChild == NULL){
				printf("appearence ambient not found\n");
				exit(-1);
			}
			
			temp = nodeAppearanceChild->Attribute("value");

			if(temp.c_str() && sscanf(temp.c_str(),"%f %f %f %f",&amb[0], &amb[1], &amb[2], &amb[3])==4)
			{
				printf("  >> ambient (rgba): %f %f %f %f\n", amb[0], amb[1], amb[2], amb[3]);
			}
			else {
				printf("Error parsing ambient\n");
				exit(-1);
			}

			nodeAppearanceChild = findChildByAttribute(nodeAppearance,"type","diffuse");
			if(nodeAppearanceChild == NULL){
				printf("appearence diffuse not found\n");
				exit(-1);
			}
			
			temp = nodeAppearanceChild->Attribute("value");

			if(temp.c_str() && sscanf(temp.c_str(),"%f %f %f %f",&dif[0], &dif[1], &dif[2], &dif[3])==4)
			{
				printf("  >> diffuse (rgba): %f %f %f %f\n", dif[0], dif[1], dif[2], dif[3]);
			}
			else {
				printf("Error parsing diffuse\n");
				exit(-1);
			}

			nodeAppearanceChild = findChildByAttribute(nodeAppearance,"type","specular");
			if(nodeAppearanceChild == NULL){
				printf("appearance specular not found\n");
				exit(-1);
			}
			
			temp = nodeAppearanceChild->Attribute("value");

			if(temp.c_str() && sscanf(temp.c_str(),"%f %f %f %f",&spe[0], &spe[1], &spe[2], &spe[3])==4)
			{
				printf("  >> specular (rgba): %f %f %f %f\n", spe[0], spe[1], spe[2], spe[3]);
			}
			else {
				printf("Error parsing specular\n");
				exit(-1);
			}
			
			
			graphScene.appearances[appid] = Appearance(appid,shininess,amb,dif,spe);

			if(hastexture){
				graphScene.appearances[appid].setTexture(graphScene.textures[texid].file);
				graphScene.appearances[appid].setTextureWrap(GL_REPEAT,GL_REPEAT);
				graphScene.appearances[appid].s=graphScene.textures[texid].texlength_s;
				graphScene.appearances[appid].t=graphScene.textures[texid].texlength_t;
			}
			
			nodeAppearance = nodeAppearance->NextSiblingElement();
			counter++;
		}
		if(counter == 0){
			printf("didn't find any appearance block\n");
			exit(-1);
		}
	}
}
void XMLScene::parseGraph(Graph &graphScene){
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
			graphScene.rootNode = graphElement->Attribute("rootid");
		}

		TiXmlElement *node = graphElement->FirstChildElement();
		TiXmlElement *nodeElement;
		bool found = false;
		bool existsPrim;
		bool existsDesc;
		while(node){
			bool displayList=false;
			nodeElement = NULL;
			temp = node->Attribute("id");
			atualnode = node->Attribute("id");

			if(temp.empty()){
				printf("node attribute id not found\n");
				exit(-1);
			}
			else {

				if(node->Attribute("displaylist")){
					temp=node->Attribute("displaylist");
					if(temp=="true")
						displayList=true;
				}
				existsPrim=false;
				existsDesc=false;
				printf(">> node id: %s\n",atualnode.c_str());
				if ( graphScene.nodes.find(atualnode) == graphScene.nodes.end() ) {
					graphScene.nodes[atualnode] = Node(atualnode);
					graphScene.nodes[atualnode].displayList=displayList;
				}
				else{
					printf(">> node %s already exists\n",atualnode.c_str());
					exit(-1);
				}

				nodeElement = node->FirstChildElement("transforms");

				if(nodeElement == NULL){
					printf("  block transforms not found\n");
					exit(-1);
				}
				else{
					nodeElement = nodeElement->FirstChildElement();
					glLoadIdentity();
					while(nodeElement){
						temp = (char *) nodeElement->Value();
						if(strcmp(temp.c_str(),"transform") == 0){
							printf("  transform\n");
							temp = nodeElement->Attribute("type");
							if(strcmp(temp.c_str(),"translate")==0)
							{
								printf("  >> type: translate\n");
								temp = nodeElement->Attribute("to");
								float x,y,z;
								if(temp.c_str() && sscanf(temp.c_str(),"%f %f %f",&x,&y,&z)==3)
								{
									printf("  >> to: %f %f %f\n", x,y,z);
								}
								else {
									printf("  error parsing to\n");
									exit(-1);
								}
								glTranslatef(x,y,z);
							}
							else if(strcmp(temp.c_str(),"rotate")==0)
							{
								temp = nodeElement->Attribute("axis");
								string axis;
								float angle,axisx = 0,axisy = 0, axisz = 0;
								if(!temp.empty())
								{
									if(temp == "x" || temp == "y" || temp == "z"){
										axis = temp;
										printf("  >> axis: %s\n", axis.c_str());
										if(temp == "x"){
											axisx = 1;
										}
										else if(temp == "y"){
											axisy = 1;
										} else {
											axisz = 1;
										}
									}
									else{
										printf("  error: wrong value of axis\n");
										exit(-1);
									}
								}
								else {
									printf("  error parsing axis\n");
									exit(-1);
								}
								temp = nodeElement->Attribute("angle");
								if(temp.c_str() && sscanf(temp.c_str(),"%f",&angle)==1)
								{
									printf("  >> angle: %f\n", angle);
								}
								else {
									printf("  error parsing angle\n");
									exit(-1);
								}
								glRotatef(angle,axisx,axisy,axisz);

							}
							else if(strcmp(temp.c_str(),"scale")==0){
								temp = nodeElement->Attribute("factor");
								float x,y,z;
								if(temp.c_str() && sscanf(temp.c_str(),"%f %f %f",&x,&y,&z)==3)
								{
									printf("  >> factor: %f %f %f\n", x,y,z);
								}
								else {
									printf("  error parsing factor\n");
									exit(-1);
								}
								glScalef(x,y,z);
							}

							else {
								printf("  error parsing type\n");
								exit(-1);
							}

						}

						nodeElement = nodeElement->NextSiblingElement();
					}
					float m[16];
					glGetFloatv(GL_MODELVIEW_MATRIX, &m[0]);
					for(int i = 0; i<16; i++)
						graphScene.nodes[atualnode].matrix[i] = m[i];

				}
				
				TiXmlElement *prim=node->FirstChildElement("primitives");
				if(prim!=NULL)
					existsPrim=true;
				TiXmlElement *desc=node->FirstChildElement("descendants");
				if(desc!=NULL)
					existsDesc=true;
				
				nodeElement = NULL;
				nodeElement = node->FirstChildElement("appearanceref");

				if(nodeElement == NULL){
					printf("  element appearanceref not found\n");
					exit(-1);
				}
				else{
					string id = nodeElement->Attribute("id");

					if(id.empty()){
						printf("  attribute id not found\n");
						exit(-1);
					}
					if(id=="inherit")
						graphScene.nodes[atualnode].inherited=true;
					else{
						graphScene.nodes[atualnode].inherited=false;
						graphScene.nodes[atualnode].appear = &graphScene.appearances[id];
					}
				}

				/********************/

				if(prim == NULL && !existsDesc){
					printf("  blocks primitives and descendants not found\n");
					exit(-1);
				}
				else if(prim !=NULL){
					nodeElement = prim->FirstChildElement();
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
						else if(strcmp(temp.c_str(),"plane")==0){
							printf(" primitive plane\n");
							float parts;
							temp = nodeElement->Attribute("parts");
							if(temp.c_str() && sscanf(temp.c_str(),"%f",&parts)==1)
							{
								printf(" >> parts: %f\n",parts);
							}
							else{
								printf(" error parsing parts\n");
								exit(-1);
							}
							graphScene.nodes[atualnode].primitives.push_back(new Plane(parts));
						}
						else if(strcmp(temp.c_str(),"patch")==0){
							string compute;
							float partsU,partsV,order;
							temp=nodeElement->Attribute("compute");
							if(!temp.empty()){
								if(temp=="point" || temp=="line" || temp=="fill")
									compute=temp;
								else{
									printf(" compute value error\n");
									exit(-1);
								}
							}
							else{
								printf(" error parsing compute\n");
							}
							temp=nodeElement->Attribute("order");
							if(temp.c_str() && sscanf(temp.c_str(),"%f",&order)==1){
								printf(" >> order: %f\n",order);
								if(order>3 || order<1){
									printf(" order must be a value between 1 and 3\n");
									exit(-1);
								}
							}
							else {
								printf("  error parsing order\n");
								exit(-1);
							}

							temp = nodeElement->Attribute("partsU");
							if(temp.c_str() && sscanf(temp.c_str(),"%f",&partsU)==1){
								printf(" >> partsU: %f\n",partsU);
							}
							else {
								printf("  error parsing partsU\n");
								exit(-1);
							}

							temp = nodeElement->Attribute("partsV");
							if(temp.c_str() && sscanf(temp.c_str(),"%f",&partsV)==1){
								printf(" >> partsV: %f\n",partsV);
							}
							else {
								printf("  error parsing partsV\n");
								exit(-1);
							}
							TiXmlElement* ctrlpoints=nodeElement->FirstChildElement();
							const int numCP = (order+1)*(order+1);
							int count=0;
							GLfloat* ctrl = new GLfloat[numCP*3];
							while(ctrlpoints){
								float x,y,z;
								temp=ctrlpoints->Attribute("x");
								if(temp.c_str() && sscanf(temp.c_str(),"%f",&x)==1){
									printf(" >> x: %f\n",x);
								}
								else{
									printf(" error parsing x\n");
									exit(-1);
								}
								temp=ctrlpoints->Attribute("y");
								if(temp.c_str() && sscanf(temp.c_str(),"%f",&y)==1){
									printf(" >> y: %f\n",y);
								}
								else{
									printf(" error parsing y\n");
									exit(-1);
								}
								temp=ctrlpoints->Attribute("z");
								if(temp.c_str() && sscanf(temp.c_str(),"%f",&z)==1){
									printf(" >> z: %f\n",z);
								}
								else{
									printf(" error parsing y\n");
									exit(-1);
								}
								ctrl[count*3 + 0]=x;
								ctrl[count*3 + 1]=y;
								ctrl[count*3 + 2]=z;
								count++;
								ctrlpoints=ctrlpoints->NextSiblingElement();
							}
							if(count!=numCP){
								printf(" bad number of control points\n");
								exit(-1);
							}
							GLfloat* ctPoints = new GLfloat[numCP * 3];
							for(int i = 0; i < numCP; i++) {
								int tmp = (i%3);
								tmp *= ((order+1)*(order+1));
								tmp += floor((float)i/3) *3;
								ctPoints[i*3 + 0] = ctrl[tmp + 0];
								ctPoints[i*3 + 1] = ctrl[tmp + 1];
								ctPoints[i*3 + 2] = ctrl[tmp + 2];
							}
							if(cull==1)
								graphScene.nodes[atualnode].primitives.push_back(new Patch(order,partsU,partsV,compute,ctrl));
							else
								graphScene.nodes[atualnode].primitives.push_back(new Patch(order,partsU,partsV,compute,ctPoints));
						}
						else if(strcmp(temp.c_str(),"vehicle")==0){
							graphScene.nodes[atualnode].primitives.push_back(new Vehicle());
						}
						else if(strcmp(temp.c_str(),"triangle") == 0){
							printf("  primitive triangle\n");
							float x1,x2,x3,y1,y2,y3,z1,z2,z3;

							temp = nodeElement->Attribute("xyz1");

							if(temp.c_str() && sscanf(temp.c_str(),"%f %f %f",&x1, &y1, &z1)==3)
							{
								printf("  >> xyz1: %f %f %f\n", x1, y1, z1);
							}
							else {
								printf("  error parsing xyz1\n");
								exit(-1);
							}

							temp = nodeElement->Attribute("xyz2");

							if(temp.c_str() && sscanf(temp.c_str(),"%f %f %f",&x2, &y2, &z2)==3)
							{
								printf("  >> xy2: %f %f %f\n", x2, y2, z2);
							}
							else {
								printf("  error parsing xyz2\n");
								exit(-1);
							}

							temp = nodeElement->Attribute("xyz3");

							if(temp.c_str() && sscanf(temp.c_str(),"%f %f %f",&x3, &y3, &z3)==3)
							{
								printf("  >> xyz3: %f %f %f\n", x3, y3, z3);
							}
							else {
								printf("  error parsing xyz3\n");
								exit(-1);
							}

							graphScene.nodes[atualnode].primitives.push_back(new Triangle(x1,y1,z1,x2,y2,z2,x3,y3,z3));
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
								printf("  >> slices: %d\n", slices);
							}
							else {
								printf("  error parsing slices\n");
								exit(-1);
							}

							temp = nodeElement->Attribute("loops");

							if(temp.c_str() && sscanf(temp.c_str(),"%d",&loops)==1)
							{
								printf("  >> loops: %d\n", loops);
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
								printf("  >> radius: %f\n", radius);
							}
							else {
								printf("  error parsing radius\n");
								exit(-1);
							}

							temp = nodeElement->Attribute("slices");

							if(temp.c_str() && sscanf(temp.c_str(),"%d",&slices)==1)
							{
								printf("  >> slices: %d\n", slices);
							}
							else {
								printf("  error parsing slices\n");
								exit(-1);
							}

							temp = nodeElement->Attribute("stacks");

							if(temp.c_str() && sscanf(temp.c_str(),"%d",&stacks)==1)
							{
								printf("  >> stacks: %d\n", stacks);
							}
							else {
								printf("  error parsing stacks\n");
								exit(-1);
							}
							graphScene.nodes[atualnode].primitives.push_back(new Sphere(radius,slices,stacks));
						}
						else if(strcmp(temp.c_str(),"cylinder") == 0){
							printf("  primitive cylinder\n");
							float base,top,height;
							int slices,stacks;

							temp = nodeElement->Attribute("base");

							if(temp.c_str() && sscanf(temp.c_str(),"%f", &base)==1)
							{
								printf("  >> base: %f\n", base);
							}
							else {
								printf("  error parsing base\n");
								exit(-1);
							}

							temp = nodeElement->Attribute("top");

							if(temp.c_str() && sscanf(temp.c_str(),"%f", &top)==1)
							{
								printf("  >> top: %f\n", top);
							}
							else {
								printf("  error parsing top\n");
								exit(-1);
							}

							temp = nodeElement->Attribute("height");

							if(temp.c_str() && sscanf(temp.c_str(),"%f", &height)==1)
							{
								printf("  >> height: %f\n", height);
							}
							else {
								printf("  error parsing height\n");
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

							graphScene.nodes[atualnode].primitives.push_back(new Cylinder(base,top,height,slices,stacks));
						}



						nodeElement = nodeElement->NextSiblingElement();
					}
				}

				nodeElement = NULL;

				nodeElement = node->FirstChildElement("descendants");

				string atualdescendant;

				if(nodeElement == NULL && !existsPrim){
					printf("  blocks descendants and primitives not found\n");
					exit(-1);
				}
				else if(nodeElement !=NULL){
					nodeElement = nodeElement->FirstChildElement("noderef");
					while(nodeElement){
							temp = nodeElement->Attribute("id");
							atualdescendant = nodeElement->Attribute("id");

							if(temp.empty()){
								printf("  error parsing noderef attribute id\n");
								exit(-1);
							}
							else{
								printf("  >> descendant %s\n",atualdescendant.c_str());
								/*if ( graphScene.nodes.find(atualdescendant) == graphScene.nodes.end() ) {
									graphScene.nodes[atualdescendant] = Node(atualdescendant);
								}
								if ( graphScene.graphNodes.find(atualdescendant) == graphScene.graphNodes.end() ) {
									graphScene.graphNodes[atualdescendant] = GraphNode(atualdescendant);
									if(graphScene.nodes.find(atualdescendant) == graphScene.nodes.end()){
										graphScene.nodes[atualdescendant] = Node(atualdescendant);
									}
									graphScene.graphNodes[atualdescendant].atualNode = &graphScene.nodes[atualdescendant];
								}
								graphScene.graphNodes[atualnode].descendants[atualdescendant] = &graphScene.graphNodes[atualdescendant];
								*/
								graphScene.nodes[atualnode].childs.push_back(atualdescendant);
							}
						nodeElement = nodeElement->NextSiblingElement();
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


