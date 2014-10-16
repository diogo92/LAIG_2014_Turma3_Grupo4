#include "DemoScene.h"
#include "CGFaxis.h"

#include "XMLScene.h"
#include "NewGraph.h"

GlobalData globals;
NewGraph graphScene;

void DemoScene::init() 
{
	XMLScene anf("scene.anf", globals, graphScene);

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

	if(globals.drawMode == 0){
		glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );
	}
	else if(globals.drawMode == 1){
		glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );
	}
	else if(globals.drawMode == 2){
		glPolygonMode( GL_FRONT_AND_BACK, GL_POINT );
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
	// Declares and enables a light
	/*float light0_pos[4] = {5, 5, 5, 1};
	light0 = new CGFlight(GL_LIGHT0, light0_pos);
	light0->setKc(0.5);
	light0->setKl(0.5);
	light0->setKq(0.5);
	light0->enable();*/
	
	setLightVector();
	setLights();
	
	setCamera();
	// Defines a default normal
	//glNormal3f(0,0,1);
	
	
	setUpdatePeriod(30);
}

void DemoScene::setLightVector(){
	this->graphLights=graphScene.lights;
}

void DemoScene::update(unsigned long t)
{
	
}
	
void DemoScene::display() 
{

	// ---- BEGIN Background, camera and axis setup
	
	// Clear image and depth buffer everytime we update the scene
	glClearColor(globals.drawBackground[0], globals.drawBackground[1], globals.drawBackground[2], globals.drawBackground[3]);
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	// Initialize Model-View matrix as identity (no transformation
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();;
	//Apply transformations corresponding to the camera position relative to the origin
	CGFscene::activeCamera->applyView();

	for(unsigned int i=0;i<graphScene.lights.size();i++){
		if(graphScene.lights.at(i)->marked)
			lights.at(i)->draw();
	}
	// Draw (and update) light
//	light0->draw();
	// Draw axis
	axis.draw();

	graphScene.draw();

	// ---- END feature demos

	// We have been drawing in a memory area that is not visible - the back buffer, 
	// while the graphics card is showing the contents of another buffer - the front buffer
	// glutSwapBuffers() will swap pointers so that the back buffer becomes the front buffer and vice-versa
	glutSwapBuffers();
}

void DemoScene::setLights(){
	for(int i=0;i<graphLights.size();i++){
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

		if(graphScene.lights.at(i)->enabled){
				this->lights.at(i)->enable();
				glEnable(GL_LIGHT0+i);
				graphLights.at(i)->state=1;
			}
			else{
				this->lights.at(i)->disable();
				glDisable(GL_LIGHT0+i);
				graphLights.at(i)->state=0;
			}
	}

}
void DemoScene::setCamera(){
	this->cameras=graphScene.cameras;
	int i=0;
	typedef std::map<std::string, Camera >::iterator it_type;
	for(it_type iterator = graphScene.cameras.begin(); iterator != graphScene.cameras.end(); iterator++,i++) {
		if(iterator->second.initial){
			activeCameraNumber=i;
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
			else if(iterator->second.type==1){
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
	delete(light0);
	delete(test);
}
