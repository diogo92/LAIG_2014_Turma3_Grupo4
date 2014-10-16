#ifndef DEMOINTERFACE_H
#define DEMOINTERFACE_H

#include <CGFinterface.h>
class DemoInterface: public CGFinterface {
	public:
		DemoInterface();
		virtual void initGUI();
		virtual void processGUI(GLUI_Control *ctrl);
};

#endif