#include "DemoInterface.h"
#include "DemoScene.h"


DemoInterface::DemoInterface()
{
}

void DemoInterface::initGUI()
{
	int atual=2;
	GLUI_Panel *panel= addPanel("Globals   -   Cameras   -   Lights", 1);
	GLUI_RadioGroup * g1 = addRadioGroupToPanel(panel,&(((DemoScene *) scene)->drawMode),1);
	addRadioButtonToGroup(g1,"Fill");
	addRadioButtonToGroup(g1,"Wireframe");
	addRadioButtonToGroup(g1,"Point");

	addColumnToPanel(panel);

	GLUI_RadioGroup * g2 = addRadioGroupToPanel(panel,&(((DemoScene*) scene)->activeCameraNumber),atual);
	atual++;
	map<string,Camera>::const_iterator it;

	for(it=((DemoScene*) scene)->cameras.begin();it!=((DemoScene*) scene)->cameras.end();it++){
		addRadioButtonToGroup(g2,(char*)it->second.id.c_str());
	}
	addColumnToPanel(panel);

	for(int i=0;i<((DemoScene *) scene)->graphLights.size();i++){
		addCheckboxToPanel(panel,(char*)((DemoScene *) scene)->graphLights.at(i)->id.c_str(),(int *)&((DemoScene *) scene)->graphLights.at(i)->state,atual);
	}

}

void DemoInterface::processGUI(GLUI_Control *ctrl)
{
	if(ctrl->user_id == 2)
		((DemoScene*) scene)->processCameras();
	if(ctrl->user_id > 2)
		((DemoScene*) scene)->setLights();
}