#include "DemoScene.h"

GlobalData globals;
Graph graphScene;

void DemoScene::setAnfFileName(char *line,unsigned int size){
	if(fgets(line, size*sizeof(char), stdin)){
		if(sscanf(line,"%s\n",line)==1){
			printf("Trying to open file %s...\n",line);
		}
		else{
			printf("Error obtaining filename.\nDefault \"scene.anf\" will be used.\n");
		}
	}
	else{
		printf("Error obtaining filename.\nDefault \"scene.anf\" will be used.\n");
	}
}

void DemoScene::setGlobals(const GlobalData &globals){
	if(globals.lightEnabled){
		glEnable(GL_LIGHTING);
	}
	else{
		glDisable(GL_LIGHTING);
	}

	if(globals.doublesided){
		glLightModelf(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);
	}
	else{
		glLightModelf(GL_LIGHT_MODEL_TWO_SIDE, GL_FALSE);
	}

	if(globals.lightLocal){
		glLightModelf(GL_LIGHT_MODEL_LOCAL_VIEWER,GL_TRUE);
	}
	else{
		glLightModelf(GL_LIGHT_MODEL_LOCAL_VIEWER,GL_FALSE);
	}
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, globals.lightAmbient);
	if (globals.cullingFace == 0){
		glDisable(GL_CULL_FACE);
	}
	else if(globals.cullingFace == 1){
		glCullFace(GL_BACK);
		glEnable(GL_CULL_FACE);
	}
	else if(globals.cullingFace == 2){
		glCullFace(GL_FRONT);
		glEnable(GL_CULL_FACE);
	}
	else if(globals.cullingFace == 3){
		glCullFace(GL_FRONT_AND_BACK);
		glEnable(GL_CULL_FACE);
	}

	if(globals.cullingOrder == 0){
		glFrontFace(GL_CCW);
	}
	else if(globals.cullingOrder == 1){
		glFrontFace(GL_CW);
	}

	
	drawMode=globals.drawMode;
	if(globals.drawShading == 1){
		glShadeModel(GL_SMOOTH);
	}
	else{
		glShadeModel(GL_FLAT);
	}
	glEnable(GL_NORMALIZE);
	glNormal3f(0,0,1);
}

void DemoScene::init() 
{

	printf("Write the name of the file to be read.\n>> ");
	
	char line[256];
	setAnfFileName(line,256);

	XMLScene anf(line, globals, graphScene);
	setGlobals(globals);
	setLightVector();
	initLights();

	typedef std::map<std::string, Camera >::iterator it_type;
	int c=0;
	for(it_type iterator = graphScene.cameras.begin(); iterator != graphScene.cameras.end(); iterator++,c++) {
		if(iterator->second.isActive)
			activeCameraNumber=c;
	}
	this->cameras=graphScene.cameras;
	setCamera();
	typedef std::map<std::string, Node >::iterator it_typeNode;
	for(it_typeNode iterator=graphScene.nodes.begin(); iterator != graphScene.nodes.end(); iterator++){
		iterator->second.checkList(&graphScene);
	}
	setUpdatePeriod(30);
}

void DemoScene::setLightVector(){
	this->graphLights=graphScene.lights;
}

void DemoScene::update(unsigned long t)
{
	typedef std::map<std::string, Node >::iterator it_typeNode;
	for(it_typeNode iterator=graphScene.nodes.begin(); iterator != graphScene.nodes.end(); iterator++){
		iterator->second.update(wind);
	}
}

void DemoScene::processCameras(){
	setCamera();
}
	
void DemoScene::display() 
{
	if(wind < 0){
		wind=0;
	}
	if(wind >50){
		wind=50;
	}

	updatePer=abs(50-wind);

	setUpdatePeriod(updatePer);
	if(drawMode == 0){
		glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );
	}
	else if(drawMode == 1){
		glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );
	}
	else if(drawMode == 2){
		glPolygonMode( GL_FRONT_AND_BACK, GL_POINT );
	}

	
	glClearColor(globals.drawBackground[0], globals.drawBackground[1], globals.drawBackground[2], globals.drawBackground[3]);
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	setLights();
	//setCamera();
		CGFscene::activeCamera->applyView();
	for(unsigned int i=0;i<graphScene.lights.size();i++){
		if(graphScene.lights.at(i)->marked)
			lights.at(i)->draw();
	}
	axis.draw();

	graphScene.draw();

	glutSwapBuffers();
}

void DemoScene::initLights(){
	for(unsigned int i=0;i<graphLights.size();i++){
		if(graphScene.lights.at(i)->type=="omni"){
			this->lights.push_back(new CGFlight(GL_LIGHT0+i,graphLights.at(i)->pos));
			this->lights.at(i)->setAmbient(graphLights.at(i)->amb);
			this->lights.at(i)->setSpecular(graphLights.at(i)->spe);
			this->lights.at(i)->setDiffuse(graphLights.at(i)->dif);
		}
		else{
			this->lights.push_back(new CGFlight(GL_LIGHT0+i,graphLights.at(i)->pos,graphLights.at(i)->tar));
			this->lights.at(i)->setAmbient(graphLights.at(i)->amb);
			this->lights.at(i)->setSpecular(graphLights.at(i)->spe);
			this->lights.at(i)->setDiffuse(graphLights.at(i)->dif);
			glLightf(GL_LIGHT0+i, GL_SPOT_EXPONENT, graphLights.at(i)->expoente);
			glLightf(GL_LIGHT0+i,GL_SPOT_CUTOFF,graphLights.at(i)->angulo);
		}

		if(graphLights.at(i)->state==1){
				this->lights.at(i)->enable();
				glEnable(GL_LIGHT0+i);
				
			}
			else{
				this->lights.at(i)->disable();
				glDisable(GL_LIGHT0+i);
			}
	}

}

void DemoScene::setLights(){
	for(unsigned int i=0;i<graphLights.size();i++){
		if(graphLights.at(i)->state==1){
				this->lights.at(i)->enable();
				glEnable(GL_LIGHT0+i);
				
			}
			else{
				this->lights.at(i)->disable();
				glDisable(GL_LIGHT0+i);
			}
	}
	
}

void DemoScene::setCamera(){
	int i=0;
	typedef std::map<std::string, Camera >::iterator it_type;
	for(it_type iterator = graphScene.cameras.begin(); iterator != graphScene.cameras.end(); iterator++,i++) {
		if(activeCameraNumber==i){
			glMatrixMode(GL_PROJECTION);
			glLoadIdentity();
			if(iterator->second.type==0){//is ortho camera
				glOrtho(iterator->second.left,iterator->second.right,iterator->second.bottom,iterator->second.top,iterator->second.near,iterator->second.far);
				glMatrixMode(GL_MODELVIEW);
				glLoadIdentity();
				if(iterator->second.direction=="x")
					gluLookAt(1,0,0,0,0,0,0,1,0);
				else if(iterator->second.direction=="y")
					gluLookAt(0,1,0,0,0,0,0,0,-1);
				else
					gluLookAt(0,0,1,0,0,0,0,1,0);
			}
			else if(iterator->second.type==1){//is perspective camera
				gluPerspective(iterator->second.angle,CGFapplication::xy_aspect,iterator->second.near,iterator->second.far);
				glMatrixMode(GL_MODELVIEW);
				glLoadIdentity();
				gluLookAt(iterator->second.pos[0],iterator->second.pos[1],iterator->second.pos[2],iterator->second.target[0],iterator->second.target[1],iterator->second.target[2],0,1,0);
				
			}

			else{
				printf("Camera error\n");
				exit(-1);
			}
			break;
		}
		
	}
	
}

DemoScene::~DemoScene()
{
	for(unsigned int i =0;i<lights.size();i++){
		delete(this->lights.at(i));
		delete(this->graphLights.at(i));
	}
}
