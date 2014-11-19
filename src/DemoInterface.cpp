#include "DemoScene.h"
#include "DemoInterface.h"



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
	map<string,Camera>::const_iterator it;

	for(it=((DemoScene*) scene)->cameras.begin();it!=((DemoScene*) scene)->cameras.end();it++){
		addRadioButtonToGroup(g2,(char*)it->second.id.c_str());
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