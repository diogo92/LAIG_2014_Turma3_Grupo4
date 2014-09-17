#include "DemoScene.h"
#include "CGFaxis.h"
#include "CGFapplication.h"

#include "ExampleObject.h"
#include "DataHolders.h"

struct global_data globals;

#include <math.h>

#include "CGFappearance.h"

#include "XMLScene.h"

void DemoScene::init() 
{
	XMLScene anf("scene.anf", globals);

	// Enables lighting computations
	glEnable(GL_LIGHTING);

	// Sets up some lighting parameters
	glLightModelf(GL_LIGHT_MODEL_TWO_SIDE, GL_FALSE);
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, CGFlight::background_ambient);  // Define ambient light
	
	// Declares and enables a light
	float light0_pos[4] = {4.0, 6.0, 5.0, 1.0};
	light0 = new CGFlight(GL_LIGHT0, light0_pos);
	light0->enable();

	// Defines a default normal
	glNormal3f(0,0,1);

	setUpdatePeriod(30);
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
	glLoadIdentity();

	// Apply transformations corresponding to the camera position relative to the origin
	CGFscene::activeCamera->applyView();

	// Draw (and update) light
	light0->draw();

	// Draw axis
	axis.draw();



	// ---- END feature demos

	// We have been drawing in a memory area that is not visible - the back buffer, 
	// while the graphics card is showing the contents of another buffer - the front buffer
	// glutSwapBuffers() will swap pointers so that the back buffer becomes the front buffer and vice-versa
	glutSwapBuffers();
}

DemoScene::~DemoScene()
{
	delete(light0);
}
