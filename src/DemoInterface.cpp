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
	addRadioButtonToGroup(g1,"Point");
	addRadioButtonToGroup(g1,"Wireframe");

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
{/*
	printf ("GUI control id: %d\n  ",ctrl->user_id);
	switch (ctrl->user_id)
	{
	case 9:
		{
			if((ctrl->get_int_val())==1)
				((LightingScene *) scene)->ligaLuz(0);
			else
				((LightingScene *) scene)->desligaLuz(0);
			break;
		};
	case 10:
		{
			if((ctrl->get_int_val())==1)
				((LightingScene *) scene)->ligaLuz(1);
			else
				((LightingScene *) scene)->desligaLuz(1);
			break;
		};

	case 11:
		{
			if((ctrl->get_int_val())==1)
				((LightingScene *) scene)->ligaLuz(2);
			else
				((LightingScene *) scene)->desligaLuz(2);
			break;
		};
	case 12:
		{
			if((ctrl->get_int_val())==1)
				((LightingScene *) scene)->ligaLuz(3);
			else
				((LightingScene *) scene)->desligaLuz(3);
			break;
		};
	case 100:
		{

			((LightingScene *) scene)->mudaRelogio();
			break;

		};

	case 1000:
		{
			printf ("GUI control id: %d\n  ",ctrl->get_int_val());
			((LightingScene *) scene)->mudaTextura(ctrl->get_int_val()-4);
			break;

		};



	case 2000:
		{
			printf ("GUI control id: %d\n  ",ctrl->get_int_val());
			((LightingScene *) scene)->mudaPoligonoTipo(ctrl->get_int_val());

			break;

		};
	}*/
}