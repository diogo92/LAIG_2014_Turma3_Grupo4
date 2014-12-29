#ifndef DEMOINTERFACE_H
#define DEMOINTERFACE_H

#include <CGFinterface.h>
class DemoInterface: public CGFinterface {
	public:
		DemoInterface();
		virtual void initGUI();
		virtual void processGUI(GLUI_Control *ctrl);
		virtual void processMouse(int button, int state, int x, int y);
		void performPicking(int x, int y);
		void processHits(GLint hits, GLuint buffer[]);
		bool pieceSelected;
};

#endif