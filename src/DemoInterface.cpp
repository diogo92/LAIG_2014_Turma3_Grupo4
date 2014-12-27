#include "DemoScene.h"
#include "DemoInterface.h"

#define BUFSIZE 256
GLuint selectBuf[BUFSIZE];

DemoInterface::DemoInterface()
{
}

void DemoInterface::initGUI()
{
	glutReshapeWindow(550,550);
	GLUI_Panel *masterPanel=addPanel("Interface",GLUI_PANEL_RAISED);
	addStaticTextToPanel(masterPanel,"Interface");
	int atual=2;
	GLUI_Panel *globalPanel= addPanelToPanel(masterPanel,"Globals", 1);
	GLUI_RadioGroup * g1 = addRadioGroupToPanel(globalPanel,&(((DemoScene *) scene)->drawMode),1);
	addRadioButtonToGroup(g1,"Fill");
	addRadioButtonToGroup(g1,"Wireframe");
	addRadioButtonToGroup(g1,"Point");

	addColumnToPanel(masterPanel);
	addStaticTextToPanel(masterPanel,"");
	GLUI_Panel *cameraPanel= addPanelToPanel(masterPanel,"Cameras",1);
	GLUI_RadioGroup * g2 = addRadioGroupToPanel(cameraPanel,&(((DemoScene*) scene)->activeCameraNumber),atual);
	atual++;
	map<string,Camera *>::const_iterator it;

	for(it=((DemoScene*) scene)->cameras.begin();it!=((DemoScene*) scene)->cameras.end();it++){
		addRadioButtonToGroup(g2,(char*)it->second->id.c_str());
	}

	addColumnToPanel(masterPanel);
	addStaticTextToPanel(masterPanel,"");
	GLUI_Panel *lighPanel=addPanelToPanel(masterPanel,"Lights",1);
	for(unsigned int i=0;i<((DemoScene *) scene)->graphLights.size();i++){
		addCheckboxToPanel(lighPanel,(char*)((DemoScene *) scene)->graphLights.at(i)->id.c_str(),(int *)&((DemoScene *) scene)->graphLights.at(i)->state,atual);
	}
	atual++;
	addColumnToPanel(masterPanel);
	addStaticTextToPanel(masterPanel,"");
	GLUI_Spinner *windSpinner=addSpinnerToPanel(masterPanel,"Wind",GLUI_SPINNER_INT,(int *)&(((DemoScene*) scene)->wind),atual);
	windSpinner->set_float_limits(1,50,GLUI_LIMIT_WRAP);

}

void DemoInterface::processGUI(GLUI_Control *ctrl)
{
	if(ctrl->user_id == 2)
		((DemoScene*) scene)->processCameras();
	if(ctrl->user_id > 2)
		((DemoScene*) scene)->setLights();
}

void DemoInterface::processMouse(int button, int state, int x, int y) 
{
	CGFinterface::processMouse(button,state, x, y);

	// do picking on mouse press (GLUT_DOWN)
	// this could be more elaborate, e.g. only performing picking when there is a click (DOWN followed by UP) on the same place
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
		performPicking(x,y);
}


void DemoInterface::performPicking(int x, int y)
{
	// Sets the buffer to be used for selection and activate selection mode
	glSelectBuffer (BUFSIZE, selectBuf);
	glRenderMode(GL_SELECT);
	// Initialize the picking name stack
	glInitNames();
	// The process of picking manipulates the projection matrix
	// so we will be activating, saving and manipulating it
	glMatrixMode(GL_PROJECTION);
	//store current projmatrix to restore easily in the end with a pop
	glPushMatrix ();
	//get the actual projection matrix values on an array of our own to multiply with pick matrix later
	GLfloat projmat[16];
	glGetFloatv(GL_PROJECTION_MATRIX,projmat);
	// reset projection matrix
	glLoadIdentity();
	// get current viewport and use it as reference for
	// setting a small picking window of 5x5 pixels around mouse coordinates for picking
	GLint viewport[4];
	glGetIntegerv(GL_VIEWPORT, viewport);
	// this is multiplied in the projection matrix
	gluPickMatrix ((GLdouble) x, (GLdouble) (CGFapplication::height - y), 5.0, 5.0, viewport);
	// multiply the projection matrix stored in our array to ensure same conditions as in normal render
	glMultMatrixf(projmat);
	// force scene drawing under this mode
	// only the names of objects that fall in the 5x5 window will actually be stored in the buffer
	((DemoScene*) scene)->display();
	// restore original projection matrix
	glMatrixMode (GL_PROJECTION);
	glPopMatrix ();
	glFlush();
	// revert to render mode, get the picking results and process them
	GLint hits;
	hits = glRenderMode(GL_RENDER);
	processHits(hits, selectBuf);
}



void DemoInterface::processHits (GLint hits, GLuint buffer[])
{
	GLuint *ptr = buffer;
	GLuint mindepth = 0xFFFFFFFF;
	GLuint *selected=NULL;
	GLuint nselected;

	// iterate over the list of hits, and choosing the one closer to the viewer (lower depth)
	for (int i=0;i<hits;i++) {
		int num = *ptr; ptr++;
		GLuint z1 = *ptr; ptr++;
		ptr++;
		if (z1 < mindepth && num>0) {
			mindepth = z1;
			selected = ptr;
			nselected=num;
		}
		for (int j=0; j < num; j++) 
			ptr++;
	}
	
	// if there were hits, the one selected is in "selected", and it consist of nselected "names" (integer ID's)
	if (selected!=NULL)
	{
		// this should be replaced by code handling the picked object's ID's (stored in "selected"), 
		// possibly invoking a method on the scene class and passing "selected" and "nselected"
		printf("Picked ID's: ");
		for (int i=0; i<nselected; i++)
			printf("%d ",selected[i]);
		printf("\n");
	}
	else
		printf("Nothing selected while picking \n");	
}